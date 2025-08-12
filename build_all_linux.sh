#!/bin/bash

# Bash script to build all configurations for Linux
# Usage: ./build_all_linux.sh [--clean]

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
GRAY='\033[0;37m'
NC='\033[0m' # No Color

# Parse arguments
CLEAN=false
if [[ "$1" == "--clean" ]]; then
    CLEAN=true
fi

echo -e "${GREEN}Smart Home Light Status Monitor - Linux Build Script${NC}"
echo -e "${GREEN}====================================================${NC}"

BUILD_TYPES=("Debug_Simple" "Debug_Verbose" "Debug_All" "Release")
TOTAL_BUILDS=${#BUILD_TYPES[@]}
CURRENT_BUILD=0

# Function to check if a command exists
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Verify prerequisites
echo -e "\n${CYAN}Checking prerequisites...${NC}"

if ! command_exists cmake; then
    echo -e "${RED}✗ CMake not found. Please install CMake 3.16 or higher.${NC}"
    echo -e "${YELLOW}  Ubuntu/Debian: sudo apt install cmake${NC}"
    echo -e "${YELLOW}  CentOS/RHEL: sudo yum install cmake${NC}"
    echo -e "${YELLOW}  Fedora: sudo dnf install cmake${NC}"
    exit 1
fi

if ! command_exists gcc && ! command_exists clang++; then
    echo -e "${RED}✗ No suitable compiler found (gcc or clang).${NC}"
    echo -e "${YELLOW}  Ubuntu/Debian: sudo apt install build-essential${NC}"
    echo -e "${YELLOW}  CentOS/RHEL: sudo yum groupinstall 'Development Tools'${NC}"
    echo -e "${YELLOW}  Fedora: sudo dnf groupinstall 'Development Tools'${NC}"
    exit 1
fi

if command_exists gcc; then
    GCC_VERSION=$(gcc -dumpversion | cut -d. -f1)
    echo -e "${GREEN}✓ GCC found: $(gcc --version | head -n1)${NC}"
    if [[ $GCC_VERSION -lt 7 ]]; then
        echo -e "${YELLOW}⚠ Warning: GCC version may be too old. Recommended: 7.0+${NC}"
    fi
fi

CMAKE_VERSION=$(cmake --version | head -n1 | grep -oE '[0-9]+\.[0-9]+' | head -n1)
echo -e "${GREEN}✓ CMake found: $CMAKE_VERSION${NC}"

# Determine number of CPU cores for parallel builds
if command_exists nproc; then
    CORES=$(nproc)
elif command_exists sysctl; then
    CORES=$(sysctl -n hw.ncpu)
else
    CORES=1
fi

echo -e "${GRAY}Using $CORES cores for parallel builds${NC}"

# Clean previous builds if requested
if $CLEAN; then
    echo -e "\n${YELLOW}Cleaning previous builds...${NC}"
    for build_type in "${BUILD_TYPES[@]}"; do
        build_dir="build_$(echo $build_type | tr '[:upper:]' '[:lower:]')"
        if [[ -d "$build_dir" ]]; then
            rm -rf "$build_dir"
            echo -e "${GRAY}Removed $build_dir${NC}"
        fi
    done
fi

# Build each configuration
for build_type in "${BUILD_TYPES[@]}"; do
    ((CURRENT_BUILD++))
    build_dir="build_$(echo $build_type | tr '[:upper:]' '[:lower:]')"
    executable_name="cj_lightsimstatus_code_chal_linux_$(echo $build_type | tr '[:upper:]' '[:lower:]')"
    
    echo -e "\n${CYAN}[$CURRENT_BUILD/$TOTAL_BUILDS] Building $build_type configuration...${NC}"
    echo -e "${GRAY}Build directory: $build_dir${NC}"
    echo -e "${GRAY}Output: $executable_name${NC}"
    
    # Create and navigate to build directory
    mkdir -p "$build_dir"
    cd "$build_dir"
    
    # Configure with CMake
    echo -e "${YELLOW}Configuring...${NC}"
    if ! cmake -DCMAKE_BUILD_TYPE="$build_type" .. > cmake_config.log 2>&1; then
        echo -e "${RED}✗ CMake configuration failed${NC}"
        echo -e "${RED}Check cmake_config.log for details${NC}"
        cd ..
        continue
    fi
    
    # Build
    echo -e "${YELLOW}Building...${NC}"
    if ! make -j"$CORES" > make_build.log 2>&1; then
        echo -e "${RED}✗ Build failed${NC}"
        echo -e "${RED}Check make_build.log for details${NC}"
        cd ..
        continue
    fi
    
    # Verify executable was created
    if [[ -f "$executable_name" ]]; then
        echo -e "${GREEN}✓ Build successful: $executable_name${NC}"
        
        # Show file info
        file_size=$(stat -c%s "$executable_name" 2>/dev/null || stat -f%z "$executable_name" 2>/dev/null || echo "0")
        file_size_kb=$((file_size / 1024))
        echo -e "${GRAY}  Size: ${file_size_kb} KB${NC}"
        echo -e "${GRAY}  Permissions: $(ls -l "$executable_name" | cut -d' ' -f1)${NC}"
        
        # Make executable if not already
        chmod +x "$executable_name"
        
    else
        # Look for executable in subdirectories
        found_exe=$(find . -name "*$build_type*" -type f -executable | head -n1)
        if [[ -n "$found_exe" ]]; then
            echo -e "${GREEN}✓ Build successful: $found_exe${NC}"
        else
            echo -e "${YELLOW}⚠ Warning: Executable not found${NC}"
        fi
    fi
    
    cd ..
done

echo -e "\n${GREEN}====================================================${NC}"
echo -e "${GREEN}Build Summary:${NC}"

# Display final status
success_count=0
for build_type in "${BUILD_TYPES[@]}"; do
    build_dir="build_$(echo $build_type | tr '[:upper:]' '[:lower:]')"
    executable_name="cj_lightsimstatus_code_chal_linux_$(echo $build_type | tr '[:upper:]' '[:lower:]')"
    
    if [[ -f "$build_dir/$executable_name" ]] || find "$build_dir" -name "*$(echo $build_type | tr '[:upper:]' '[:lower:]')*" -type f -executable >/dev/null 2>&1; then
        echo -e "${GREEN}✓ $build_type - SUCCESS${NC}"
        ((success_count++))
    else
        echo -e "${RED}✗ $build_type - FAILED${NC}"
    fi
done

echo -e "\n${CYAN}Built $success_count of ${#BUILD_TYPES[@]} configurations successfully${NC}"

echo -e "\n${CYAN}To run an executable:${NC}"
echo -e "${GRAY}  cd build_release${NC}"
echo -e "${GRAY}  ./cj_lightsimstatus_code_chal_linux_release${NC}"

echo -e "\n${CYAN}Packages created in: build_*/package/${NC}"

# Test run suggestion
echo -e "\n${CYAN}Quick test (if lights API server is running):${NC}"
echo -e "${GRAY}  timeout 5s ./build_release/cj_lightsimstatus_code_chal_linux_release || echo 'Test completed'${NC}"
