add_executable(PrimeGenerator PrimeGenerator.cpp main.cpp)
add_executable(PrimeGeneratorTests tests/TestPrimeGenerator.cpp PrimeGenerator.cpp)

target_link_libraries(PrimeGeneratorTests PRIVATE Catch2::Catch2WithMain)