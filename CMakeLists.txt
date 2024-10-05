cmake_minimum_required(VERSION 3.10)

# Set project name and version
project(MyCppProject)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Automatically search for all .cpp files in src and its subdirectories
file(GLOB_RECURSE SOURCES "src/**/*.cpp")
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")

# Include Catch2
include(FetchContent)

FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.13.9  # Specify the desired version
)

FetchContent_MakeAvailable(catch2)

# Create a library with the data structures and algorithms files
add_library(MyLib ${SOURCES})

# Create an executable for the tests
add_executable(MyTests ${TEST_SOURCES})

# Link the library and Catch2 to the test executable
target_link_libraries(MyTests MyLib Catch2::Catch2)

# Register Catch2 tests with CMake
include(CTest)
include(Catch)
catch_discover_tests(MyTests)
