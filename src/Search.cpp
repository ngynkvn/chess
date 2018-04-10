#include "Search.h"
#include <iostream>
namespace Search
{
void pawnMoves(std::vector<Move> &v, const Board &b)
{
    //loop through and find pawn pieces
    Piece pawns[8];
    int i = 0;
    Piece **arr = b.getBoard();
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            Piece p = arr[row][col];
            if (p.getPieceCode() == epcWpawn) //found a white pawn
            {
                pawns[i++] = arr[row][col];
            }
        }
    }
    for (i = 0; i < pawns.length; i++){
    }
}

std::vector<Move> generateMoveList(const Board &b)
{
    std::vector<Move> v;
    pawnMoves(v, b);
    return v;
}

}