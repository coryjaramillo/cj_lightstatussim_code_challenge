cmake_minimum_required(VERSION 3.16)
project(cj_lightsimstatus_code_chal)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Platform detection
if(WIN32)
    set(PLATFORM_NAME "win11")
    set(PLATFORM_SUFFIX ".exe")
elseif(UNIX AND NOT APPLE)
    set(PLATFORM_NAME "linux")
    set(PLATFORM_SUFFIX "")
else()
    set(PLATFORM_NAME "unknown")
    set(PLATFORM_SUFFIX "")
endif()

# Build type configurations
set(CMAKE_CONFIGURATION_TYPES "Debug_Simple;Debug_Verbose;Debug_All;Release" CACHE STRING "" FORCE)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
endif()

# Build type specific flags and definitions
if(CMAKE_BUILD_TYPE STREQUAL "Debug_Simple")
    add_definitions(-DDEBUG_BUILD_SIMPLE)
    set(BUILD_TYPE_SUFFIX "_debug_simple")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug_Verbose")
    add_definitions(-DDEBUG_BUILD_VERBOSE)
    set(BUILD_TYPE_SUFFIX "_debug_verbose")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug_All")
    add_definitions(-DDEBUG_BUILD_VERBOSE -DDEBUG_BUILD_SIMPLE)
    set(BUILD_TYPE_SUFFIX "_debug_all")
else()
    set(BUILD_TYPE_SUFFIX "_release")
endif()

# Create executable with platform and build type in name
set(EXECUTABLE_NAME "${PROJECT_NAME}_${PLATFORM_NAME}${BUILD_TYPE_SUFFIX}${PLATFORM_SUFFIX}")

add_executable(${EXECUTABLE_NAME} 
    main.cpp
    src/HomeLights.cpp
    includes/cj_lightsimstatus_code_chal/HomeLights.h
)

# Platform-specific configurations
if(WIN32)
    # Windows specific settings
    target_compile_definitions(${EXECUTABLE_NAME} PUBLIC _WIN32_WINNT=0x0A00)
    target_compile_definitions(${EXECUTABLE_NAME} PUBLIC WIN32_LEAN_AND_MEAN)
    
    # Force 64-bit build for Windows
    if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
        message(FATAL_ERROR "cpp-httplib and this project require a 64-bit build on Windows.")
    endif()
    
    # Windows libraries
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE ws2_32)
    
    # Enable static linking for Release builds on Windows
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_options(${EXECUTABLE_NAME} PRIVATE $<$<CONFIG:Release>:/MT>)
        target_link_options(${EXECUTABLE_NAME} PRIVATE $<$<CONFIG:Release>:/INCREMENTAL:NO>)
    else()
        target_compile_options(${EXECUTABLE_NAME} PRIVATE $<$<CONFIG:Debug>:/MTd>)
    endif()
    
elseif(UNIX AND NOT APPLE)
    # Linux specific settings
    target_compile_definitions(${EXECUTABLE_NAME} PUBLIC __linux__)
    
    # Linux libraries
    find_package(Threads REQUIRED)
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE Threads::Threads)
    
    # Enable static linking for Release builds on Linux
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_link_options(${EXECUTABLE_NAME} PRIVATE -static-libgcc -static-libstdc++)
    endif()
    
    # Additional Linux libraries that might be needed
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE dl)
endif()

# Include directories
target_include_directories(${EXECUTABLE_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/external
    ${CMAKE_SOURCE_DIR}/includes/${PROJECT_NAME}
)

# Compiler-specific optimizations
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Debug flags
    target_compile_options(${EXECUTABLE_NAME} PRIVATE 
        $<$<CONFIG:Debug>:-g -O0 -Wall -Wextra>
    )
    # Release flags
    target_compile_options(${EXECUTABLE_NAME} PRIVATE 
        $<$<CONFIG:Release>:-O3 -DNDEBUG>
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # MSVC flags
    target_compile_options(${EXECUTABLE_NAME} PRIVATE 
        $<$<CONFIG:Debug>:/Od /Zi /W3>
        $<$<CONFIG:Release>:/O2 /DNDEBUG>
    )
endif()

# Install and packaging
install(TARGETS ${EXECUTABLE_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# Create package directory structure
set(PACKAGE_DIR "${CMAKE_BINARY_DIR}/package")
set(PACKAGE_NAME "${PROJECT_NAME}_${PLATFORM_NAME}${BUILD_TYPE_SUFFIX}")

# Custom target for packaging
add_custom_target(package_build ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PACKAGE_DIR}/${PACKAGE_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${EXECUTABLE_NAME}> ${PACKAGE_DIR}/${PACKAGE_NAME}/
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/README.md ${PACKAGE_DIR}/${PACKAGE_NAME}/
    DEPENDS ${EXECUTABLE_NAME}
    COMMENT "Creating package for ${PACKAGE_NAME}"
)

# Copy runtime dependencies for Windows
if(WIN32)
    # For Windows, we might need to copy additional DLLs
    add_custom_command(TARGET package_build POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Windows package created: ${PACKAGE_NAME}"
        COMMENT "Finalizing Windows package"
    )
endif()

# Copy runtime dependencies for Linux  
if(UNIX AND NOT APPLE)
    add_custom_command(TARGET package_build POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Linux package created: ${PACKAGE_NAME}"
        COMMENT "Finalizing Linux package"
    )
endif()

# Print build configuration information
message(STATUS "Build configuration:")
message(STATUS "  Platform: ${PLATFORM_NAME}")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Executable name: ${EXECUTABLE_NAME}")
message(STATUS "  Package name: ${PACKAGE_NAME}")
