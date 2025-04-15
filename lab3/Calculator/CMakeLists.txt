aux_source_directory(Exception EXCEPTION_SOURCES)
aux_source_directory(Model MODEL_SOURCES)

add_executable(Calculator ${EXCEPTION_SOURCES} Controller/CalculatorController.cpp ${MODEL_SOURCES} main.cpp)

