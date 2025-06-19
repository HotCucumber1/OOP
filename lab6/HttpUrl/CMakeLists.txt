aux_source_directory(Exception EXCEPTION_SOURCES)

add_executable(HttpUrl ${EXCEPTION_SOURCES} Model/Protocol.cpp Model/HttpUrl.cpp main.cpp)
add_executable(TestHttpUrl ${EXCEPTION_SOURCES} Model/Protocol.cpp Model/HttpUrl.cpp test/TestHttpUrl.cpp)

target_link_libraries(TestHttpUrl PRIVATE Catch2::Catch2WithMain)
