aux_source_directory(Model MODEL_SOURCES)

add_executable(Shapes ${MODEL_SOURCES} Controller/ShapeController.cpp main.cpp)
add_executable(TestShapes ${MODEL_SOURCES} Tests/TestShapes.cpp)
add_executable(TestShapesController ${MODEL_SOURCES} Controller/ShapeController.cpp Tests/TestShapesController.cpp)

target_link_libraries(TestShapes PRIVATE Catch2::Catch2WithMain)
target_link_libraries(TestShapesController PRIVATE Catch2::Catch2WithMain)