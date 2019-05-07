#include "Search.h"
#include <iostream>
#include <map>
#include <assert.h>
#include <algorithm>
#include <functional>
#include "MoveGenerator.h"
#include "Movement.h"
namespace Search
{
ePieceCode getColor(ePieceCode code)
{
    if (code == epcEmpty)
    {
        return epcEmpty;
    }
    return code > Black ? ePieceCode::Black : ePieceCode::White;
}

std::vector<Coord> wPawnCaptures = {Coord(1, 1),
                                    Coord(-1, 1)};
std::vector<Coord> bPawnCaptures = {Coord(1, -1),
                                    Coord(-1, -1)};

Coord firstPieceOnRay(Coord point, Coord dirRay, const Board &b)
{
    do
    {
        point = point + dirRay;
    } while (b.inside(point) && b.getPiece(point) == epcEmpty);
    return point;
}

bool checkHelper(const Board &b, Coord piece, std::vector<Coord> dirs, int epcCode, bool ray)
{
    auto code = static_cast<ePieceCode>(epcCode);
    return std::any_of(dirs.begin(), dirs.end(), [&](const Coord &dir) {
        Coord possibleMove = ray ? firstPieceOnRay(piece, dir, b) : piece + dir;
        return b.inside(possibleMove) && b.getPiece(possibleMove) == code;
    });
}
bool checkHelper(const Board &b, Coord piece, Movement::MoveSet m)
{
    return checkHelper(b, piece, m.directions, m.piece + (b.isWhite() ? White : Black), m.ray);
}

bool inCheck(Board &b, Move consideringMove)
{
    bool turnIsWhite = b.isWhite();
    int c = turnIsWhite ? White : Black;

    b.makeMove(consideringMove);
    std::vector<Coord> pieceCoords = Cache::findPieces(b, King + c);
    Coord piece = pieceCoords.at(0);

    bool result = std::any_of(Movement::movements.begin(), Movement::movements.end(), [&](Movement::MoveSet m) {
        return checkHelper(b, piece, m);
    });

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
    Cache::cachePositions(b);
    std::for_each(Movement::movements.begin(), Movement::movements.end(), [&](Movement::MoveSet m) {
        addMovesTo(v, m.generateMoves(b));
    });
    return v;
}

} // namespace Search
