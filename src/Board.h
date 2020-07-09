#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include "Piece.h"
#include "Move.h"
#include <ostream>
#include <vector>
#include <string>
#include <array>
#include <functional>

#define BOARD_SIZE 8

struct _Board {
    pieceCode state[64];

    coordinate first_coordinate_of(const pieceCode& p) const {
        auto iter = std::find_if(std::begin(state), std::end(state), std::bind(piece_eq, std::placeholders::_1, p));
        size_t index = iter - std::begin(state);
        return coordinate(index % BOARD_SIZE, index / BOARD_SIZE);
    }

    _Board from_fen(std::string) const;
    pieceCode piece_at(const coordinate&) const;
    bool move(const Move&) const;
};
class Board
{
public:
  Board();
  Board(const Board &);
  std::array<ePieceCode, 64> getBoard() const;
  coordinate getKing(ePieceCode) const;
  ePieceCode getPiece(const coordinate &) const;
  Board &makeMove(const Move &);
  void unmakeMove();
  bool inside(const coordinate &c) const;
  bool isWhite() const;
  ePieceCode currColor() const { return whiteTurn ? White : Black; };
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

inline ePieceCode Board::getPiece(const coordinate &c) const
{
  auto [x, y] = c;
  return board[(y << 3) + x];
}
inline bool Board::inside(const coordinate &c) const
{
  auto [x, y] = c;
  return x > -1 && x < 8 && y > -1 && y < 8;
};
inline std::array<ePieceCode, 64> Board::getBoard() const
{
    return this->board;
}

#endif // BOARD_H
