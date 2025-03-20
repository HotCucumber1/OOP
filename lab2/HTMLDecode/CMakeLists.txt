add_executable(Decoder ../../StreamValidChecker/StreamValidChecker.cpp Decoder.cpp main.cpp)
add_executable(TestDecoder ../../StreamValidChecker/StreamValidChecker.cpp tests/TestDecoder.cpp Decoder.cpp)

target_link_libraries(TestDecoder PRIVATE Catch2::Catch2WithMain)
