#!/bin/bash
# Simple test runner script for HomeLights C++ project

set -e  # Exit on any error

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${PROJECT_ROOT}/build"

echo "HomeLights Test Runner"
echo "====================="

# Parse command line arguments
CLEAN=false
BUILD_TYPE="Debug"
RUN_UNIT=true
RUN_INTEGRATION=true
USE_CTEST=false

while [[ $# -gt 0 ]]; do
    case $1 in
        --clean)
            CLEAN=true
            shift
            ;;
        --release)
            BUILD_TYPE="Release"
            shift
            ;;
        --unit-only)
            RUN_INTEGRATION=false
            shift
            ;;
        --integration-only)
            RUN_UNIT=false
            shift
            ;;
        --ctest)
            USE_CTEST=true
            shift
            ;;
        --help)
            echo "Usage: $0 [OPTIONS]"
            echo "Options:"
            echo "  --clean             Clean build directory"
            echo "  --release           Build in Release mode (default: Debug)"
            echo "  --unit-only         Run only unit tests"
            echo "  --integration-only  Run only integration tests"
            echo "  --ctest             Use CTest to run tests"
            echo "  --help              Show this help"
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            echo "Use --help for usage information"
            exit 1
            ;;
    esac
done

cd "$PROJECT_ROOT"

# Clean if requested
if [ "$CLEAN" = true ]; then
    echo "Cleaning build directory..."
    rm -rf "$BUILD_DIR"
fi

# Create and configure build
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

echo "Configuring CMake..."
cmake .. -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DBUILD_TESTS=ON

echo "Building project..."
cmake --build .

echo ""
echo "Build completed successfully!"
echo ""

# Run tests
if [ "$USE_CTEST" = true ]; then
    echo "Running tests with CTest..."
    echo "=========================="
    ctest --verbose
else
    if [ "$RUN_UNIT" = true ]; then
        echo "Running Unit Tests..."
        echo "===================="
        ./tests/HomeLightsTests
        echo ""
    fi
    
    if [ "$RUN_INTEGRATION" = true ]; then
        echo "Running Integration Tests..."
        echo "==========================="
        ./tests/IntegrationTests
        echo ""
    fi
fi

echo "All tests completed!"
