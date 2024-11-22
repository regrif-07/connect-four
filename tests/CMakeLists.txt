add_executable(test_board src/test_board.c)
target_link_libraries(test_board PRIVATE board unity)
target_include_directories(test_board PRIVATE "${unity_SOURCE_DIR}/src/")
add_test(NAME TestBoard COMMAND test_board)

add_executable(test_board_serializer src/test_board_serializer.c)
target_link_libraries(test_board_serializer PRIVATE board unity)
target_include_directories(test_board_serializer PRIVATE "${unity_SOURCE_DIR}/src/")
add_test(NAME TestBoardSerializer COMMAND test_board_serializer)

add_executable(test_game_state src/test_game_state.c)
target_link_libraries(test_game_state PRIVATE connect_four_core unity)
target_include_directories(test_game_state PRIVATE "${unity_SOURCE_DIR}/src/")
add_test(NAME TestGameState COMMAND test_game_state)

add_executable(test_id_generator src/test_id_generator.c)
target_link_libraries(test_id_generator PRIVATE utility unity)
target_include_directories(test_id_generator PRIVATE "${unity_SOURCE_DIR}/src/")
add_test(NAME TestIdGenerator COMMAND test_id_generator)

add_executable(test_string_utility src/test_string_utility.c)
target_link_libraries(test_string_utility PRIVATE utility unity)
target_include_directories(test_string_utility PRIVATE "${unity_SOURCE_DIR}/src/")
add_test(NAME TestStringUtility COMMAND test_string_utility)