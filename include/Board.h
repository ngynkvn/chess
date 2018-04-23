#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include "Piece.h"
#include "Move.h"
#include <ostream>
#include <string>


/** 
 * Board class holds important information pertaining to the existing state of the game.
 * This is a data-type that is treated as an immutable throughout the code, however it is important to note that 
 * it is actually not immutable and has various methods for setting internal state.
 * 
 * In the future we will work to make this data-type 100% immutable to allow for cleaner code.
 */
class Board
{
public:
  Board();
  Board(const Board &);
  ~Board();
  Piece **getBoard() const;
  Piece getPiece(Coord) const;
  Board makeMove(Move) const;
  Board unmakeMove(Move) const;
  bool inside(Coord) const;
  bool isWhite() const;
  ePieceCode currColor() { return whiteTurn ? white : black; };
  void setTurn(bool);
  ePieceCode opposite() const;
  ePieceCode same() const;
  Move getPrevMove() const;
  void setPrevMove(Move);
  Board &operator=(const Board &); //copy assignment constructor.
  friend ostream &operator<<(ostream &, const Board &);

private:
  Piece **board = 0;
  bool whiteTurn;
  Move prevMove = Move(-1, -1, -1, -1);
};

#endif // BOARD_H
