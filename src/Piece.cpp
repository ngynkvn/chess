#include "Piece.h"

Piece::Piece(ePieceCode code) : pieceCode(code) {}

Piece::Piece() : pieceCode(epcEmpty) {}

bool Piece::empty() {
    return pieceCode == epcEmpty;
}

bool Piece::operator==(const Piece& right)
{
    return pieceCode == right.getPieceCode();
}
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