add_executable(Decoder ../../Core/Core.cpp Decoder.cpp main.cpp)
add_executable(DecoderTests ../../Core/Core.cpp tests/TestDecoder.cpp Decoder.cpp)

target_link_libraries(DecoderTests PRIVATE Catch2::Catch2WithMain)
