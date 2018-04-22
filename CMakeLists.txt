cmake_minimum_required(VERSION 3.9)
project(chess)

set(CMAKE_CXX_STANDARD 11)

add_executable(chess
        chess/include/Board.h
        chess/include/Evaluation.h
        chess/include/Move.h
        chess/include/Piece.h
        chess/include/Search.h
        chess/include/uci.h
        chess/src/Board.cpp
        chess/src/Evaluation.cpp
        chess/src/main.cpp
        chess/src/Move.cpp
        chess/src/Piece.cpp
        chess/src/Search.cpp
        chess/src/uci.cpp
        chess/test/catch.hpp
        chess/test/perft.cpp
        chess/test/test-main.cpp
        chess/test/tests.cpp
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
