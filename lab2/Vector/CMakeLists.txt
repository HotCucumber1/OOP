add_executable(Vector ../../Core/Core.cpp Vector.cpp main.cpp)
add_executable(TestVector ../../Core/Core.cpp tests/TestVector.cpp Vector.cpp)

target_link_libraries(TestVector PRIVATE Catch2::Catch2WithMain)
