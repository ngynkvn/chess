#ifndef PIECE_H
#define PIECE_H

/**
 * Adapted from https://chessprogramming.wikispaces.com/Pieces
 * */

/*
 * ePieceCode is a simple enumerator to allow for identification of pieces within the program. We separate pieces 
 * by color to distinguish between opposing sides.
 */
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
  void setPieceCode(ePieceCode c);
  bool operator==(const Piece &) const;
  bool operator==(const ePieceCode &) const;
  bool operator!=(const Piece &) const;
};

#endif
