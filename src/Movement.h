#if !defined(MOVEMENT_H)
#define MOVEMENT_H
#include "Cache.h"
namespace Movement
{
struct MoveSet
{
    ePieceCode piece;
    std::vector<Coord> directions;
    bool ray;
    MoveSet(ePieceCode piece, std::vector<Coord> directions, bool ray) : piece(piece), directions(std::move(directions)), ray(ray) {}
    MoveSet(ePieceCode piece) : piece(piece) {}
    std::vector<Move> generateMoves(Board &b)
    {
        std::vector<Move> moves;
        MoveGenerator *moveGenerator = new BaseMoveGenerator(b, ray, directions, &moves);
        if (piece == epcWpawn) // Should this be a constexpr?
        {
            moveGenerator = new PawnMoveGenerator(b, &moves);
        }
        auto pieceCoords = Cache::findPieces(b, piece + (b.isWhite() ? 0 : 7));
        for (auto pieceCoord : pieceCoords)
        {
            moveGenerator->genMove(pieceCoord);
        }
        return moves;
    }
};

const std::vector<Coord> dirRook = {Coord(0, 1),
                                    Coord(0, -1),
                                    Coord(1, 0),
                                    Coord(-1, 0)};
const std::vector<Coord> dirBishop = {Coord(1, 1),
                                      Coord(1, -1),
                                      Coord(-1, -1),
                                      Coord(-1, 1)};
const std::vector<Coord> dirQueen = {Coord(1, 1),
                                     Coord(1, -1),
                                     Coord(-1, -1),
                                     Coord(-1, 1),
                                     Coord(0, 1),
                                     Coord(0, -1),
                                     Coord(1, 0),
                                     Coord(-1, 0)};
;
const std::vector<Coord> dirKnight = {Coord(1, 2),
                                      Coord(2, 1),
                                      Coord(2, -1),
                                      Coord(1, -2),
                                      Coord(-1, 2),
                                      Coord(-2, 1),
                                      Coord(-2, -1),
                                      Coord(-1, -2)};
const std::vector<Coord> dirKing = dirQueen;
const MoveSet Rook = MoveSet(epcWrook, dirRook, true);
const MoveSet Bishop = MoveSet(epcWbishop, dirBishop, true);
const MoveSet Queen = MoveSet(epcWqueen, dirQueen, true);
const MoveSet Knight = MoveSet(epcWknight, dirKnight, false);
const MoveSet King = MoveSet(epcWking, dirKing, false);
const MoveSet Pawn = MoveSet(epcWpawn);
const std::vector<MoveSet> movements = {Rook, Bishop, Queen, Knight, Pawn, King};
} // namespace Movement
#endif // MOVEMENT_H
