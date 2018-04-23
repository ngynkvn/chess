#include "catch.hpp"
#include "Move.h"
#include "Piece.h"
#include "Board.h"

unsigned long long perft(Board, int, int &);
unsigned long long perft(Board, int, int &, int &);

TEST_CASE("Piece data-type works correctly", "[piece]")
{
    Piece p = Piece(epcEmpty);
    CHECK(p.empty());

    p = Piece(epcWpawn);

    CHECK_FALSE(p.empty());

    CHECK(p == Piece(epcWpawn));
    CHECK(p == epcWpawn);
    CHECK_FALSE(p == epcEmpty);
    CHECK_FALSE(p != Piece(epcWpawn));

    CHECK(p.getPieceCode() == epcWpawn);
    CHECK(p.getColor() == white);
    CHECK_FALSE(p.getColor() == black);
    CHECK_FALSE(p.getColor() == epcEmpty);
}

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
        CHECK(perft(start, 3, captures, checks) == 8902);
        CHECK(captures == 34);
        CHECK(checks == 12);
    }
    SECTION("Depth 4 should show 1576 captures.")
    {
        CHECK(perft(start, 4, captures, checks) == 197281);
        CHECK(captures == 1576);
        CHECK(checks == 469);
    }
}

TEST_CASE("Board data-type works correctly", "[board]")
{
    Board start;
    SECTION("Pawns are in the correct positions.")
    {
        for (int i = 0; i < 8; i++)
        {
            CHECK(start.getPiece(Coord(i, 1)).getPieceCode() == epcWpawn);
            CHECK(start.getPiece(Coord(i, 6)).getPieceCode() == epcBpawn);
        }
    }
    SECTION("Major pieces are in the correct positions.")
    {
        ePieceCode table[] = {epcWrook, epcWknight, epcWbishop, epcWking, epcWqueen, epcWbishop, epcWknight, epcWrook};
        for (int i = 0; i < 8; i++)
        {
            CHECK(start.getPiece(Coord(i, 0)).getPieceCode() == table[i]);
            CHECK(start.getPiece(Coord(i, 7)).getPieceCode() == table[i] + black);
        }
    }
    SECTION("Inputting moves does not modify previous board state.")
    {
        Move wPawnPush(Coord(1, 1), Coord(1, 2));
        Board postMortem = start.makeMove(wPawnPush);

        Piece pieceFrom = start.getPiece(wPawnPush.from());
        Piece pieceTo = start.getPiece(wPawnPush.to());

        CHECK(pieceFrom.getPieceCode() != epcEmpty);
        CHECK(pieceTo.getPieceCode() != epcWpawn);
        CHECK(pieceFrom.getPieceCode() == epcWpawn);
        CHECK(pieceTo.getPieceCode() == epcEmpty);

        pieceFrom = postMortem.getPiece(wPawnPush.from());
        pieceTo = postMortem.getPiece(wPawnPush.to());

        CHECK(pieceFrom.getPieceCode() != epcWpawn);
        CHECK(pieceFrom.getPieceCode() == epcEmpty);

        CHECK(pieceTo.getPieceCode() == epcWpawn);
        CHECK(pieceTo.getPieceCode() != epcEmpty);
    }
}

TEST_CASE("Move data-type works correctly", "[move]")
{

    SECTION("Move can be created from 4 int parameters.")
    {
        Move m(1, 2, 3, 4);
        REQUIRE(m.from().x == 1);
        REQUIRE(m.from().y == 2);
        REQUIRE(m.to().x == 3);
        REQUIRE(m.to().y == 4);
    }

    SECTION("Move can be created from 2 coord parameters.")
    {
        Move m(Coord(5, 6), Coord(6, 7));
        REQUIRE(m.from().x == 5);
        REQUIRE(m.from().y == 6);
        REQUIRE(m.to().x == 6);
        REQUIRE(m.to().y == 7);
    }
}
