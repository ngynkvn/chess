#ifndef PIECE_H
#define PIECE_H

class Piece {
    public:
    // implement getters and constructor. 
    // please make and use Piece as an IMMUTABLE data type (no modification allowed.)
    private:
      ePieceType pieceType;
      ePieceColor pieceColor;
};

enum ePieceType
{
    none, 
    pawn, 
    knight, 
    bishop, 
    rook, 
    queen, 
    king
};

enum ePieceColor 
{
    none,
    white,
    black
}

#endif