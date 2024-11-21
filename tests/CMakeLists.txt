add_executable(test_board src/test_board.c)
target_link_libraries(test_board PRIVATE board unity)
target_include_directories(test_board PRIVATE "${unity_SOURCE_DIR}/src/")
add_test(NAME TestBoard COMMAND test_board)

add_executable(test_board_serializer src/test_board_serializer.c)
target_link_libraries(test_board_serializer PRIVATE board unity)
target_include_directories(test_board_serializer PRIVATE "${unity_SOURCE_DIR}/src/")
add_test(NAME TestBoardSerializer COMMAND test_board_serializer)