# Quick Start Build Guide

## TL;DR - Get Building Fast!

### Linux
```bash
# One-liner for all builds
./build_all_linux.sh

# Or use Python (cross-platform)
python3 build_all.py

# Or use Makefile
make all

# Just build release
make
```

### Windows
```powershell
# PowerShell script for all builds
.\build_all_windows.ps1

# Or use Python (cross-platform)
python build_all.py
```

## Quick Commands

| Command | Description |
|---------|-------------|
| `make` | Build release (Linux) |
| `make all` | Build all configurations (Linux) |
| `python3 build_all.py` | Cross-platform build all |
| `python3 build_all.py --config Release` | Build specific config |
| `./build_all_linux.sh --clean` | Clean and build (Linux) |
| `make clean` | Clean builds (Linux) |

## Executables Created

- **Linux Release**: `build_release/cj_lightsimstatus_code_chal_linux_release`
- **Linux Debug Simple**: `build_debug_simple/cj_lightsimstatus_code_chal_linux_debug_simple`
- **Linux Debug Verbose**: `build_debug_verbose/cj_lightsimstatus_code_chal_linux_debug_verbose`
- **Linux Debug All**: `build_debug_all/cj_lightsimstatus_code_chal_linux_debug_all`

- **Windows Release**: `build_release/cj_lightsimstatus_code_chal_win11_release.exe`
- **Windows Debug Simple**: `build_debug_simple/cj_lightsimstatus_code_chal_win11_debug_simple.exe`
- **Windows Debug Verbose**: `build_debug_verbose/cj_lightsimstatus_code_chal_win11_debug_verbose.exe`
- **Windows Debug All**: `build_debug_all/cj_lightsimstatus_code_chal_win11_debug_all.exe`

## Packages

Each build creates a package in `build_*/package/[executable_name]/` containing:
- The executable
- README.md
- All necessary runtime dependencies

## Prerequisites

### Linux
```bash
sudo apt install build-essential cmake  # Ubuntu/Debian
```

### Windows
- Visual Studio Build Tools 2019/2022 OR MinGW-w64
- CMake 3.16+

## Running

```bash
# Linux
./build_release/cj_lightsimstatus_code_chal_linux_release

# Windows
.\build_release\cj_lightsimstatus_code_chal_win11_release.exe
```

**Note**: Requires a lights API server running on localhost:8080

See [README.md](README.md) for complete documentation.
