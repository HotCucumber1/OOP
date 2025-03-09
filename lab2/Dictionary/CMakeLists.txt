add_executable(dictionary Dictionary.cpp main.cpp)
add_executable(dict-tests tests/TestDictionary.cpp Dictionary.cpp)

target_link_libraries(dict-tests PRIVATE Catch2::Catch2WithMain)
