# Set the minimum version of CMake that can be used
# Use target debugging need CMake version 3.7.2 or higher
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.16)


set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_C_COMPILER "clang")
# set(CMAKE_CXX_COMPILER "clang++")
# output compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Setting build type to 'Debug' as none was specified.")
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()


# Set the project name
project(dataStructure)

add_executable(${PROJECT_NAME}
    src/main.cpp
)