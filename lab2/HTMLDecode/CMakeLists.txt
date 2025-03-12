add_executable(Decoder ../../Core/Core.cpp Decoder.cpp main.cpp)
add_executable(TestDecoder ../../Core/Core.cpp tests/TestDecoder.cpp Decoder.cpp)

target_link_libraries(TestDecoder PRIVATE Catch2::Catch2WithMain)
