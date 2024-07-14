cmake_minimum_required(VERSION 3.12)
project(DIFFIMAGES)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optimization flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Source files
set(SOURCE_FILES
    main.cpp
    ./utils/ImageHandler.cc
)

# Prevent a "command line is too long" failure in Windows.
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")

# Create the executable
add_executable(main ${SOURCE_FILES})

# Link against OpenCV libraries
target_link_libraries(main ${OpenCV_LIBS})

# Include directories and compile options
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(main PRIVATE -O3)
