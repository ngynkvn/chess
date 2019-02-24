#include "MoveGenerator.h"
#include "Search.h"
void BaseMoveGenerator::genMove(Coord piece) {
    for (auto j : directions)
    {
        Coord possibleMove = piece + j;
        while (ray && board.inside(possibleMove) && b.getPiece(possibleMove) == epcEmpty && !Search::inCheck(board, Move(piece, possibleMove)))
        {
            moves->emplace_back(piece, possibleMove);
            possibleMove = possibleMove + j;
        }
        if (!b.inside(possibleMove))
            continue;

        auto pieceTo = b.getPiece(possibleMove);
        if ((Search::getColor(pieceTo) == b.opposite() || pieceTo == epcEmpty) && !Search::inCheck(board, Move(piece, possibleMove)))
            moves->emplace_back(piece, possibleMove);
    }
}

void PawnMoveGenerator::genMove(Coord piece) {

    int DIRECTION_OF_ATTACK = b.isWhite() ? 1 : -1;
    int HOME_ROW = b.isWhite() ? 1 : 6;
    Coord push = Coord(0, DIRECTION_OF_ATTACK);
    std::vector<Coord> captures = {Coord(1, DIRECTION_OF_ATTACK), Coord(-1, DIRECTION_OF_ATTACK)};
    Coord possibleMove = piece + push;

    if (b.inside(possibleMove) && b.getPiece(possibleMove) == epcEmpty && !Search::inCheck(board, Move(piece, possibleMove)))
    {
        moves->emplace_back(piece, possibleMove);
        Coord possibleMove2 = possibleMove + push;
        if ((piece.y == HOME_ROW) && b.getPiece(possibleMove2) == epcEmpty && !Search::inCheck(b, Move(piece, possibleMove2)))
            moves->emplace_back(piece, possibleMove2);
    }
    for (Coord cap : captures)
    {
        Coord possibleMove = piece + cap;
        if (b.inside(possibleMove) && Search::getColor(b.getPiece(possibleMove)) == b.opposite() && !Search::inCheck(b, Move(piece, possibleMove)))
            moves->emplace_back(piece, possibleMove);
    }
}
