# Simple Makefile wrapper for CMake builds
# Smart Home Light Status Monitor
#
# Usage:
#   make                    # Build release version
#   make debug-simple       # Build debug simple version
#   make debug-verbose      # Build debug verbose version  
#   make debug-all          # Build debug all version
#   make all                # Build all configurations
#   make clean              # Clean all build directories
#   make help               # Show this help

.PHONY: all clean help release debug-simple debug-verbose debug-all

# Default target
release: build_release
	@echo "Building Release configuration..."
	@mkdir -p build_release
	@cd build_release && cmake -DCMAKE_BUILD_TYPE=Release .. && make

debug-simple: build_debug_simple
	@echo "Building Debug_Simple configuration..."
	@mkdir -p build_debug_simple
	@cd build_debug_simple && cmake -DCMAKE_BUILD_TYPE=Debug_Simple .. && make

debug-verbose: build_debug_verbose
	@echo "Building Debug_Verbose configuration..."
	@mkdir -p build_debug_verbose
	@cd build_debug_verbose && cmake -DCMAKE_BUILD_TYPE=Debug_Verbose .. && make

debug-all: build_debug_all
	@echo "Building Debug_All configuration..."
	@mkdir -p build_debug_all
	@cd build_debug_all && cmake -DCMAKE_BUILD_TYPE=Debug_All .. && make

# Build all configurations
all: release debug-simple debug-verbose debug-all
	@echo ""
	@echo "All configurations built successfully!"
	@echo ""
	@echo "Executables created:"
	@ls -la build_*/cj_lightsimstatus_code_chal_linux_* 2>/dev/null || echo "  No executables found"
	@echo ""
	@echo "To run:"
	@echo "  ./build_release/cj_lightsimstatus_code_chal_linux_release"

# Create build directories
build_%:
	@mkdir -p $@

# Clean all build directories
clean:
	@echo "Cleaning build directories..."
	@rm -rf build_*
	@echo "Clean complete."

# Show help
help:
	@echo "Smart Home Light Status Monitor - Build System"
	@echo "=============================================="
	@echo ""
	@echo "Available targets:"
	@echo "  make              Build release version (default)"
	@echo "  make release      Build release version"
	@echo "  make debug-simple Build debug simple version"
	@echo "  make debug-verbose Build debug verbose version"
	@echo "  make debug-all    Build debug all version"
	@echo "  make all          Build all configurations"
	@echo "  make clean        Clean all build directories"
	@echo "  make help         Show this help"
	@echo ""
	@echo "Build outputs:"
	@echo "  Release:       build_release/cj_lightsimstatus_code_chal_linux_release"
	@echo "  Debug Simple:  build_debug_simple/cj_lightsimstatus_code_chal_linux_debug_simple"
	@echo "  Debug Verbose: build_debug_verbose/cj_lightsimstatus_code_chal_linux_debug_verbose"
	@echo "  Debug All:     build_debug_all/cj_lightsimstatus_code_chal_linux_debug_all"
	@echo ""
	@echo "Prerequisites:"
	@echo "  - CMake 3.16+"
	@echo "  - GCC 7.0+ or Clang 6.0+"
	@echo "  - Build essentials (make, etc.)"
	@echo ""
	@echo "For Windows builds, use build_all_windows.ps1"

# Make this the default when no target is specified
.DEFAULT_GOAL := release
