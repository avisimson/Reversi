cmake_minimum_required(VERSION 3.8)
project(Reversi)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Board.cpp Board.h Game.cpp Game.h Player.cpp Player.h ReversiGame.cpp ReversiGame.h GameType.h)
add_executable(Reversi ${SOURCE_FILES})