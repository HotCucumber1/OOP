aux_source_directory(Model MODEL_SOURCES)

add_executable(Shapes ${MODEL_SOURCES} Controller/ShapeController.cpp main.cpp)