@echo off
REM Simple test runner script for HomeLights C++ project (Windows)

setlocal EnableDelayedExpansion

set "PROJECT_ROOT=%~dp0"
set "BUILD_DIR=%PROJECT_ROOT%build"

echo HomeLights Test Runner (Windows)
echo =================================

REM Parse command line arguments
set "CLEAN=false"
set "BUILD_TYPE=Debug"
set "RUN_UNIT=true"
set "RUN_INTEGRATION=true"
set "USE_CTEST=false"

:parse_args
if "%~1"=="" goto after_args
if "%~1"=="--clean" (
    set "CLEAN=true"
    goto next_arg
)
if "%~1"=="--release" (
    set "BUILD_TYPE=Release"
    goto next_arg
)
if "%~1"=="--unit-only" (
    set "RUN_INTEGRATION=false"
    goto next_arg
)
if "%~1"=="--integration-only" (
    set "RUN_UNIT=false"
    goto next_arg
)
if "%~1"=="--ctest" (
    set "USE_CTEST=true"
    goto next_arg
)
if "%~1"=="--help" (
    echo Usage: %~nx0 [OPTIONS]
    echo Options:
    echo   --clean             Clean build directory
    echo   --release           Build in Release mode ^(default: Debug^)
    echo   --unit-only         Run only unit tests
    echo   --integration-only  Run only integration tests
    echo   --ctest             Use CTest to run tests
    echo   --help              Show this help
    exit /b 0
)
echo Unknown option: %~1
echo Use --help for usage information
exit /b 1

:next_arg
shift
goto parse_args

:after_args

cd /d "%PROJECT_ROOT%"

REM Clean if requested
if "%CLEAN%"=="true" (
    echo Cleaning build directory...
    if exist "%BUILD_DIR%" rmdir /s /q "%BUILD_DIR%"
)

REM Create and configure build
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd /d "%BUILD_DIR%"

echo Configuring CMake...
cmake .. -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DBUILD_TESTS=ON
if errorlevel 1 (
    echo CMake configuration failed!
    exit /b 1
)

echo Building project...
cmake --build .
if errorlevel 1 (
    echo Build failed!
    exit /b 1
)

echo.
echo Build completed successfully!
echo.

REM Run tests
if "%USE_CTEST%"=="true" (
    echo Running tests with CTest...
    echo ==========================
    ctest --verbose
) else (
    if "%RUN_UNIT%"=="true" (
        echo Running Unit Tests...
        echo ====================
        tests\HomeLightsTests.exe
        if errorlevel 1 (
            echo Unit tests failed!
            exit /b 1
        )
        echo.
    )
    
    if "%RUN_INTEGRATION%"=="true" (
        echo Running Integration Tests...
        echo ===========================
        tests\IntegrationTests.exe
        if errorlevel 1 (
            echo Integration tests failed!
            exit /b 1
        )
        echo.
    )
)

echo All tests completed successfully!
