aux_source_directory(Exception EXCEPTION_SOURCES)

add_executable(Car ${EXCEPTION_SOURCES} Model/Car.cpp Controller/CarController.cpp main.cpp)
add_executable(TestCar Model/Car.cpp Tests/TestCar.cpp)

target_link_libraries(TestCar PRIVATE Catch2::Catch2WithMain)
