add_executable(decoder ../../Core/Core.cpp Decoder.cpp main.cpp)
add_executable(decoder-tests ../../Core/Core.cpp tests/TestDecoder.cpp Decoder.cpp)

target_link_libraries(decoder-tests PRIVATE Catch2::Catch2WithMain)
