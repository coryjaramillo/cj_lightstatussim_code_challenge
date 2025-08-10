# HomeLights Testing Guide for Windows 11

This project now includes full Windows 11 support for building and running unit tests and integration tests.

## Test Runner Options

The project provides multiple ways to run tests on Windows 11:

### 1. Windows Batch File (run_tests.bat)
The simplest option - a traditional Windows batch file:

```cmd
# Run all tests
run_tests.bat

# Available options:
run_tests.bat --clean              # Clean build directory first
run_tests.bat --release            # Build in Release mode
run_tests.bat --unit-only          # Run only unit tests  
run_tests.bat --integration-only   # Run only integration tests
run_tests.bat --ctest              # Use CTest to run tests
run_tests.bat --help               # Show help
```

### 2. PowerShell Script (run_tests.ps1)
A more modern PowerShell approach with better error handling:

```powershell
# Run all tests
.\run_tests.ps1

# Available options:
.\run_tests.ps1 -Clean              # Clean build directory first
.\run_tests.ps1 -Release            # Build in Release mode  
.\run_tests.ps1 -UnitOnly           # Run only unit tests
.\run_tests.ps1 -IntegrationOnly    # Run only integration tests
.\run_tests.ps1 -CTest              # Use CTest to run tests
.\run_tests.ps1 -Help               # Show help
```

**Note**: If PowerShell execution policy prevents running scripts, you may need to run:
```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

### 3. Cross-Platform Python Script (run_tests.py)
Updated to work on both Windows and Linux:

```cmd
# Run all tests
python run_tests.py

# Available options:
python run_tests.py --build-type Debug|Release
python run_tests.py --clean
python run_tests.py --unit-only
python run_tests.py --integration-only
python run_tests.py --no-build          # Skip build, run tests only
python run_tests.py --ctest
```

### 4. Manual CMake Build
For developers who prefer manual control:

```cmd
# Create and enter build directory
mkdir build
cd build

# Configure with tests enabled
cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON

# Build
cmake --build .

# Run tests individually
tests\HomeLightsTests.exe
tests\IntegrationTests.exe

# Or use CTest
ctest --verbose
```

## Prerequisites

- **Windows 11** (64-bit)
- **CMake 3.31+** 
- **C++14 compatible compiler** (Visual Studio 2017+, MinGW-w64, or Clang)
- **Python 3.6+** (only if using Python test runner)

## Key Windows-Specific Improvements

1. **Executable Extensions**: All test runners now correctly look for `.exe` files on Windows
2. **Path Handling**: Uses Windows-style backslashes and proper path joining
3. **Cross-Platform File Operations**: Replaced Unix `rm -rf` with Python's `shutil.rmtree()`
4. **Error Handling**: Proper Windows exit codes and error detection
5. **Multiple Script Types**: Batch, PowerShell, and Python options for different preferences

## Project Structure

```
HomeLights/
├── run_tests.bat           # Windows batch script
├── run_tests.ps1           # PowerShell script  
├── run_tests.py            # Cross-platform Python script
├── run_tests.sh            # Linux bash script (original)
├── CMakeLists.txt          # Updated with test support
├── tests/
│   ├── CMakeLists.txt      # Test configuration
│   ├── TestFramework.h     # Lightweight test framework
│   ├── MockHomeLights.h    # Mock class for testing
│   ├── HomeLightsTests.cpp # Unit tests (21 tests)
│   ├── IntegrationTests.cpp# Integration tests (3 tests)
│   └── README.md           # Detailed test documentation
└── build/                  # Build directory (created automatically)
    └── tests/
        ├── HomeLightsTests.exe    # Unit test executable
        └── IntegrationTests.exe   # Integration test executable
```

## Test Coverage

- **21 Unit Tests**: Constructor, brightness conversion, change detection, queue management, edge cases
- **3 Integration Tests**: Basic functionality without external dependencies  
- **100% Pass Rate**: All tests pass on Windows 11

## Troubleshooting

### Common Issues

1. **CMake Version**: Ensure CMake 3.31+ is installed
2. **Compiler Path**: Make sure your C++ compiler is in system PATH
3. **Build Fails**: Try cleaning build directory with `--clean` flag
4. **PowerShell Scripts Disabled**: Run `Set-ExecutionPolicy RemoteSigned -Scope CurrentUser`

### Build Modes

- **Debug** (default): Includes debug symbols and verbose output
- **Release**: Optimized build for performance testing

## Integration with Development Workflow

All test runners automatically:
1. Configure CMake with proper Windows settings
2. Build both main project and tests
3. Run tests and report results
4. Exit with appropriate error codes for CI/CD integration

Choose the test runner that best fits your Windows development environment!
