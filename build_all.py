#!/usr/bin/env python3
"""
Cross-platform build script for Smart Home Light Status Monitor
Supports Windows 11 and Linux builds with all configurations

Usage:
    python build_all.py [--clean] [--config CONFIG] [--help]

Options:
    --clean     Clean previous builds before building
    --config    Build specific configuration only (Debug_Simple, Debug_Verbose, Debug_All, Release)
    --help      Show this help message
"""

import os
import sys
import subprocess
import platform
import argparse
import shutil
from pathlib import Path

class Colors:
    """ANSI color codes for terminal output"""
    RED = '\033[0;31m'
    GREEN = '\033[0;32m'
    YELLOW = '\033[1;33m'
    CYAN = '\033[0;36m'
    GRAY = '\033[0;37m'
    BOLD = '\033[1m'
    NC = '\033[0m'  # No Color
    
    @staticmethod
    def colorize(text, color):
        """Colorize text for terminal output"""
        if platform.system() == 'Windows' and not os.environ.get('FORCE_COLOR'):
            return text  # Windows terminal may not support colors
        return f"{color}{text}{Colors.NC}"

def print_header(text):
    """Print a colored header"""
    print(Colors.colorize(text, Colors.GREEN + Colors.BOLD))
    print(Colors.colorize("=" * len(text), Colors.GREEN))

def print_info(text):
    """Print info message in cyan"""
    print(Colors.colorize(text, Colors.CYAN))

def print_success(text):
    """Print success message in green"""
    print(Colors.colorize(f"✓ {text}", Colors.GREEN))

def print_warning(text):
    """Print warning message in yellow"""
    print(Colors.colorize(f"⚠ {text}", Colors.YELLOW))

def print_error(text):
    """Print error message in red"""
    print(Colors.colorize(f"✗ {text}", Colors.RED))

def print_gray(text):
    """Print gray text"""
    print(Colors.colorize(text, Colors.GRAY))

def detect_platform():
    """Detect the current platform"""
    system = platform.system().lower()
    if system == 'windows':
        return 'windows'
    elif system == 'linux':
        return 'linux'
    elif system == 'darwin':
        return 'macos'
    else:
        return 'unknown'

def check_prerequisites():
    """Check if required tools are installed"""
    print_info("Checking prerequisites...")
    
    # Check CMake
    try:
        result = subprocess.run(['cmake', '--version'], 
                              capture_output=True, text=True, check=True)
        version_line = result.stdout.split('\n')[0]
        print_success(f"CMake found: {version_line}")
    except (subprocess.CalledProcessError, FileNotFoundError):
        print_error("CMake not found. Please install CMake 3.16 or higher.")
        return False
    
    current_platform = detect_platform()
    
    # Check compiler
    if current_platform == 'windows':
        # Try to find MSVC or MinGW
        try:
            subprocess.run(['cl'], capture_output=True, check=True)
            print_success("MSVC compiler found")
        except (subprocess.CalledProcessError, FileNotFoundError):
            try:
                result = subprocess.run(['gcc', '--version'], 
                                      capture_output=True, text=True, check=True)
                version_line = result.stdout.split('\n')[0]
                print_success(f"GCC found: {version_line}")
            except (subprocess.CalledProcessError, FileNotFoundError):
                print_error("No suitable compiler found. Please install Visual Studio Build Tools or MinGW.")
                return False
    else:
        # Check for GCC or Clang on Linux/macOS
        compiler_found = False
        for compiler in ['gcc', 'clang++']:
            try:
                result = subprocess.run([compiler, '--version'], 
                                      capture_output=True, text=True, check=True)
                version_line = result.stdout.split('\n')[0]
                print_success(f"{compiler.upper()} found: {version_line}")
                compiler_found = True
                break
            except (subprocess.CalledProcessError, FileNotFoundError):
                continue
        
        if not compiler_found:
            print_error("No suitable compiler found (gcc or clang).")
            if current_platform == 'linux':
                print_gray("  Ubuntu/Debian: sudo apt install build-essential")
                print_gray("  CentOS/RHEL: sudo yum groupinstall 'Development Tools'")
                print_gray("  Fedora: sudo dnf groupinstall 'Development Tools'")
            return False
    
    return True

def get_cpu_count():
    """Get the number of CPU cores for parallel builds"""
    try:
        return os.cpu_count() or 1
    except:
        return 1

def build_configuration(config, clean=False):
    """Build a specific configuration"""
    current_platform = detect_platform()
    
    # Determine build directory and executable name
    build_dir = f"build_{config.lower()}"
    
    if current_platform == 'windows':
        platform_name = 'win11'
        exe_suffix = '.exe'
    else:
        platform_name = 'linux'
        exe_suffix = ''
    
    executable_name = f"cj_lightsimstatus_code_chal_{platform_name}_{config.lower()}{exe_suffix}"
    
    print_info(f"Building {config} configuration...")
    print_gray(f"Build directory: {build_dir}")
    print_gray(f"Output: {executable_name}")
    
    # Clean if requested
    if clean and os.path.exists(build_dir):
        print_gray(f"Cleaning {build_dir}...")
        shutil.rmtree(build_dir)
    
    # Create build directory
    os.makedirs(build_dir, exist_ok=True)
    
    try:
        # Configure with CMake
        print_gray("Configuring...")
        cmake_cmd = ['cmake', f'-DCMAKE_BUILD_TYPE={config}', '..']
        result = subprocess.run(cmake_cmd, cwd=build_dir, 
                              capture_output=True, text=True, check=True)
        
        # Build
        print_gray("Building...")
        if current_platform == 'windows':
            build_cmd = ['cmake', '--build', '.', '--config', config]
        else:
            build_cmd = ['make', f'-j{get_cpu_count()}']
        
        result = subprocess.run(build_cmd, cwd=build_dir, 
                              capture_output=True, text=True, check=True)
        
        # Verify executable was created
        exe_path = None
        for root, dirs, files in os.walk(build_dir):
            for file in files:
                if file.startswith('cj_lightsimstatus_code_chal') and (
                    file.endswith('.exe') or (exe_suffix == '' and os.access(os.path.join(root, file), os.X_OK))):
                    exe_path = os.path.join(root, file)
                    break
            if exe_path:
                break
        
        if exe_path:
            file_size = os.path.getsize(exe_path)
            file_size_kb = file_size // 1024
            print_success(f"Build successful: {os.path.basename(exe_path)}")
            print_gray(f"  Size: {file_size_kb} KB")
            return True
        else:
            print_warning("Executable not found after build")
            return False
            
    except subprocess.CalledProcessError as e:
        print_error(f"Build failed for {config}")
        print_gray(f"Error: {e}")
        if e.stderr:
            print_gray(f"stderr: {e.stderr}")
        return False
    except Exception as e:
        print_error(f"Unexpected error building {config}: {e}")
        return False

def main():
    """Main function"""
    parser = argparse.ArgumentParser(
        description="Cross-platform build script for Smart Home Light Status Monitor",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python build_all.py                    # Build all configurations
  python build_all.py --config Release   # Build only Release
  python build_all.py --clean            # Clean and build all
        """
    )
    
    parser.add_argument('--clean', action='store_true',
                       help='Clean previous builds before building')
    parser.add_argument('--config', choices=['Debug_Simple', 'Debug_Verbose', 'Debug_All', 'Release'],
                       help='Build specific configuration only')
    
    args = parser.parse_args()
    
    print_header("Smart Home Light Status Monitor - Cross-Platform Build Script")
    
    # Check prerequisites
    if not check_prerequisites():
        print_error("Prerequisites check failed. Please install required tools.")
        return 1
    
    # Determine configurations to build
    if args.config:
        build_types = [args.config]
    else:
        build_types = ['Debug_Simple', 'Debug_Verbose', 'Debug_All', 'Release']
    
    total_builds = len(build_types)
    successful_builds = 0
    
    # Build each configuration
    for i, build_type in enumerate(build_types, 1):
        print(f"\n[{i}/{total_builds}] {build_type}")
        if build_configuration(build_type, clean=args.clean):
            successful_builds += 1
    
    # Summary
    print_header("Build Summary")
    current_platform = detect_platform()
    
    for build_type in build_types:
        build_dir = f"build_{build_type.lower()}"
        
        if current_platform == 'windows':
            pattern = 'cj_lightsimstatus_code_chal_win11_*.exe'
        else:
            pattern = 'cj_lightsimstatus_code_chal_linux_*'
        
        # Check if executable exists
        found = False
        if os.path.exists(build_dir):
            for root, dirs, files in os.walk(build_dir):
                for file in files:
                    if file.startswith('cj_lightsimstatus_code_chal'):
                        found = True
                        break
                if found:
                    break
        
        if found:
            print_success(f"{build_type} - SUCCESS")
        else:
            print_error(f"{build_type} - FAILED")
    
    print(f"\n{Colors.colorize(f'Built {successful_builds} of {total_builds} configurations successfully', Colors.CYAN)}")
    
    # Usage instructions
    print_info("\nTo run an executable:")
    if current_platform == 'windows':
        print_gray("  cd build_release")
        print_gray("  .\\cj_lightsimstatus_code_chal_win11_release.exe")
    else:
        print_gray("  cd build_release")
        print_gray("  ./cj_lightsimstatus_code_chal_linux_release")
    
    print_info("\nPackages created in: build_*/package/")
    
    return 0 if successful_builds == total_builds else 1

if __name__ == '__main__':
    try:
        sys.exit(main())
    except KeyboardInterrupt:
        print_error("\nBuild interrupted by user")
        sys.exit(1)
    except Exception as e:
        print_error(f"Unexpected error: {e}")
        sys.exit(1)
