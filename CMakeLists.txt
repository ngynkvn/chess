cmake_minimum_required(VERSION 3.9)
project(chess)

set(CMAKE_CXX_STANDARD 11)

add_executable(chess
        include/Board.h
        include/Evaluation.h
        include/Move.h
        include/Piece.h
        include/Search.h
        include/uci.h
        src/Board.cpp
        src/Evaluation.cpp
        src/main.cpp
        src/Move.cpp
        src/Piece.cpp
        src/Search.cpp
        src/uci.cpp
        test/catch.hpp
        test/perft.cpp
        test/test-main.cpp
        test/tests.cpp)
