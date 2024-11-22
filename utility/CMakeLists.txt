add_library(utility STATIC
        src/io_utility.c
        src/id_generator.c
        src/string_utility.c)

target_include_directories(utility PUBLIC include)

target_link_libraries(utility error_handling)