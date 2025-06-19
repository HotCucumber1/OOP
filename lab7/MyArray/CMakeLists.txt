add_executable(TestMyArray test/TestMyArray.cpp)

target_link_libraries(TestMyArray PRIVATE Catch2::Catch2WithMain)
