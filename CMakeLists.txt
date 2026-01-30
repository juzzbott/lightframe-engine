cmake_minimum_required(VERSION 3.10)
project(lightframe_engine CXX C)

# ========================================
# CMAKE Settings
# ========================================

# Set C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/obj)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# SET COMPILE COMMAND
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable -Werror
add_compile_options(-Werror)

# Set build types
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose build type" FORCE)
endif ()

# Setup configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

# Add the lightframe engine library
add_subdirectory("lightframe")

# Add the test-bed application
add_subdirectory("test-bed")
