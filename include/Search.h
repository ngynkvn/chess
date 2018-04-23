#ifndef SEARCH_H
#define SEARCH_H

#include "Move.h"
#include "Piece.h"
#include "Board.h"
#include <vector>

/* 
 * Search is a namespace that holds all logic related to move generation. Inside the CPP file are a multitude of methods 
 * that support the fundamental generateMoveList() method which allows for the chess AI to actually play.
 * 
 */
namespace Search
{
std::vector<Move> generateMoveList(const Board &);
std::vector<Coord> findPieces(const Board&, ePieceCode);
bool inCheck(Board, Move);
bool inCheck(Board);
}

#endif
