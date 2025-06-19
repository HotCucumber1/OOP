add_executable(MyString Model/MyString.cpp main.cpp)
add_executable(TestMyString Model/MyString.cpp Test/TestMyString.cpp)

target_link_libraries(TestMyString PRIVATE Catch2::Catch2WithMain)