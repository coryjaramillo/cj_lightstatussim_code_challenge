# HomeLights - Smart Home Lighting Monitor

A C++14 application for monitoring and tracking changes in a smart home lighting system through HTTP REST API communication.

## Features

- **Real-time Light Monitoring**: Continuously polls smart lighting system for state changes
- **Change Detection**: Detects and reports only modified light states in JSON format
- **Light Management**: Handles addition and removal of lights from the system  
- **Brightness Conversion**: Converts API brightness values (0-255) to user-friendly percentages (0-100)
- **Error Handling**: Graceful handling of connection errors and malformed JSON responses
- **Debug Support**: Multiple debug build configurations for development

## Architecture

- **Core Class**: `HomeLights` class handles all lighting system interactions
- **HTTP Communication**: Uses httplib for REST API communication with lighting server
- **JSON Processing**: Leverages nlohmann/json for parsing and serializing data
- **Queue-based Changes**: Efficient change detection using queue-based processing
- **Object-oriented Design**: Clean, maintainable C++14 implementation

## Prerequisites

- **CMake 3.31+** for build configuration
- **C++14 compatible compiler** (GCC, Clang, MSVC)
- **64-bit platform** (required for Windows builds)
- **Windows**: Links with ws2_32 library for networking

## Dependencies

All dependencies are included in the `external/` directory:
- `nlohmann/json` - JSON library for parsing and serialization
- `httplib` - HTTP client library for API communication

## Building

### Standard Build
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### Debug Builds
```bash
# Simple debug output
cmake .. -DCMAKE_BUILD_TYPE=Debug_Simple

# Verbose debug output  
cmake .. -DCMAKE_BUILD_TYPE=Debug_Verbose

# All debug output
cmake .. -DCMAKE_BUILD_TYPE=Debug_All
```

### Release Build
```bash
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

## Usage

The application connects to a smart lighting HTTP server and monitors for changes:

```bash
./cj_lightsimstatus_code_chal
```

### Expected Server Endpoints

- `GET /lights` - Returns array of all lights with basic info
- `GET /lights/{id}` - Returns detailed state for specific light

### Output Format

**Initial startup** - displays all lights:
```json
[
  {
    "id": "1",
    "name": "Living Room",
    "room": "living_room", 
    "on": true,
    "brightness": 78
  }
]
```

**Change detection** - displays only modifications:
```json
{
  "id": "1",
  "brightness": 95
}
```

**New light discovered**:
```json
{
  "id": "3",
  "name": "Kitchen",
  "room": "kitchen",
  "on": false,
  "brightness": 0
}
```

**Light removed**:
```
Kitchen (2) has been removed
```

## Testing

The project includes comprehensive unit tests and integration tests.

### Quick Test Run
```bash
# Run all tests
./run_tests.sh

# Or use Python script
python3 run_tests.py
```

### Test Categories
- **Unit Tests**: Core functionality, brightness conversion, change detection
- **Integration Tests**: HTTP communication with mock server
- **Edge Cases**: Error handling, malformed data, connection failures

### Manual Test Commands
```bash
# Build with tests enabled
cmake .. -DBUILD_TESTS=ON
cmake --build .

# Run unit tests
./tests/HomeLightsTests

# Run integration tests  
./tests/IntegrationTests

# Run with CTest
ctest --verbose
```

See [tests/README.md](tests/README.md) for detailed testing documentation.

## Configuration

### Server Connection
Default connection: `localhost:8080`

To modify, update the `main.cpp` file:
```cpp
std::string currentHost = "your-server";
int currentPort = 8080;
```

### Debug Output Control
Control debug verbosity with build type:
- `Debug_Simple`: Basic operation logging
- `Debug_Verbose`: Detailed internal state logging  
- `Debug_All`: All debug output enabled

## Project Structure

```
├── main.cpp                 # Application entry point
├── src/
│   └── HomeLights.cpp      # Core implementation
├── includes/
│   └── cj_lightsimstatus_code_chal/
│       └── HomeLights.h    # Class definition
├── external/               # Third-party libraries
│   ├── json.hpp           # nlohmann JSON library
│   ├── json_fwd.hpp       # JSON forward declarations
│   └── httplib.h          # HTTP client library
├── tests/                 # Unit and integration tests
│   ├── TestFramework.h    # Lightweight test framework
│   ├── MockHomeLights.h   # Mock class for testing
│   ├── HomeLightsTests.cpp # Unit test suite
│   ├── IntegrationTests.cpp # Integration test suite
│   └── README.md          # Testing documentation
├── CMakeLists.txt         # Build configuration
├── run_tests.sh           # Test runner script (Bash)
├── run_tests.py           # Test runner script (Python)
└── README.md              # This file
```

## Development

### Adding New Features
1. Implement functionality in `HomeLights` class
2. Add corresponding unit tests in `tests/HomeLightsTests.cpp`
3. Update integration tests if HTTP API changes
4. Document changes in appropriate README files

### Code Style
- Follow existing naming conventions
- Use descriptive variable and method names
- Include error handling for network operations
- Add debug output for development builds

### Build Types
- **Release**: Optimized build for production use
- **Debug**: Standard debug build with symbols
- **Debug_Simple**: Debug with basic logging
- **Debug_Verbose**: Debug with detailed logging
- **Debug_All**: Debug with all logging enabled

## Troubleshooting

### Common Issues

**Build Errors**:
- Ensure CMake 3.31+ is installed
- Verify C++14 compiler availability
- Check that all dependencies are present in `external/`

**Runtime Connection Issues**:
- Verify lighting server is running on specified host/port
- Check firewall settings for network connectivity
- Enable debug build to see connection details

**JSON Parsing Errors**:  
- Verify server returns valid JSON responses
- Check API endpoint compatibility
- Enable verbose debug to see raw server responses

### Debug Builds
Use debug builds to troubleshoot issues:
```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug_Verbose
cmake --build .
./cj_lightsimstatus_code_chal
```

## License

This project is a coding challenge implementation for smart home lighting system monitoring.
