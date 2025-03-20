add_executable(Vector ../../StreamValidChecker/StreamValidChecker.cpp Vector.cpp main.cpp)
add_executable(TestVector ../../StreamValidChecker/StreamValidChecker.cpp tests/TestVector.cpp Vector.cpp)

target_link_libraries(TestVector PRIVATE Catch2::Catch2WithMain)
