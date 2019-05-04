
#if !defined(CACHE_H)
#define CACHE_H
#include <map>
#include "Move.h"
#include "Piece.h"
#include "Board.h"

namespace Cache
{

std::map<ePieceCode, std::vector<Coord>> cachePos;

void cachePositions(Board &b)
{
    cachePos.clear();
    ePieceCode **board = b.getBoard();
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != epcEmpty)
            {
                cachePos[board[i][j]].emplace_back(j, i);
            }
        }
}

std::vector<Coord> findPieces(Board &b, int piece)
{
    return cachePos[static_cast<ePieceCode>(piece)];
}

} // namespace Cache

#endif // CACHE_H