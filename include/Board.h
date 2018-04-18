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
  Board(Piece **);
  Board copy();
  Piece **getBoard() const;
  Piece getPiece(Coord) const;
  Board makeMove(Move) const;
  Board unmakeMove(Move) const;
  bool inside(Coord) const;
  bool isWhite();
  void setTurn(bool);
  ePieceCode opposite() const;
  friend ostream &operator<<(ostream &, const Board &);

private:
  Piece **board = 0;
  bool whiteTurn;
};

#endif // BOARD_H
