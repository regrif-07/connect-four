add_library(connect_four_core STATIC
        src/game.c
        src/game_state.c
)

target_include_directories(connect_four_core PUBLIC include)

target_link_libraries(connect_four_core
        board
        error_handling
        utility)