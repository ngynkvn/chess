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
  Board(const Board&);
  ~Board();
  Piece **getBoard() const;
  Piece getPiece(Coord) const;
  Board makeMove(Move) const;
  Board unmakeMove(Move) const;
  bool inside(Coord) const;
  bool isWhite() const;
  ePieceCode currColor() {return whiteTurn ? white:black;};
  void setTurn(bool);
  ePieceCode opposite() const;
  ePieceCode same() const;
  Move getPrevMove() const;
  void setPrevMove(Move) ;
  Board &operator= (const Board &); //copy assignment constructor.
  friend ostream &operator<<(ostream &, const Board &);

private:
  Piece **board = 0;
  bool whiteTurn;
  Move prevMove = Move(-1,-1,-1,-1);
};

#endif // BOARD_H
