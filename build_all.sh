#!/bin/bash

set -e  # Exit immediately if a build command fails

# Locate CMake in the windows system


# Dynamically choose how many cpu's to use for each build command


# Build Debug_Simple
C:\Users\skyse\AppData\Local\Programs\CLion\bin\cmake\win\x64\bin\cmake.exe --build C:\Users\skyse\Software_Engineering\CLionProjects\cj_lightstatussim_code_challenge\cmake-build-debug_simple --target cj_lightsimstatus_code_chal -j 14

# Build Debug_Verbose
C:\Users\skyse\AppData\Local\Programs\CLion\bin\cmake\win\x64\bin\cmake.exe --build C:\Users\skyse\Software_Engineering\CLionProjects\cj_lightstatussim_code_challenge\cmake-build-debug_verbose --target cj_lightsimstatus_code_chal -j 14

# Build Debug_All
C:\Users\skyse\AppData\Local\Programs\CLion\bin\cmake\win\x64\bin\cmake.exe --build C:\Users\skyse\Software_Engineering\CLionProjects\cj_lightstatussim_code_challenge\cmake-build-debug_all --target cj_lightsimstatus_code_chal -j 14

# Build Release
C:\Users\skyse\AppData\Local\Programs\CLion\bin\cmake\win\x64\bin\cmake.exe --build C:\Users\skyse\Software_Engineering\CLionProjects\cj_lightstatussim_code_challenge\cmake-build-release --target cj_lightsimstatus_code_chal -j 14