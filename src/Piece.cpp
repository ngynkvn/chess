#include "Piece.h"

Piece::Piece(ePieceCode code) : pieceCode(code) {}

Piece::Piece() : pieceCode(epcEmpty) {}

//Returns true if the piece position is empty
//Otherwise, it returns false
bool Piece::empty() {
    return pieceCode == epcEmpty;
}

//Returns true if the move was made by the right piece
//Otherwise, it returns false
bool Piece::operator==(const Piece& right)
{
    return pieceCode == right.getPieceCode();
}

//Returns false if the move was not made by the right piece
//Otherwise, it returns true
bool Piece::operator!=(const Piece& right)
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
    return pieceCode > black ? ePieceCode::black : ePieceCode::white;
}

//Returns the piececode of the piece
ePieceCode Piece::getPieceCode() const
{
    return pieceCode;
}