#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include "Piece.h"
#include "Move.h"

class Board {
    public:
      Board();
      Piece getPiece();
      Board makeMove(Move);
      Board unmakeMove(Move);

    private:
      Piece ** board;
};

#endif