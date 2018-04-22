#include "Piece.h"

Piece::Piece(ePieceCode code) : pieceCode(code) {}

Piece::Piece() : pieceCode(epcEmpty) {}

//returns true if there's no piece
bool Piece::empty() {
    return pieceCode == epcEmpty;
}

//returns true if the move was made by the right piece
bool Piece::operator==(const Piece& right)
{
    return pieceCode == right.getPieceCode();
}

//returns false if the move was not made by the right piece
bool Piece::operator!=(const Piece& right)
{
    return !(pieceCode == right.getPieceCode());
}

ePieceCode Piece::getColor()
{
    if(empty())
    {
        return epcEmpty;
    }
    return pieceCode > black ? ePieceCode::black : ePieceCode::white;
}

ePieceCode Piece::getPieceCode() const
{
    return pieceCode;
}