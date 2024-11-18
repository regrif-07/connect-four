add_library(connect_four_core STATIC
        src/board.c
        src/game.c
)

target_include_directories(connect_four_core PUBLIC include)

target_link_libraries(connect_four_core
        error_handling)