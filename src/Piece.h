#ifndef PIECE_H
#define PIECE_H

/**
 * Adapted from https://chessprogramming.wikispaces.com/Pieces
 * */

enum pieceCode
{
  empty   =  0b00000000,
  white   =  0b11000000,
  Wpawn   =  0b11000001,
  Wknight =  0b11000010,
  Wbishop =  0b11000100,
  Wrook   =  0b11001000,
  Wqueen  =  0b11010000,
  Wking   =  0b11100000,
  pawn    =  0b00111111 & Wpawn,
  knight  =  0b00111111 & Wknight,
  bishop  =  0b00111111 & Wbishop,
  rook    =  0b00111111 & Wrook,
  queen   =  0b00111111 & Wqueen,
  King    =  0b00111111 & Wking,
  black   =  0b10000000,
  Bpawn   =  0b10111111 & Wpawn,
  Bknight =  0b10111111 & Wknight,
  Bbishop =  0b10111111 & Wbishop,
  Brook   =  0b10111111 & Wrook,
  Bqueen  =  0b10111111 & Wqueen,
  Bking   =  0b10111111 & Wking,
};
// 00 000000

//TODO test
bool piece_eq(pieceCode p1, pieceCode p2) {
  return p1 & p2 == p2;
}

/*
 * ePieceCode is a simple enumerator to allow for identification of pieces within the program. We separate pieces 
 * by color to distinguish between opposing sides.
 */
enum ePieceCode
{
  epcEmpty = -1,
  White = 0,
  epcWpawn,
  epcWknight,
  epcWbishop,
  epcWrook,
  epcWqueen,
  epcWking,
  Pawn = epcWpawn,
  Knight = epcWknight,
  Bishop = epcWbishop,
  Rook = epcWrook,
  Queen = epcWqueen,
  King = epcWking,
  Black = 7,
  epcBpawn,
  epcBknight,
  epcBbishop,
  epcBrook,
  epcBqueen,
  epcBking
,};

class Piece
{
private:
  ePieceCode pieceCode;

public:
    explicit Piece(ePieceCode);
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
