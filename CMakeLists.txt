cmake_minimum_required(VERSION 3.29)
project(OOP_project)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(Catch2)
add_subdirectory(lab2/Dictionary)
add_subdirectory(lab2/Vector)
add_subdirectory(lab2/HTMLDecode)
