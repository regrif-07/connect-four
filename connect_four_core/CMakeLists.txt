add_library(connect_four_core STATIC
        src/game_context.c
        src/game_functionality.c
        src/game_context_serializer.c
        src/game_state.c
        src/save_system.c
)

target_include_directories(connect_four_core PUBLIC include)

target_link_libraries(connect_four_core
        board
        error_handling
        utility)