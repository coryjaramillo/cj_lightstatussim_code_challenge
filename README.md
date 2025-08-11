# Smart Home Light Status Monitor

A C++14 smart home light monitoring application that provides real-time status tracking of light systems via HTTP API integration.

## Overview

This application continuously monitors smart home lights through an HTTP REST API, detecting and reporting state changes in real-time. It supports multiple debug levels and provides JSON-formatted output for all light states and changes.

### Features

- **Real-time monitoring**: Continuous polling of light status via HTTP API
- **Change detection**: Automatic detection of light state modifications, additions, and removals
- **Multiple debug levels**: Simple, Verbose, and All debug configurations
- **JSON output**: All states and changes formatted as JSON
- **Cross-platform**: Supports both Windows 11 and Linux
- **Brightness conversion**: Automatic conversion from API range (0-255) to percentage (0-100)

## Prerequisites

### Windows 11
- **CMake**: Version 3.16 or higher
- **Visual Studio 2019/2022** with C++ build tools, OR
- **MinGW-w64** with GCC 7.0 or higher
- **Windows SDK**: 10.0.19041.0 or higher

### Linux
- **CMake**: Version 3.16 or higher
- **GCC**: Version 7.0 or higher, OR
- **Clang**: Version 6.0 or higher
- **Build essentials**: `build-essential` package (Ubuntu/Debian) or equivalent

### Installation Commands

#### Windows 11
```cmd
# Using Chocolatey
choco install cmake visualstudio2022buildtools

# Or download from:
# CMake: https://cmake.org/download/
# Visual Studio Build Tools: https://visualstudio.microsoft.com/downloads/
```

#### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install build-essential cmake gcc g++
```

#### Linux (CentOS/RHEL/Fedora)
```bash
# CentOS/RHEL
sudo yum groupinstall "Development Tools"
sudo yum install cmake gcc gcc-c++

# Fedora
sudo dnf groupinstall "Development Tools"
sudo dnf install cmake gcc gcc-c++
```

## Build Types

This project supports four distinct build configurations:

1. **Debug_Simple**: Basic debug output with simple logging
2. **Debug_Verbose**: Detailed debug output with comprehensive logging
3. **Debug_All**: Both simple and verbose debug outputs combined
4. **Release**: Optimized production build with no debug output

## Building Instructions

### Quick Build (Default Release)

#### Windows 11
```cmd
# Clone and navigate to project
git clone <repository-url>
cd cj_lightsimstatus_code_chal

# Create build directory
mkdir build
cd build

# Configure and build (Release by default)
cmake ..
cmake --build . --config Release

# The executable will be: cj_lightsimstatus_code_chal_win11_release.exe
```

#### Linux
```bash
# Clone and navigate to project
git clone <repository-url>
cd cj_lightsimstatus_code_chal

# Create build directory
mkdir build
cd build

# Configure and build (Release by default)
cmake ..
make

# The executable will be: cj_lightsimstatus_code_chal_linux_release
```

### Building All Configurations

#### Windows 11 - All Build Types

**Debug_Simple Build:**
```cmd
mkdir build_debug_simple
cd build_debug_simple
cmake -DCMAKE_BUILD_TYPE=Debug_Simple ..
cmake --build . --config Debug_Simple
cd ..
# Output: cj_lightsimstatus_code_chal_win11_debug_simple.exe
```

**Debug_Verbose Build:**
```cmd
mkdir build_debug_verbose
cd build_debug_verbose
cmake -DCMAKE_BUILD_TYPE=Debug_Verbose ..
cmake --build . --config Debug_Verbose
cd ..
# Output: cj_lightsimstatus_code_chal_win11_debug_verbose.exe
```

**Debug_All Build:**
```cmd
mkdir build_debug_all
cd build_debug_all
cmake -DCMAKE_BUILD_TYPE=Debug_All ..
cmake --build . --config Debug_All
cd ..
# Output: cj_lightsimstatus_code_chal_win11_debug_all.exe
```

**Release Build:**
```cmd
mkdir build_release
cd build_release
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
cd ..
# Output: cj_lightsimstatus_code_chal_win11_release.exe
```

#### Linux - All Build Types

**Debug_Simple Build:**
```bash
mkdir build_debug_simple
cd build_debug_simple
cmake -DCMAKE_BUILD_TYPE=Debug_Simple ..
make
cd ..
# Output: cj_lightsimstatus_code_chal_linux_debug_simple
```

**Debug_Verbose Build:**
```bash
mkdir build_debug_verbose
cd build_debug_verbose
cmake -DCMAKE_BUILD_TYPE=Debug_Verbose ..
make
cd ..
# Output: cj_lightsimstatus_code_chal_linux_debug_verbose
```

**Debug_All Build:**
```bash
mkdir build_debug_all
cd build_debug_all
cmake -DCMAKE_BUILD_TYPE=Debug_All ..
make
cd ..
# Output: cj_lightsimstatus_code_chal_linux_debug_all
```

**Release Build:**
```bash
mkdir build_release
cd build_release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
cd ..
# Output: cj_lightsimstatus_code_chal_linux_release
```

### Automated Build Script

#### Windows PowerShell Script
Create `build_all.ps1`:
```powershell
# Build all configurations for Windows
$BuildTypes = @("Debug_Simple", "Debug_Verbose", "Debug_All", "Release")

foreach ($BuildType in $BuildTypes) {
    $BuildDir = "build_$($BuildType.ToLower())"
    Write-Host "Building $BuildType configuration..."
    
    New-Item -ItemType Directory -Force -Path $BuildDir
    Set-Location $BuildDir
    
    cmake -DCMAKE_BUILD_TYPE=$BuildType ..
    cmake --build . --config $BuildType
    
    Set-Location ..
    Write-Host "$BuildType build completed.`n"
}
```

#### Linux Bash Script
Create `build_all.sh`:
```bash
#!/bin/bash

# Build all configurations for Linux
BUILD_TYPES=("Debug_Simple" "Debug_Verbose" "Debug_All" "Release")

for build_type in "${BUILD_TYPES[@]}"; do
    build_dir="build_$(echo $build_type | tr '[:upper:]' '[:lower:]')"
    echo "Building $build_type configuration..."
    
    mkdir -p $build_dir
    cd $build_dir
    
    cmake -DCMAKE_BUILD_TYPE=$build_type ..
    make -j$(nproc)
    
    cd ..
    echo "$build_type build completed."
    echo
done
```

Make executable and run:
```bash
chmod +x build_all.sh
./build_all.sh
```

## Running the Application

### Prerequisites for Running
Ensure you have a lights API server running on `localhost:8080` or modify the host/port in the source code.

### Windows 11
```cmd
# Navigate to build directory and run
cd build_release
.\cj_lightsimstatus_code_chal_win11_release.exe

# Or run from any directory (if in PATH)
cj_lightsimstatus_code_chal_win11_release.exe
```

### Linux
```bash
# Navigate to build directory and run
cd build_release
./cj_lightsimstatus_code_chal_linux_release

# Or make executable globally accessible
sudo cp cj_lightsimstatus_code_chal_linux_release /usr/local/bin/
cj_lightsimstatus_code_chal_linux_release
```

## Package Generation

The build system automatically creates deployment packages in the `build/package/` directory containing:
- The executable
- This README file
- Any required runtime dependencies

### Package Structure
```
package/
└── cj_lightsimstatus_code_chal_[platform]_[buildtype]/
    ├── cj_lightsimstatus_code_chal_[platform]_[buildtype][.exe]
    └── README.md
```

Example package names:
- `cj_lightsimstatus_code_chal_win11_release/`
- `cj_lightsimstatus_code_chal_linux_debug_all/`

## Dependencies

### Third-Party Libraries (Header-Only, Included)
- **nlohmann/json**: JSON parsing and serialization
- **httplib**: HTTP client functionality

### System Dependencies
- **Windows**: ws2_32.lib (Windows Sockets)
- **Linux**: pthreads, libdl

## Troubleshooting

### Common Issues

#### Windows Build Issues
```cmd
# Error: MSVC not found
# Solution: Install Visual Studio Build Tools
# Download from: https://visualstudio.microsoft.com/downloads/

# Error: CMake version too old
# Solution: Update CMake
choco upgrade cmake
```

#### Linux Build Issues
```bash
# Error: compiler not found
sudo apt install build-essential

# Error: CMake version too old
# Ubuntu 18.04/20.04: Install from CMake official repository
wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
sudo apt-add-repository 'deb https://apt.kitware.com/ubuntu/ focal main'
sudo apt update
sudo apt install cmake
```

#### Runtime Issues
```bash
# Error: Connection refused
# Solution: Ensure lights API server is running on localhost:8080

# Error: Permission denied (Linux)
chmod +x cj_lightsimstatus_code_chal_linux_*

# Error: Library not found (Linux)
ldd cj_lightsimstatus_code_chal_linux_release  # Check dependencies
```

## Development

### Project Structure
```
├── CMakeLists.txt              # Build configuration
├── README.md                   # This file
├── main.cpp                    # Application entry point
├── src/
│   └── HomeLights.cpp          # Main implementation
├── includes/
│   └── cj_lightsimstatus_code_chal/
│       └── HomeLights.h        # Header files
└── external/                   # Third-party libraries
    ├── httplib.h
    ├── json.hpp
    └── json_fwd.hpp
```

### Debug Output Levels

**DEBUG_BUILD_SIMPLE**: Basic status messages
```cpp
#ifdef DEBUG_BUILD_SIMPLE
    std::cout << "CHANGE CAPTURED..." << std::endl;
    std::cout << "Sleeping for 100 milliseconds..." << std::endl;
#endif
```

**DEBUG_BUILD_VERBOSE**: Detailed operational information (defined in HomeLights.cpp)

**DEBUG_BUILD_ALL**: Both simple and verbose output combined

### API Integration
The application expects a REST API endpoint at `/lights` that returns JSON data in the following format:
```json
[
  {
    "id": 1,
    "name": "Living Room Light",
    "room": "Living Room",
    "on": true,
    "brightness": 128
  }
]
```

## License

This project is a coding challenge implementation. Please refer to your organization's licensing requirements.

## Support

For build issues or questions, please:
1. Check the troubleshooting section above
2. Verify all prerequisites are installed
3. Ensure you're using the correct build commands for your platform
4. Review CMake configuration messages for any warnings or errors
