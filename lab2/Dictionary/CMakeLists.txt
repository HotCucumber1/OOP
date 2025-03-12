add_executable(Dictionary Dictionary.cpp main.cpp)
add_executable(TestDictionary tests/TestDictionary.cpp Dictionary.cpp)

target_link_libraries(TestDictionary PRIVATE Catch2::Catch2WithMain)
