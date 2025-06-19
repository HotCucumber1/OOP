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
add_subdirectory(lab2/PrimeGenerator)
add_subdirectory(lab2/URLParser)

add_subdirectory(lab3/Car)
add_subdirectory(lab3/Calculator)

add_subdirectory(lab4/Shapes)

add_subdirectory(lab5/Date)
add_subdirectory(lab5/MyString)

add_subdirectory(lab6/HttpUrl)
add_subdirectory(lab6/StringList)

add_subdirectory(lab7/FIndMaxEx)
add_subdirectory(lab7/MyArray)
