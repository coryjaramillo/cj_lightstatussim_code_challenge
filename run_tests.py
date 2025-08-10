#!/usr/bin/env python3
"""
Test runner script for HomeLights C++ project
Builds and runs all unit tests and integration tests
"""

import os
import subprocess
import sys
import argparse
from pathlib import Path

def run_command(cmd, cwd=None, capture_output=False):
    """Run a shell command and return the result"""
    try:
        if capture_output:
            result = subprocess.run(cmd, shell=True, cwd=cwd, capture_output=True, text=True)
            return result.returncode, result.stdout, result.stderr
        else:
            result = subprocess.run(cmd, shell=True, cwd=cwd)
            return result.returncode, "", ""
    except Exception as e:
        print(f"Error running command '{cmd}': {e}")
        return 1, "", str(e)

def build_project(build_dir, build_type="Debug", clean=False):
    """Build the project with tests enabled"""
    
    print(f"Building project in {build_type} mode...")
    
    # Create build directory if it doesn't exist
    os.makedirs(build_dir, exist_ok=True)
    
    # Clean build if requested
    if clean and os.path.exists(build_dir):
        print("Cleaning previous build...")
        returncode, _, _ = run_command(f"rm -rf {build_dir}/*", cwd=".")
        if returncode != 0:
            print("Warning: Could not clean build directory")
    
    # Configure CMake
    cmake_cmd = f"cmake .. -DCMAKE_BUILD_TYPE={build_type} -DBUILD_TESTS=ON"
    print(f"Running: {cmake_cmd}")
    returncode, stdout, stderr = run_command(cmake_cmd, cwd=build_dir, capture_output=True)
    
    if returncode != 0:
        print(f"CMake configuration failed!")
        print(f"stdout: {stdout}")
        print(f"stderr: {stderr}")
        return False
    
    # Build the project
    build_cmd = "cmake --build ."
    print(f"Running: {build_cmd}")
    returncode, stdout, stderr = run_command(build_cmd, cwd=build_dir, capture_output=True)
    
    if returncode != 0:
        print(f"Build failed!")
        print(f"stdout: {stdout}")
        print(f"stderr: {stderr}")
        return False
    
    print("Build completed successfully!")
    return True

def run_unit_tests(build_dir):
    """Run unit tests"""
    print("\n" + "="*50)
    print("RUNNING UNIT TESTS")
    print("="*50)
    
    test_executable = os.path.join(".", build_dir, "tests", "HomeLightsTests")
    
    if not os.path.exists(test_executable):
        print(f"Unit test executable not found at {test_executable}")
        return False
    
    returncode, _, _ = run_command(test_executable, cwd=".")
    return returncode == 0

def run_integration_tests(build_dir):
    """Run integration tests"""
    print("\n" + "="*50)
    print("RUNNING INTEGRATION TESTS")
    print("="*50)
    
    test_executable = os.path.join(".", build_dir, "tests", "IntegrationTests")
    
    if not os.path.exists(test_executable):
        print(f"Integration test executable not found at {test_executable}")
        return False
    
    returncode, _, _ = run_command(test_executable, cwd=".")
    return returncode == 0

def run_ctest(build_dir):
    """Run all tests using CTest"""
    print("\n" + "="*50)
    print("RUNNING TESTS WITH CTEST")
    print("="*50)
    
    ctest_cmd = "ctest --verbose"
    returncode, stdout, stderr = run_command(ctest_cmd, cwd=build_dir, capture_output=True)
    
    print(stdout)
    if stderr:
        print("STDERR:", stderr)
    
    return returncode == 0

def main():
    parser = argparse.ArgumentParser(description="Build and run HomeLights tests")
    parser.add_argument("--build-type", choices=["Debug", "Release"], default="Debug",
                       help="Build type (Debug or Release)")
    parser.add_argument("--build-dir", default="build", 
                       help="Build directory (default: build)")
    parser.add_argument("--clean", action="store_true",
                       help="Clean build directory before building")
    parser.add_argument("--unit-only", action="store_true",
                       help="Run only unit tests")
    parser.add_argument("--integration-only", action="store_true", 
                       help="Run only integration tests")
    parser.add_argument("--no-build", action="store_true",
                       help="Skip build step and run tests directly")
    parser.add_argument("--ctest", action="store_true",
                       help="Use CTest to run tests")
    
    args = parser.parse_args()
    
    # Get project root directory
    project_root = Path(__file__).parent
    os.chdir(project_root)
    
    build_dir = args.build_dir
    
    # Build project unless skipped
    if not args.no_build:
        if not build_project(build_dir, args.build_type, args.clean):
            print("Build failed, exiting...")
            sys.exit(1)
    
    # Run tests
    success = True
    
    if args.ctest:
        success = run_ctest(build_dir)
    else:
        if not args.integration_only:
            unit_success = run_unit_tests(build_dir)
            success = success and unit_success
        
        if not args.unit_only:
            integration_success = run_integration_tests(build_dir)
            success = success and integration_success
    
    # Print final result
    print("\n" + "="*50)
    if success:
        print("ALL TESTS PASSED!")
        print("="*50)
        sys.exit(0)
    else:
        print("SOME TESTS FAILED!")
        print("="*50)
        sys.exit(1)

if __name__ == "__main__":
    main()
