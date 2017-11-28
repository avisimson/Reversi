cmake_minimum_required(VERSION 3.8)
project(Reversi)

#set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")

add_subdirectory(lib/googletest-release-1.8.0)

include_directories(src lib/googletest-release-1.8.0/googletest/include)
include_directories(lib/googletest-release-1.8.0/googlemock/include)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE_FILES src/Board.h src/Board.cpp src/Game.cpp src/Game.h
        src/GameType.h src/Player.h src/Player.cpp src/ReversiGame.cpp src/ReversiGame.h)

set(TEST_FILES Tests/Board_test.cpp Tests/Board_test.h Tests/Player_test.cpp Tests/Player_test.h)

add_executable(game ${SOURCE_FILES} src/main.cpp)
add_executable(tests ${SOURCE_FILES} ${TEST_FILES} Tests/test_main.cpp)

target_link_libraries(tests gtest gtest_main gmock)