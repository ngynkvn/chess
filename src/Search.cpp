#include "Search.h"
#include <iostream>
#include <map>
#include <assert.h>
#include <algorithm>
#include <functional>
#include "MoveGenerator.h"

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

    Coord wPawnPush = Coord(0, 1);
    Coord bPawnPush = Coord(0, -1);
    std::vector<Coord> wPawnCaptures = {Coord(1, 1),
                                        Coord(-1, 1)};
    std::vector<Coord> bPawnCaptures = {Coord(1, -1),
                                        Coord(-1, -1)};
                                        
    struct Movement {
        ePieceCode piece;
        std::vector<Coord> directions;
        bool ray;
        Movement(ePieceCode piece, std::vector<Coord> directions, bool ray) : piece(piece), directions(std::move(directions)), ray(ray) {}
        Movement(ePieceCode piece) : piece(piece) {}
        std::vector<Move> generateMoves(Board& b)
        {
            std::vector<Move> moves;
            MoveGenerator* moveGenerator = new BaseMoveGenerator(b, ray, directions, &moves);
            if(piece == epcWpawn)
            {
                moveGenerator = new PawnMoveGenerator(b, &moves);
            }
            auto pieceCoords = findPieces(b, piece + (b.isWhite() ? 0 : 7));
            for (auto pieceCoord : pieceCoords)
            {
                moveGenerator->genMove(pieceCoord);
            }
            return moves;
        }
        
    };

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
                               Coord(-1, 0)};;
std::vector<Coord> dirKnight = {Coord(1, 2),
                            Coord(2, 1),
                            Coord(2, -1),
                            Coord(1, -2),
                            Coord(-1, 2),
                            Coord(-2, 1),
                            Coord(-2, -1),
                            Coord(-1, -2)};
std::vector<Coord> dirKing = dirQueen;
Movement movementRook = Movement(epcWrook, dirRook, true);
Movement movementBishop = Movement(epcWbishop, dirBishop, true);
Movement movementQueen = Movement(epcWqueen, dirQueen, true);
Movement movementKnight = Movement(epcWknight, dirKnight, false);
Movement movementKing = Movement(epcWking, dirKing, false);
Movement movementPawn = Movement(epcWpawn);
Movement movements[] = {movementRook, movementBishop, movementQueen, movementKnight, movementPawn, movementKing};

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

Coord firstPieceOnRay(Coord point, Coord dirRay, const Board& b)
{
    do {
        point += dirRay;
    } while (b.inside(point) && b.getPiece(point) == epcEmpty);
    return point;
}

bool checkHelper(const Board &b, Coord piece, std::vector<Coord> dirs, int epcCode, bool ray)
{
    auto code = static_cast<ePieceCode>(epcCode);
    return any_of(dirs.begin(), dirs.end(), [&](const Coord& dir) {
        Coord possibleMove = ray ? firstPieceOnRay(piece, dir, b) : piece + dir;
        return b.inside(possibleMove) && b.getPiece(possibleMove) == code;
    });
}
bool checkHelper(const Board &b, Coord piece, Movement m)
{
    return checkHelper(b, piece, m.directions, m.piece + (b.isWhite() ? white : black), m.ray);
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

    std::vector<Coord> pieceCoords = findPieces(b, epcWking + c);
    b.makeMove(consideringMove);

    Coord piece = pieceCoords[0];

    c = turnIsWhite ? black : white;
    bool result = std::any_of(movements, movements + 6, [&](Movement m) {
        return checkHelper(b, piece, m);
    }) || checkHelper(b, piece, turnIsWhite ? wPawnCaptures : bPawnCaptures, epcWpawn + c, false);
    
    b.unmakeMove();
    return result;
}

void addMovesTo(std::vector<Move> &v, std::vector<Move> moves)
{
    v.insert(v.end(), moves.begin(), moves.end());
}

std::vector<Move> generateMoveList(Board &b)
{
    std::vector<Move> v;
    cachePositions(b);
    std::for_each(movements, movements+6, [&](Movement m) {
        addMovesTo(v, m.generateMoves(b));
    });
    return v;
}


} // namespace Search
