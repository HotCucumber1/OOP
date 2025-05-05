add_executable(Date Model/Date.cpp main.cpp)
add_executable(TestDate Model/Date.cpp Tests/TestDate.cpp)

target_link_libraries(TestDate PRIVATE Catch2::Catch2WithMain)