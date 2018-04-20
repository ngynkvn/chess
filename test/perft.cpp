#include "Board.h"
#include "Search.h"
#include <vector>
typedef unsigned long long u64;

//Based off perft function here:
//http://chessprogramming.wikispaces.com/Perft
u64 perft(Board b, int depth, int& captures)
{
    if(depth == 1){
        std::vector<Move> moves = Search::generateMoveList(b);
        for (auto i = moves.begin(); i != moves.end(); i++)
        {
            if(b.getPiece((*i).to()) != epcEmpty)
                captures++;
        }
        return moves.size();
    }

    u64 nodes = 0;
    std::vector<Move> moves = Search::generateMoveList(b);
    for (auto i = moves.begin(); i != moves.end(); i++)
    {
        Board next = b.makeMove(*i);
        nodes += perft(next, depth - 1, captures);
    }
    return nodes;
}
