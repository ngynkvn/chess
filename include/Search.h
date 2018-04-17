#ifndef SEARCH_H
#define SEARCH_H

#include "Move.h"
#include "Piece.h"
#include "Board.h"
#include <vector>

namespace Search
{
    Coord dirKing[] = { Coord(-1, -1),
                        Coord(-1, 0),
                        Coord(-1, 1),
                        Coord(0, 1),
                        Coord(0, -1),
                        Coord(1, -1),
                        Coord(1, 0),
                        Coord(1, 1)
                      };
std::vector<Move> generateMoveList(const Board &);
}

#endif