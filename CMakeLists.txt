cmake_minimum_required(VERSION 3.26)
project(Monkey_Typer)

set(CMAKE_CXX_STANDARD 20)

#set(BUILD_SHARED_LIBS FALSE) on Windows - uncomment this line

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 11.0.2
)

FetchContent_MakeAvailable(fmt)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(SFML)

add_executable(MonkeyTyper main.cpp
        Settings.cpp
        Menu.cpp
        Game.cpp)
target_link_libraries(MonkeyTyper fmt sfml-graphics)
