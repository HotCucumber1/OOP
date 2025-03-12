add_executable(PrimeGenerator PrimeGenerator.cpp main.cpp)
add_executable(TestPrimeGenerator tests/TestPrimeGenerator.cpp PrimeGenerator.cpp)

target_link_libraries(TestPrimeGenerator PRIVATE Catch2::Catch2WithMain)
