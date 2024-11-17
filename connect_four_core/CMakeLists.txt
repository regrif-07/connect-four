add_library(connect_four_core STATIC
        src/board.c)

target_include_directories(connect_four_core PUBLIC include)