cmake_minimum_required(VERSION 3.30)
project(connect_four C)

set(CMAKE_C_STANDARD 23)

enable_testing()

include(FetchContent)

FetchContent_Declare(
        Unity
        GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
)
FetchContent_MakeAvailable(Unity)

add_subdirectory(connect_four_game)
add_subdirectory(connect_four_core)
add_subdirectory(utility)
add_subdirectory(error_handling)

add_subdirectory(tests)