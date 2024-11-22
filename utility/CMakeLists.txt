add_library(utility STATIC
        src/io_utility.c
        src/id_generator.c)

target_include_directories(utility PUBLIC include)

target_link_libraries(utility error_handling)