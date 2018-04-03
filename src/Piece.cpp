#include "Piece.h"

Piece::Piece(ePieceCode code) : pieceCode(code)
{
}

int Piece::getColor()
{
    return pieceCode > black ? ePieceCode::black : ePieceCode::white;
}

int Piece::getPiece()
{
    return pieceCode;
}