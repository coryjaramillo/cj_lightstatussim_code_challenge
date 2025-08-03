cmake_minimum_required(VERSION 3.31)
project(cj_lightsimstatus_code_chal)

set(CMAKE_CXX_STANDARD 14)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG_BUILD)
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

# ==== INSTALL AND PACKAGING SECTION (ADD THIS AT THE END) ====
# Install target and extra files into package directory structure
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(FILES ${CMAKE_SOURCE_DIR}/config/appconfig.json DESTINATION config)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/docs/ DESTINATION docs)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources/ DESTINATION resources)

# Optionally set CPack/packaging options
set(CPACK_GENERATOR "ZIP")
include(CPack)