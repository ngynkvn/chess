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
MoveSet Rook = MoveSet(ePieceCode::Rook, dirRook, true);
MoveSet Bishop = MoveSet(ePieceCode::Bishop, dirBishop, true);
MoveSet Queen = MoveSet(ePieceCode::Queen, dirQueen, true);
MoveSet Knight = MoveSet(ePieceCode::Knight, dirKnight, false);
MoveSet King = MoveSet(ePieceCode::King, dirKing, false);
MoveSet Pawn = MoveSet(ePieceCode::Pawn);
const std::vector<MoveSet> movements = {Rook, Bishop, Queen, Knight, Pawn, King};
} // namespace Movement
#endif // MOVEMENT_H
