#include "catch.hpp"
#include "Move.h"
#include "Piece.h"
#include "Board.h"
#include "pertf.h"
#include <iostream>

TEST_CASE("Move generation is correct.", "[perft]")
{
    Board start;
    SECTION("Depth 1")
    {
        auto [nodes, captures, checks] = perft(start, 1);
        CHECK(nodes == 20);
        CHECK(captures == 0);
        // CHECK(checks == 0);
    }
    SECTION("Depth 2")
    {
        auto [nodes, captures, checks] = perft(start, 2);
        CHECK(nodes == 400);
        CHECK(captures == 0);
        // CHECK(checks == 0);
    }
    SECTION("Depth 3 should show 34 captures.")
    {
        auto [nodes, captures, checks] = perft(start, 3);
        CHECK(nodes == 8902);
        CHECK(captures == 34);
        // CHECK(checks == 12);
    }
    SECTION("Depth 4 should show 1576 captures.")
    {
        auto [nodes, captures, checks] = perft(start, 4);
        CHECK(nodes == 197281);
        CHECK(captures == 1576);
        // CHECK(checks == 469);
    }
    SECTION("Depth 5")
    {
        auto [nodes, captures, checks] = perft(start, 5);
        CHECK(nodes == 4865609);
        CHECK(captures == 82719);
    }
}

TEST_CASE("Board data-type works correctly", "[board]")
{
    Board start;
    SECTION("Pawns are in the correct positions.")
    {
        for (int i = 0; i < 8; i++)
        {
            CHECK(start.getPiece(Coord(i, 1)) == epcWpawn);
            CHECK(start.getPiece(Coord(i, 6)) == epcBpawn);
        }
    }
    SECTION("Major pieces are in the correct positions.")
    {
        ePieceCode table[] = {epcWrook, epcWknight, epcWbishop, epcWking, epcWqueen, epcWbishop, epcWknight, epcWrook};
        for (int i = 0; i < 8; i++)
        {
            CHECK(start.getPiece(Coord(i, 0)) == table[i]);
            CHECK(start.getPiece(Coord(i, 7)) == table[i] + ePieceCode::Black);
        }
    }
    SECTION("Inputting moves does not modify previous board state.")
    {
        Move wPawnPush(Coord(1, 1), Coord(1, 2));

        ePieceCode pieceFrom = start.getPiece(wPawnPush.from);
        ePieceCode pieceTo = start.getPiece(wPawnPush.to);

        start.makeMove(wPawnPush);

        CHECK(pieceFrom != epcEmpty);
        CHECK(pieceTo != epcWpawn);
        CHECK(pieceFrom == epcWpawn);
        CHECK(pieceTo == epcEmpty);

        pieceFrom = start.getPiece(wPawnPush.from);
        pieceTo = start.getPiece(wPawnPush.to);

        CHECK(pieceFrom != epcWpawn);
        CHECK(pieceFrom == epcEmpty);

        CHECK(pieceTo == epcWpawn);
        CHECK(pieceTo != epcEmpty);
    }
}

TEST_CASE("Move data-type works correctly", "[move]")
{

    SECTION("Move can be created from 4 int parameters.")
    {
        Move m(1, 2, 3, 4);
        REQUIRE(m.from.first == 1);
        REQUIRE(m.from.second == 2);
        REQUIRE(m.to.first == 3);
        REQUIRE(m.to.second == 4);
    }

    SECTION("Move can be created from 2 coord parameters.")
    {
        Move m(Coord(5, 6), Coord(6, 7));
        REQUIRE(m.from.first == 5);
        REQUIRE(m.from.second == 6);
        REQUIRE(m.to.first == 6);
        REQUIRE(m.to.second == 7);
    }
}
