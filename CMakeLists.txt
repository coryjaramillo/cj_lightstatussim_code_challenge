cmake_minimum_required(VERSION 3.31)
project(cj_lightsimstatus_code_chal)

set(CMAKE_CXX_STANDARD 14)

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