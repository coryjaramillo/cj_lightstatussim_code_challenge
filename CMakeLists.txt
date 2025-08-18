cmake_minimum_required(VERSION 3.31)
project(cj_lightsimstatus_code_chal)

set(CMAKE_CXX_STANDARD 14)

if(DEFINED ENV{CLION_HOME})
    set(MINGW_BIN_PATH "$ENV{CLION_HOME}/bin/mingw/bin")
else()
    # Fallback: Manually specify your CLion directory version
    set(MINGW_BIN_PATH "C:/Program Files/JetBrains/CLion 2025.1/bin/mingw/bin")
endif()


if(CMAKE_BUILD_TYPE STREQUAL "Debug_Simple")
    add_definitions(-DDEBUG_BUILD_SIMPLE)
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Debug_Verbose")
    add_definitions(-DDEBUG_BUILD_VERBOSE)
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Debug_All")
    add_definitions(-DDEBUG_BUILD_VERBOSE -DDEBUG_BUILD_SIMPLE)
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


add_custom_command(TARGET cj_lightsimstatus_code_chal POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${MINGW_BIN_PATH}/libstdc++-6.dll"
        "$<TARGET_FILE_DIR:cj_lightsimstatus_code_chal>/libstdc++-6.dll"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${MINGW_BIN_PATH}/libgcc_s_seh-1.dll"
        "$<TARGET_FILE_DIR:cj_lightsimstatus_code_chal>/libgcc_s_seh-1.dll"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${MINGW_BIN_PATH}/libwinpthread-1.dll"
        "$<TARGET_FILE_DIR:cj_lightsimstatus_code_chal>/libwinpthread-1.dll"
)