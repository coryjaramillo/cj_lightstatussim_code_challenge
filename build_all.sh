#!/bin/bash

set -e  # Exit immediately if a build command fails

USERNAME="${USERNAME:-$USER}"

# List any possible CLion install roots on your system here:
CLION_SEARCH_ROOTS=(
    "/c/Users/$USERNAME/AppData/Local/Programs"
    "/c/Program Files/JetBrains"
)

CLION_CMAKE=""

for search_root in "${CLION_SEARCH_ROOTS[@]}"; do
    echo "Search Root: $search_root"
    if [[ -d "$search_root" ]]; then
        latest_clion=$(ls -d "$search_root"/CLion* 2>/dev/null | sort -Vr | head -n 1)
        if [[ -n "$latest_clion" ]]; then
            candidate="$latest_clion/bin/cmake/win/x64/bin/cmake.exe"
            if [[ -f "$candidate" ]]; then
                CLION_CMAKE="$candidate"
                break  # Stop at the first found, highest version
            fi
        fi
    fi
done

# If CLion bundled not found, fall back to PATH/system CMake
if [[ -n "$CLION_CMAKE" ]]; then
    CMAKE_EXE="$CLION_CMAKE"
else
    CMAKE_EXE=$(where cmake.exe 2>/dev/null | head -n 1)
    if [[ -z "$CMAKE_EXE" ]]; then
        if [[ -f "/c/Program Files/CMake/bin/cmake.exe" ]]; then
            CMAKE_EXE="/c/Program Files/CMake/bin/cmake.exe"
        elif [[ -f "/c/Program Files (x86)/CMake/bin/cmake.exe" ]]; then
            CMAKE_EXE="/c/Program Files (x86)/CMake/bin/cmake.exe"
        else
            echo "CMake executable not found (not in any CLion bundled or system locations)."
            exit 1
        fi
    fi
fi

echo "Using CMake: $CMAKE_EXE"



# Get the number of logical CPUs on the system
if command -v nproc >/dev/null 2>&1; then
    ALL_CPUS=$(nproc)
elif command -v wmic >/dev/null 2>&1; then
    ALL_CPUS=$(wmic cpu get NumberOfLogicalProcessors | awk 'NF {print $1}' | head -n 1)
else
    ALL_CPUS=2
fi

# Calculate 75% of available CPUs, rounded up
CPUS=$(( (ALL_CPUS * 3 + 3) / 4 ))

# Guarantee at least 2
if (( CPUS < 2 )); then
    CPUS=2
fi

echo "Using $CPUS out of $ALL_CPUS available CPUs for parallel build jobs."


# Find the project root directory dynamically
# Searches from your home directory downward (adjust "/" to a narrower root if you want)
# Assume script is run from the project root
PROJECT_ROOT="$(pwd)"
PROJECT_NAME="cj_lightstatussim_code_challenge"

# Double-check that this really looks like the project… (optional)
if [[ ! -d "$PROJECT_ROOT/.idea" && ! -e "$PROJECT_ROOT/CMakeLists.txt" ]]; then
    echo "ERROR: This does not appear to be the '$PROJECT_NAME' root directory"
    exit 1
fi

# Convert Unix/Msys path to Windows format for CMake/MinGW
if command -v cygpath >/dev/null 2>&1; then
    WIN_PROJECT_ROOT=$(cygpath -w "$PROJECT_ROOT")
else
    # Bash/WSL fallback; crude but works if root starts with /e/
    WIN_PROJECT_ROOT=$(echo "$PROJECT_ROOT" | sed -E 's#^/([a-zA-Z])/#\1:/#')
fi

echo "Using current directory as project root: $WIN_PROJECT_ROOT"

# Build Debug_Simple
"$CMAKE_EXE" --build "$WIN_PROJECT_ROOT\\cmake-build-debug_simple" --target cj_lightsimstatus_code_chal -j "$CPUS"

# Build Debug_Verbose
"$CMAKE_EXE" --build "$WIN_PROJECT_ROOT\\cmake-build-debug_verbose" --target cj_lightsimstatus_code_chal -j "$CPUS"

# Build Debug_All
"$CMAKE_EXE" --build "$WIN_PROJECT_ROOT\\cmake-build-debug_all" --target cj_lightsimstatus_code_chal -j "$CPUS"

# Build Release
"$CMAKE_EXE" --build "$WIN_PROJECT_ROOT\\cmake-build-release" --target cj_lightsimstatus_code_chal -j "$CPUS"
