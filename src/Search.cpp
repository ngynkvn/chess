#include "Search.h"
#include <iostream>
namespace Search
{

Coord dirKing[] = {Coord(-1, -1),
                   Coord(-1, 0),
                   Coord(-1, 1),
                   Coord(0, 1),
                   Coord(0, -1),
                   Coord(1, -1),
                   Coord(1, 0),
                   Coord(1, 1)};
                   
std::vector<Coord> findPieces(const Board &b, ePieceCode piece)
{
    Piece **board = b.getBoard();
    std::vector<Coord> pieces;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j].getPieceCode() == piece)
            {
                pieces.push_back(Coord(j, i));
            }
        }
    }
    return pieces;
}

//Dumbly adds all possible moves for King without considering castling and whether the move will place him in check.
void kingMoves(std::vector<Move> &v, const Board &b)
{
    std::vector<Coord> pieceV = findPieces(b, epcWking);

    if (pieceV.size() == 1)
    {
        Coord piece = pieceV[0];
        for (int i = 0; i < 8; i++)
        {
            Coord possibleMove = piece + dirKing[i];
            if (b.inside(possibleMove) && (b.getPiece(possibleMove).empty() || b.getPiece(possibleMove).getColor() == b.opposite()))
            {
                v.push_back(Move(piece, possibleMove));
            }
        }
    }
}

std::vector<Move> generateMoveList(const Board &b)
{
    std::vector<Move> v;
    kingMoves(v, b);
    return v;
}
}