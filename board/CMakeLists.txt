add_library(board STATIC
        src/board.c
        src/board_serializer.c)

target_include_directories(board PUBLIC include)

target_link_libraries(board error_handling)