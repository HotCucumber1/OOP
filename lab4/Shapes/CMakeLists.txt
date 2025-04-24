include(FetchContent)

FetchContent_Declare(
        FakeIt
        GIT_REPOSITORY https://github.com/eranpeer/FakeIt.git
        GIT_TAG master
)
FetchContent_MakeAvailable(FakeIt)
include_directories(${fakeit_SOURCE_DIR}/single_header/standalone)

find_package(SFML 2.5.1 COMPONENTS graphics window system audio REQUIRED)
aux_source_directory(Model MODEL_SOURCES)
aux_source_directory(Canvas CANVAS_SOURCES)

add_executable(Shapes ${MODEL_SOURCES} ${CANVAS_SOURCES} Controller/ShapeController.cpp main.cpp)
add_executable(TestShapes ${MODEL_SOURCES} ${CANVAS_SOURCES} Tests/TestShapes.cpp)
add_executable(TestDraw ${MODEL_SOURCES} ${CANVAS_SOURCES} Tests/TestDraw.cpp)
add_executable(TestShapesController ${MODEL_SOURCES} ${CANVAS_SOURCES} Controller/ShapeController.cpp Tests/TestShapesController.cpp)

target_link_libraries(TestShapes PRIVATE Catch2::Catch2WithMain)
target_link_libraries(TestDraw sfml-graphics sfml-window sfml-system Catch2::Catch2WithMain)
target_link_libraries(TestShapesController sfml-graphics sfml-window sfml-system Catch2::Catch2WithMain)
target_link_libraries(Shapes sfml-graphics sfml-window sfml-system)