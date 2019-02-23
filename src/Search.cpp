#include <utility>

#include "Search.h"
#include <iostream>
#include <map>
#include <assert.h>
#include <algorithm>
#include <functional>

namespace Search
{


    ePieceCode getColor(ePieceCode code)
    {
        if (code == epcEmpty)
        {
            return epcEmpty;
        }
        return code > black ? ePieceCode::black : ePieceCode::white;
    }
    struct Movement {
        ePieceCode piece;
        std::vector<Coord> directions;
        bool ray;
        Movement(ePieceCode piece, std::vector<Coord> directions, bool ray) : piece(piece), directions(std::move(directions)), ray(ray) {}
        std::vector<Move> generateMoves(Board& b)
        {
            std::vector<Coord> pieceCoords = findPieces(b, piece + (b.isWhite() ? 0 : 7));
            std::vector<Move> moves;
            for (auto pieceCoord : pieceCoords)
            {
                for (auto j : directions)
                {
                    Coord possibleMove = pieceCoord + j;
                    while (ray && b.inside(possibleMove) && b.getPiece(possibleMove) == epcEmpty && !inCheck(b, Move(pieceCoord, possibleMove)))
                    {
                        moves.emplace_back(pieceCoord, possibleMove);
                        possibleMove = possibleMove + j;
                    }
                    if (!b.inside(possibleMove))
                        continue;
                    auto pieceTo = b.getPiece(possibleMove);
                    if ((getColor(pieceTo) == b.opposite() || pieceTo == epcEmpty) && !inCheck(b, Move(pieceCoord, possibleMove)))
                        moves.emplace_back(pieceCoord, possibleMove);
                }
            }
            return moves;
        }
    };

std::vector<Coord> dirRook = {Coord(0, 1),
                              Coord(0, -1),
                              Coord(1, 0),
                              Coord(-1, 0)};
Movement movementRook = Movement(epcWrook, dirRook, true);

std::vector<Coord> dirBishop = {Coord(1, 1),
                                Coord(1, -1),
                                Coord(-1, -1),
                                Coord(-1, 1)};
Movement movementBishop = Movement(epcWbishop, dirBishop, true);

std::vector<Coord> dirQueen = {Coord(1, 1),
                               Coord(1, -1),
                               Coord(-1, -1),
                               Coord(-1, 1),
                               Coord(0, 1),
                               Coord(0, -1),
                               Coord(1, 0),
                               Coord(-1, 0)};
Movement movementQueen = Movement(epcWqueen, dirQueen, true);

std::vector<Coord> dirKnight = {Coord(1, 2),
                                Coord(2, 1),
                                Coord(2, -1),
                                Coord(1, -2),
                                Coord(-1, 2),
                                Coord(-2, 1),
                                Coord(-2, -1),
                                Coord(-1, -2)};
Movement movementKnight = Movement(epcWknight, dirKnight, false);

std::vector<Coord> dirKing = {Coord(-1, -1),
                              Coord(-1, 0),
                              Coord(-1, 1),
                              Coord(0, 1),
                              Coord(0, -1),
                              Coord(1, -1),
                              Coord(1, 0),
                              Coord(1, 1)};
Movement movementKing = Movement(epcWking, dirKing, false);

Coord wPawnPush = Coord(0, 1);
Coord bPawnPush = Coord(0, -1);
std::vector<Coord> wPawnCaptures = {Coord(1, 1),
                                    Coord(-1, 1)};

std::vector<Coord> bPawnCaptures = {Coord(1, -1),
                                    Coord(-1, -1)};

std::map<ePieceCode, std::vector<Coord>> cachePos;

void cachePositions(Board &b)
{
    cachePos.clear();
    ePieceCode **board = b.getBoard();
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != epcEmpty)
            {
                cachePos[board[i][j]].emplace_back(j, i);
            }
        }
}

std::vector<Coord> findPieces(Board &b, int piece)
{
    return cachePos[static_cast<ePieceCode>(piece)];
}

bool rayCheckHelper(const Board &b, Coord piece, std::vector<Coord> dir, int epcCode)
{
    auto code = static_cast<ePieceCode>(epcCode);

    for (auto k : dir)
    {

        Coord possibleMove = piece + k;
        while (b.inside(possibleMove) && b.getPiece(possibleMove) == epcEmpty)
        {
            possibleMove = possibleMove + k;
        }

        if (b.inside(possibleMove) && b.getPiece(possibleMove) == code)
            return true;
    }

    return false;
}

bool squareCheckHelper(const Board &b, Coord piece, std::vector<Coord> dir, int epcCode)
{
    auto code = static_cast<ePieceCode>(epcCode);
    for (auto k : dir)
    {
        Coord possibleMove = piece + k;
        if (b.inside(possibleMove) && b.getPiece(possibleMove) == code)
            return true;
    }
    return false;
}

bool inCheck(Board &b, Move consideringMove)
{
    bool turnIsWhite = b.isWhite();
    int c = turnIsWhite ? white : black;
    auto pieceTo = b.getPiece(consideringMove.to());

    if (pieceTo == (turnIsWhite ? epcWking : epcBking))
    {
        return true;
    }

    std::vector<Coord> pieceV = findPieces(b, epcWking + c);
    b.makeMove(consideringMove);

    Coord piece = pieceV[0];

    c = turnIsWhite ? black : white;
    bool result = rayCheckHelper(b, piece, dirRook, epcWrook + c) || rayCheckHelper(b, piece, dirQueen, epcWqueen + c) || rayCheckHelper(b, piece, dirBishop, epcWbishop + c) || squareCheckHelper(b, piece, dirKnight, epcWknight + c) || squareCheckHelper(b, piece, turnIsWhite ? wPawnCaptures : bPawnCaptures, epcWpawn + c) || squareCheckHelper(b, piece, dirKing, epcWking + c);
    b.unmakeMove();
    return result;
}

void pawnMove(std::vector<Move> &v, Board &b, std::vector<Coord> &pieceV)
{
    bool turnIsWhite = b.isWhite();
    Coord push = turnIsWhite ? wPawnPush : bPawnPush;
    std::vector<Coord> captures = turnIsWhite ? wPawnCaptures : bPawnCaptures;

    for (auto piece : pieceV)
    {
        Coord possibleMove = piece + push;

        if (b.inside(possibleMove) && b.getPiece(possibleMove) == epcEmpty && !inCheck(b, Move(piece, possibleMove)))
        {
            v.emplace_back(piece, possibleMove);
            Coord possibleMove2 = possibleMove + push;
            if ((piece.y == (turnIsWhite ? 1 : 6)) && b.getPiece(possibleMove2) == epcEmpty && !inCheck(b, Move(piece, possibleMove2)))
                v.emplace_back(piece, possibleMove2);
        }
        for (Coord cap : captures)
        {
            Coord possibleMove = piece + cap;
            if (b.inside(possibleMove) && getColor(b.getPiece(possibleMove)) == b.opposite() && !inCheck(b, Move(piece, possibleMove)))
                v.emplace_back(piece, possibleMove);
        }
    }
}

void addMovesTo(std::vector<Move> &v, std::vector<Move> moves)
{
    v.insert(v.end(), moves.begin(), moves.end());
}

std::vector<Move> generateMoveList(Board &b)
{
    std::vector<Move> v;
    cachePositions(b);
    addMovesTo(v, movementKnight.generateMoves(b));
    addMovesTo(v, movementBishop.generateMoves(b));
    addMovesTo(v, movementQueen.generateMoves(b));
    addMovesTo(v, movementRook.generateMoves(b));
    auto pieces = findPieces(b, b.isWhite() ? epcWpawn : epcBpawn);
    pawnMove(v, b, pieces);
    addMovesTo(v, movementKing.generateMoves(b));
    return v;
}


} // namespace Search
