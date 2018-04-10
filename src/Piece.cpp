#include "Piece.h"

Piece::Piece(ePieceCode code) : pieceCode(code) {}

Piece::Piece() : pieceCode(epcEmpty) {}

bool Piece::empty() {
    return pieceCode == epcEmpty;
}

ePieceCode Piece::getColor()
{
    if(empty())
    {
        return epcEmpty;
    }
    return pieceCode > black ? ePieceCode::black : ePieceCode::white;
}

ePieceCode Piece::getPieceCode()
{
    return pieceCode;
}