add_executable(connect_four_game src/main.c)

target_link_libraries(connect_four_game
        connect_four_core
        utility)