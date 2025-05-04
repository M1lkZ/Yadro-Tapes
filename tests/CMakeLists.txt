add_executable(file_tape_tests test_file_tape.cpp)
add_executable(tape_sorter_tests test_tape_sorter.cpp)

target_link_libraries(file_tape_tests
    PRIVATE tape_lib
    GTest::gtest_main
)

target_link_libraries(tape_sorter_tests
    PRIVATE tape_lib
    GTest::gtest_main
)

add_test(NAME file_tape_tests COMMAND file_tape_tests)
add_test(NAME tape_sorter_tests COMMAND tape_sorter_tests)