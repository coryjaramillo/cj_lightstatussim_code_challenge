cmake_minimum_required(VERSION 3.31)
project(cj_lightsimstatus_code_chal)

set(CMAKE_CXX_STANDARD 14)

# Try to detect CLion installation
if(DEFINED ENV{CLION_IDE})
    set(CLION_FOUND TRUE)
    file(GLOB_RECURSE CLION_EXE_LIST
            LIST_DIRECTORIES true
            RELATIVE "C:/"
            "C:/clion.exe"
            "C:/Program Files/JetBrains/CLion*/bin/clion.exe"
            "C:/Users/*/AppData/Local/Programs/CLion*/bin/clion.exe"
    )

    foreach(path IN LISTS CLION_EXE_LIST)
        # This matches any "CLion/bin" at the end
        if(path MATCHES "CLion/bin$")
            message(STATUS "Directory ends with CLion/bin: ${path}")
            set(CLION_PATH "C:/${path}")
        elseif(path MATCHES "CLion[^/\\\\]+[\\\\/]bin$")
            message(STATUS "Wildcard match: Directory ends with CLion<SOMETHING>/bin: ${path}")
            set(CLION_PATH "C:/${path}")
        endif()
    endforeach()
elseif(WIN32)
    file(GLOB CLION_DIRS "C:/Program Files/JetBrains/CLion*")
    if(CLION_DIRS)
        list(SORT CLION_DIRS DESCENDING)
        list(GET CLION_DIRS 0 CLION_PATH)
        set(CLION_FOUND TRUE)
    else()
        set(CLION_FOUND FALSE)
    endif()
else()
    set(CLION_FOUND FALSE)
endif()

# Use different logic depending on whether CLion is present
if(CLION_FOUND)
    message(STATUS "CLion IDE detected...")
    set(MINGW_BIN_PATH "${CLION_PATH}/mingw/bin/")

    if(CMAKE_BUILD_TYPE STREQUAL "Debug_Simple")
        add_definitions(-DDEBUG_BUILD_SIMPLE)
    endif()
    if(CMAKE_BUILD_TYPE STREQUAL "Debug_Verbose")
        add_definitions(-DDEBUG_BUILD_VERBOSE)
    endif()
    if(CMAKE_BUILD_TYPE STREQUAL "Debug_All")
        add_definitions(-DDEBUG_BUILD_VERBOSE -DDEBUG_BUILD_SIMPLE)
    endif()

else()
    message(STATUS "CLion IDE not found, using conventional CMake setup.")
    # Set up your conventional CMake logic (compiler, paths, etc.)
    # For example, rely on system-wide MinGW and CMake settings
endif()


add_executable(${PROJECT_NAME} main.cpp
        src/HomeLights.cpp
        includes/cj_lightsimstatus_code_chal/HomeLights.h)

target_compile_definitions(${PROJECT_NAME} PUBLIC _WIN32_WINNT=0x0A00)

# Force 64-bit build
if (WIN32 AND NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "cpp-httplib and this project require a 64-bit build on Windows.")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_SOURCE_DIR}/external
        ${CMAKE_SOURCE_DIR}/includes/${PROJECT_NAME})

message("MinGW BIN Path: ${MINGW_BIN_PATH}")
message("CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")


file(COPY "${MINGW_BIN_PATH}libstdc++-6.dll" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "${MINGW_BIN_PATH}libgcc_s_seh-1.dll" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "${MINGW_BIN_PATH}libwinpthread-1.dll" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")