# CMakeLists.txt for unit tests

cmake_minimum_required(VERSION 3.31)

# Set up test executable
add_executable(HomeLightsTests
    HomeLightsTests.cpp
    ../src/HomeLights.cpp
)

target_include_directories(HomeLightsTests PRIVATE
    ${CMAKE_SOURCE_DIR}/includes/cj_lightsimstatus_code_chal
    ${CMAKE_SOURCE_DIR}/external
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Use the same C++ standard as the main project
set_property(TARGET HomeLightsTests PROPERTY CXX_STANDARD 14)

# Add the same compile definitions as the main project
target_compile_definitions(HomeLightsTests PUBLIC _WIN32_WINNT=0x0A00)

# Link the same libraries as the main project
target_link_libraries(HomeLightsTests PRIVATE ws2_32)

# Add debug build definitions for testing
target_compile_definitions(HomeLightsTests PRIVATE 
    -DDEBUG_BUILD_SIMPLE
    -DDEBUG_BUILD_VERBOSE
)

# Set up integration test executable
add_executable(IntegrationTests
    IntegrationTests.cpp
    ../src/HomeLights.cpp
)

target_include_directories(IntegrationTests PRIVATE
    ${CMAKE_SOURCE_DIR}/includes/cj_lightsimstatus_code_chal
    ${CMAKE_SOURCE_DIR}/external
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Use the same C++ standard as the main project
set_property(TARGET IntegrationTests PROPERTY CXX_STANDARD 14)

# Add the same compile definitions as the main project
target_compile_definitions(IntegrationTests PUBLIC _WIN32_WINNT=0x0A00)

# Link the same libraries as the main project
target_link_libraries(IntegrationTests PRIVATE ws2_32)

# Register tests with CTest
add_test(NAME HomeLightsUnitTests COMMAND HomeLightsTests)
add_test(NAME HomeLightsIntegrationTests COMMAND IntegrationTests)
