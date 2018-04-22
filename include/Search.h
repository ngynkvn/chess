#ifndef SEARCH_H
#define SEARCH_H

#include "Move.h"
#include "Piece.h"
#include "Board.h"
#include <vector>

namespace Search
{

std::vector<Move> generateMoveList(const Board &);
std::vector<Coord> findPieces(Board, ePieceCode);
bool inCheck(Board, Move);
}

#endif
