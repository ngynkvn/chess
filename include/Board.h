#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include "Piece.h"
#include "Move.h"
#include <ostream>
#include <string>

using namespace std;

class Board
{
    public:
        Board();
        Board(Piece** newBoard);
        Piece** getBoard();
        Piece getPiece(Coord c) const;
        Board makeMove(Move m) const;
        Board unmakeMove(Move m) const;
        friend ostream &operator<<(ostream&, const Board&);
      private:
        Piece** board = 0;

};

#endif // BOARD_H
