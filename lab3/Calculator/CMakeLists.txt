aux_source_directory(Exception EXCEPTION_SOURCES)
aux_source_directory(Model MODEL_SOURCES)

add_executable(Calculator ${EXCEPTION_SOURCES} Controller/CalculatorController.cpp ${MODEL_SOURCES} main.cpp)
add_executable(TestCalculator ${EXCEPTION_SOURCES} ${MODEL_SOURCES} Tests/TestCalculator.cpp)
add_executable(TestCalculatorController
        ${EXCEPTION_SOURCES}
        ${MODEL_SOURCES}
        Controller/CalculatorController.cpp
        Tests/TestCalculatorController.cpp
)

target_link_libraries(TestCalculator PRIVATE Catch2::Catch2WithMain)
target_link_libraries(TestCalculatorController PRIVATE Catch2::Catch2WithMain)