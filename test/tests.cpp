#include "catch.hpp"
#include "Move.h"
#include "Piece.h"
#include "Board.h"

unsigned long long perft(Board&, int, int &);
unsigned long long perft(Board&, int, int &, int &);

TEST_CASE("Move generation is correct.", "[perft]")
{
    Board start;
    int captures = 0;
    int checks = 0;
    CHECK(perft(start, 1, captures) == 20);
    CHECK(captures == 0);
    CHECK(perft(start, 2, captures) == 400);
    CHECK(captures == 0);
    SECTION("Depth 3 should show 34 captures.")
    {
        CHECK(perft(start, 3, captures) == 8902);
        CHECK(captures == 34);
    }
    SECTION("Depth 4 should show 1576 captures.")
    {
        CHECK(perft(start, 4, captures) == 197281);
        CHECK(captures == 1576);
    }
    SECTION("Depth 5")
    {
        // CHECK(perft(start, 5, captures) == 4865609);
        // CHECK(captures == 82719);
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
            CHECK(start.getPiece(Coord(i, 7)) == table[i] + black);
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
