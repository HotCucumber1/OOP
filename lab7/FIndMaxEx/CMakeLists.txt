add_executable(FindMaxEx main.cpp)
add_executable(TestFindMaxEx TestFindMaxEx.cpp)

target_link_libraries(TestFindMaxEx PRIVATE Catch2::Catch2WithMain)