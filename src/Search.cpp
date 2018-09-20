#include "Search.h"
#include <iostream>
#include <map>
#include <assert.h>

namespace Search
{

std::vector<Coord> dirRook = {Coord(0, 1),
                              Coord(0, -1),
                              Coord(1, 0),
                              Coord(-1, 0)};

std::vector<Coord> dirBishop = {Coord(1, 1),
                                Coord(1, -1),
                                Coord(-1, -1),
                                Coord(-1, 1)};

std::vector<Coord> dirQueen = {Coord(1, 1),
                               Coord(1, -1),
                               Coord(-1, -1),
                               Coord(-1, 1),
                               Coord(0, 1),
                               Coord(0, -1),
                               Coord(1, 0),
                               Coord(-1, 0)};

std::vector<Coord> dirKnight = {Coord(1, 2),
                                Coord(2, 1),
                                Coord(2, -1),
                                Coord(1, -2),
                                Coord(-1, 2),
                                Coord(-2, 1),
                                Coord(-2, -1),
                                Coord(-1, -2)};

std::vector<Coord> dirKing = {Coord(-1, -1),
                              Coord(-1, 0),
                              Coord(-1, 1),
                              Coord(0, 1),
                              Coord(0, -1),
                              Coord(1, -1),
                              Coord(1, 0),
                              Coord(1, 1)};

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
    ePieceCode code = static_cast<ePieceCode>(epcCode);

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
    ePieceCode code = static_cast<ePieceCode>(epcCode);
    for (auto k : dir)
    {
        Coord possibleMove = piece + k;
        if (b.inside(possibleMove) && b.getPiece(possibleMove) == code)
            return true;
    }
    return false;
}

bool inCheck(Board &b, Move m)
{
    bool turnIsWhite = b.isWhite();
    int c = turnIsWhite ? white : black;
    auto pieceTo = b.getPiece(m.to());

    if (pieceTo == epcWking || pieceTo == epcBking)
    {
        return true;
    }

    std::vector<Coord> pieceV = findPieces(b, epcWking + c);
    b.makeMove(m);

    if (pieceV.empty())
        throw std::runtime_error("Found king is not on board.");

    Coord piece = pieceV[0];

    c = turnIsWhite ? black : white;
    bool result = rayCheckHelper(b, piece, dirRook, epcWrook + c) || rayCheckHelper(b, piece, dirQueen, epcWqueen + c) || rayCheckHelper(b, piece, dirBishop, epcWbishop + c) || squareCheckHelper(b, piece, dirKnight, epcWknight + c) || squareCheckHelper(b, piece, turnIsWhite ? wPawnCaptures : bPawnCaptures, epcWpawn + c) || squareCheckHelper(b, piece, dirKing, epcWking + c);
    b.unmakeMove();
    return result;
}

bool inCheck(Board &b)
{
    bool turnIsWhite = b.isWhite();

    std::vector<Coord> pieceV = turnIsWhite ? findPieces(b, epcWking) : findPieces(b, epcBking);

    Coord piece = pieceV[0];
    int c = turnIsWhite ? black : white;
    bool result = rayCheckHelper(b, piece, dirRook, epcWrook + c) || rayCheckHelper(b, piece, dirQueen, epcWqueen + c) || rayCheckHelper(b, piece, dirBishop, epcWbishop + c) || squareCheckHelper(b, piece, dirKnight, epcWknight + c) || squareCheckHelper(b, piece, turnIsWhite ? wPawnCaptures : bPawnCaptures, epcWpawn + c);
    b.unmakeMove();
    return result;
}

ePieceCode getColor(ePieceCode code);

void rayMove(std::vector<Move> &v, Board &b, std::vector<Coord> &pieceV, std::vector<Coord> dir)
{
    for (auto piece : pieceV)
    {

        for (auto j : dir)
        {
            Coord possibleMove = piece + j;
            while (b.inside(possibleMove) && b.getPiece(possibleMove) == epcEmpty && !inCheck(b, Move(piece, possibleMove)))
            {
                v.emplace_back(piece, possibleMove);
                possibleMove = possibleMove + j;
            }

            if (!b.inside(possibleMove))
                continue;

            auto pieceTo = b.getPiece(possibleMove);
            if (getColor(pieceTo) == b.opposite() && !inCheck(b, Move(piece, possibleMove)))
                v.emplace_back(piece, possibleMove);
        }
    }
}

ePieceCode getColor(ePieceCode code)
{
    if (code == epcEmpty)
    {
        return epcEmpty;
    }
    return code > black ? ePieceCode::black : ePieceCode::white;
}

void squareMove(std::vector<Move> &v, Board &b, std::vector<Coord> &pieceV, std::vector<Coord> dir)
{

    for (auto piece : pieceV)
    {
        for (auto d : dir)
        {
            Coord possibleMove = piece + d;
            if (!b.inside(possibleMove))
                continue;
            auto pieceTo = b.getPiece(possibleMove);
            if ((pieceTo == epcEmpty || getColor(pieceTo) == b.opposite()) && (pieceTo != epcBking && pieceTo != epcWking) && !inCheck(b, Move(piece, possibleMove)))
                v.emplace_back(piece, possibleMove);
        }
    }
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

void generateMove(std::vector<Move> &v, Board &b, int code)
{
    std::vector<Coord> pieceV = b.isWhite() ? findPieces(b, code) : findPieces(b, code + 7);

    switch (code)
    {

    case epcWpawn:
        pawnMove(v, b, pieceV);
        break;
    case epcWknight:
        squareMove(v, b, pieceV, dirKnight);
        break;
    case epcWbishop:
        rayMove(v, b, pieceV, dirBishop);
        break;
    case epcWrook:
        rayMove(v, b, pieceV, dirRook);
        break;
    case epcWqueen:
        rayMove(v, b, pieceV, dirQueen);
        break;
    case epcWking:
        squareMove(v, b, pieceV, dirKing);
        break;
    default:
        throw("Not a known pieceCode.");
    }
}

std::vector<Move> generateMoveList(Board &b)
{
    std::vector<Move> v;
    cachePositions(b);
    generateMove(v, b, epcWknight);
    if (!checkValidMoves(v, b))
    {
        assert(false);
    }
    generateMove(v, b, epcWbishop);
    if (!checkValidMoves(v, b))
    {
        assert(false);
    }
    generateMove(v, b, epcWqueen);
    if (!checkValidMoves(v, b))
    {
        assert(false);
    }
    generateMove(v, b, epcWrook);
    if (!checkValidMoves(v, b))
    {
        assert(false);
    }
    generateMove(v, b, epcWpawn);
    if (!checkValidMoves(v, b))
    {
        assert(false);
    }
    generateMove(v, b, epcWking);
    if (!checkValidMoves(v, b))
    {
        assert(false);
    }

    return v;
}


bool checkValidMoves(std::vector<Move> v, const Board &b)
{
    for (auto m : v)
    {
        auto piece = b.getPiece(m.to());
        if (piece == epcWking || piece == epcBking)
        {
            std::cout << b << std::endl;
            std::cout << m << std::endl;
            return false;
        }
    }
    return true;
}
} // namespace Search
