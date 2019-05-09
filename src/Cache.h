
#if !defined(CACHE_H)
#define CACHE_H
#include <map>
#include "Move.h"
#include "Piece.h"
#include "Board.h"

namespace Cache
{

std::vector<Coord> findPieces(Board &b, int piece)
{
    std::vector<Coord> v;
    auto board = b.getBoard();
    for (int i = 0; i < 64; i++){
            if (board[i] == piece)
            {
                v.emplace_back(i % 8, i / 8);
            }
        }
    return v;
}
} // namespace Cache

#endif // CACHE_H