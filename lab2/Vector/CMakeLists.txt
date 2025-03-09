add_executable(vector ../../Core/Core.cpp Vector.cpp main.cpp)
add_executable(vector-tests ../../Core/Core.cpp tests/TestVector.cpp Vector.cpp)
add_executable(vector-unit-tests ../../Core/Core.cpp tests/TestVectorCore.cpp Vector.cpp)

target_link_libraries(vector-tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(vector-unit-tests PRIVATE Catch2::Catch2WithMain)
