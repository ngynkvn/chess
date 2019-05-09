#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include "Piece.h"
#include "Move.h"
#include <ostream>
#include <vector>
#include <string>
#include <array>

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
  std::array<ePieceCode, 64> getBoard() const;
  ePieceCode getPiece(const Coord &) const;
  Board &makeMove(const Move &);
  void unmakeMove();
  bool inside(const Coord &c) const;
  bool isWhite() const;
  ePieceCode currColor() { return whiteTurn ? White : Black; };
  void setTurn(bool);
  ePieceCode opposite() const;
  ePieceCode same() const;
  Move getPrevMove() const;
  void setPrevMove(Move);
  friend std::ostream &operator<<(std::ostream &, const Board &);

private:
  std::array<ePieceCode,64> board;
  bool whiteTurn = true;
  std::vector<Move> history;
  Move prevMove = Move(-1, -1, -1, -1);
  ePieceCode prevCapture = epcEmpty;
  std::vector<ePieceCode> captures;
};

inline ePieceCode Board::getPiece(const Coord &c) const
{
  auto [x, y] = c;
  return board[(y << 3) + x];
}
inline bool Board::inside(const Coord &c) const
{
  auto [x, y] = c;
  return x > -1 && x < 8 && y > -1 && y < 8;
};
inline std::array<ePieceCode, 64> Board::getBoard() const
{
    return this->board;
}

#endif // BOARD_H
