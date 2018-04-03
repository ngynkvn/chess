#ifndef PIECE_H
#define PIECE_H

enum ePieceType
{
    TYPE_NONE, 
    pawn, 
    knight, 
    bishop, 
    rook, 
    queen, 
    king
};

enum ePieceColor
{
    COLOR_NONE,
    white,
    black
};

class Piece {
    public:
    // implement getters and constructor. 
    // please make and use Piece as an IMMUTABLE data type (no modification allowed.)
    private:
      ePieceType pieceType;
      ePieceColor pieceColor;
};

#endif