cmake_minimum_required(VERSION 3.8)
project(Reversi)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_subdirectory(lib/googletest-release-1.8.0)

include_directories(src lib/googletest-release-1.8.0/googletest/include)
include_directories(lib/googletest-release-1.8.0/googlemock/include)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE_FILES src/client/Board.h src/client/Board.cpp src/client/Game.cpp src/client/Game.h
        src/client/GameType.h src/client/Player.h src/client/Player.cpp src/client/ReversiGame.cpp
        src/client/ReversiGame.h src/client/NetworkClient.cpp src/client/NetworkClient.h src/client/Display.h
        src/client/ConsoleDisplay.cpp src/client/ConsoleDisplay.h)

set(SERVER_FILES src/Server/ReversiServer.cpp src/Server/ReversiServer.h src/Server/main.cpp
        src/Server/HandleClient.cpp src/Server/HandleClient.h src/Server/GameManager.cpp src/Server/GameManager.h
        src/Server/Command.h src/Server/StartCommand.cpp src/Server/StartCommand.h src/Server/JoinGameCommand.cpp
        src/Server/JoinGameCommand.h src/Server/GameListCommand.cpp src/Server/GameListCommand.h
        src/Server/CloseCommand.cpp src/Server/CloseCommand.h src/Server/MakeMoveCommand.cpp
        src/Server/MakeMoveCommand.h src/Server/DirectorCommand.cpp src/Server/DirectorCommand.h
        src/Server/Task.h src/Server/ThreadPool.cpp src/Server/ThreadPool.h)

set(TEST_FILES Tests/Board_test.cpp Tests/Board_test.h Tests/Player_test.cpp Tests/Player_test.h
        Tests/ReversiGame_test.cpp Tests/ReversiGame_test.h Tests/test_main.cpp)

add_executable(Server ${SERVER_FILES} src/Server/main.cpp)
add_executable(Tests ${SOURCE_FILES} ${TEST_FILES} Tests/test_main.cpp)
add_executable(Reversi ${SOURCE_FILES} src/client/main.cpp)

target_link_libraries(Tests gtest gtest_main gmock)
