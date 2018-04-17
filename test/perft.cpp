#include "Board.h"
#include "Search.h"
typedef unsigned long long u64;

//Based off perft function here:
//http://chessprogramming.wikispaces.com/Perft
u64 perft(Board b, int depth)
{
    if(depth == 1)
        return Search::generateMoveList(b).size();

    u64 nodes = 0;
    std::vector<Move> moves = Search::generateMoveList(b);
    for (auto i = moves.begin(); i != moves.end(); i++)
    {
        Board next = b.makeMove(*i);
        nodes += perft(next, depth - 1);
    }
    return nodes;
}