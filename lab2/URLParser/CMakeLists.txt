add_executable(UrlParser UrlParser.cpp main.cpp)
add_executable(TestUrlParse UrlParser.cpp tests/test.cpp)

target_link_libraries(TestUrlParse PRIVATE Catch2::Catch2WithMain)