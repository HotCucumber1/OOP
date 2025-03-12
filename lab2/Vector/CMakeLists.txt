add_executable(Vector ../../Core/Core.cpp Vector.cpp main.cpp)
add_executable(VectorTests ../../Core/Core.cpp tests/TestVector.cpp Vector.cpp)

target_link_libraries(VectorTests PRIVATE Catch2::Catch2WithMain)
