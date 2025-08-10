# HomeLights Unit Tests

This directory contains unit tests for the HomeLights smart home lighting monitoring system.

## Test Structure

### Files

- **`TestFramework.h`**: Lightweight C++ unit testing framework
- **`MockHomeLights.h`**: Mock class extending HomeLights for testable functionality
- **`HomeLightsTests.cpp`**: Main test suite with comprehensive test cases
- **`CMakeLists.txt`**: CMake configuration for building tests

### Test Categories

#### 1. Constructor Tests
- Valid host and port initialization
- Empty host handling

#### 2. Brightness Conversion Tests
- API value (0-255) to percentage (0-100) conversion
- Percentage to API value conversion
- Edge cases: min, max, and middle values
- Proper rounding behavior

#### 3. Queue Management Tests  
- Initial empty state verification
- Adding and retrieving changes
- Multiple changes handling
- FIFO queue behavior

#### 4. Light Data Processing Tests
- Valid JSON response handling
- Empty JSON response handling
- Invalid/missing JSON keys handling

#### 5. Change Detection Tests
- No changes detection
- Brightness change detection
- On/off toggle detection
- New light addition
- Light removal detection

#### 6. Edge Case Tests
- Empty light data handling
- Missing required keys
- Exception handling

## Building and Running Tests

### Prerequisites
- CMake 3.31 or higher
- C++14 compatible compiler
- All dependencies from main project (nlohmann/json, httplib)

### Build Commands

```bash
# From project root directory
mkdir build && cd build
cmake ..
cmake --build . --target HomeLightsTests

# Or alternatively, build all targets including tests
cmake --build .
```

### Running Tests

```bash
# Run tests directly
./tests/HomeLightsTests

# Or use CTest for integrated testing
ctest --test-dir . --verbose
```

### Expected Output

The test framework provides detailed output showing:
- Individual test results (PASSED/FAILED)
- Failure reasons with specific assertion details
- Overall test summary with statistics
- Success rate percentage

## Test Implementation Details

### Mock Strategy
The tests use a `MockHomeLights` class that extends the original `HomeLights` class to:
- Expose protected methods for testing
- Provide access to private member variables
- Allow direct manipulation of internal state
- Wrap private static methods for testing

### Testing Philosophy
- **Unit-focused**: Each test focuses on a single piece of functionality
- **Isolated**: Tests don't depend on external services or network connections
- **Comprehensive**: Covers normal cases, edge cases, and error conditions
- **Maintainable**: Clear test names and documentation

### Limitations
- HTTP client functionality is not fully mocked (requires actual server for integration testing)
- Some tests focus on state manipulation rather than actual API calls
- Exception testing is limited to basic scenarios

## Adding New Tests

To add new tests:

1. Add test method to `HomeLightsTests` class
2. Register test in `runAllTests()` method using `testFramework.addTest()`
3. Follow naming convention: `test_Category_SpecificCase()`
4. Use assertion macros: `ASSERT_TRUE`, `ASSERT_EQ`, `ASSERT_STREQ`, etc.
5. Document expected behavior in comments

## Test Configuration

Tests are built with debug symbols enabled and include:
- `DEBUG_BUILD_SIMPLE` definition for basic debug output
- `DEBUG_BUILD_VERBOSE` definition for detailed debug output
- Same compiler flags and dependencies as main project

The test build can be disabled by setting `-DBUILD_TESTS=OFF` when configuring CMake.
