#include "Piece.h"

Piece::Piece(ePieceCode code) : pieceCode(code) {}

Piece::Piece() : pieceCode(epcEmpty) {}

//Returns true if the piece position is empty
//Otherwise, it returns false
bool Piece::empty() {
    return pieceCode == epcEmpty;
}

//TODO test
bool piece_eq(pieceCode p1, pieceCode p2) {
  return (p1 & p2) == p2;
}

//Returns true if the move was made by the right piece
//Otherwise, it returns false
bool Piece::operator==(const Piece& right) const
{
    return pieceCode == right.getPieceCode();
}

bool Piece::operator==(const ePieceCode& code) const
{
    return pieceCode == code;
}

//Returns false if the move was not made by the right piece
//Otherwise, it returns true
bool Piece::operator!=(const Piece& right) const
{
    return !(pieceCode == right.getPieceCode());
}

//Returns piece color if the coordinate on the board is not empty
ePieceCode Piece::getColor()
{
    if (empty())
    {
        return epcEmpty;
    }
    return pieceCode > Black ? ePieceCode::Black : ePieceCode::White;
}

//Returns the piececode of the piece
ePieceCode Piece::getPieceCode() const
{
    return pieceCode;
}

void Piece::setPieceCode(ePieceCode c) 
{
    pieceCode = c;
}
