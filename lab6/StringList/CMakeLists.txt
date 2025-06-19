add_executable(StringList Model/StringList.cpp main.cpp)
add_executable(TestStringList Model/StringList.cpp test/TestStringList.cpp)

target_link_libraries(TestStringList PRIVATE Catch2::Catch2WithMain)