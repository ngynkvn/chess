#ifndef PIECE_H
#define PIECE_H

/**
 * Adapted from https://chessprogramming.wikispaces.com/Pieces
 * */
enum ePieceCode
{
  epcEmpty = -1,
  white,
  epcWpawn,
  epcWknight,
  epcWbishop,
  epcWrook,
  epcWqueen,
  epcWking,
  black = 7,
  epcBpawn,
  epcBknight,
  epcBbishop,
  epcBrook,
  epcBqueen,
  epcBking
};

class Piece
{
private:
  ePieceCode pieceCode;

public:
  Piece(ePieceCode);
  Piece();
  bool empty();
  ePieceCode getColor();
  ePieceCode getPieceCode() const;
  bool operator==(const Piece &);
  bool operator!=(const Piece &);
};

#endif