add_executable(test_board src/test_board.c)
target_link_libraries(test_board PRIVATE connect_four_core unity)
target_include_directories(test_board PRIVATE "${unity_SOURCE_DIR}/src/")
add_test(NAME TestBoard COMMAND test_board)