#include "Board.h"
#include "Search.h"
#include "Move.h"
#include "pertf.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

//Based off perft function here:
//http://chessprogramming.wikispaces.com/Perft

/*
 * Perft functions allow for the testing of move generation algorithms and verify that they correctly 
 * generate all possible board states from a given position up to a certain depth.
 * We have included helper code to also test amounts of captures and checks to further validify our code.
 */

u64 perft_nodes(Board &b, int depth, u64 &captures, u64 &checks)
{
    std::vector<Move> moves = Search::generateMoveList(b);
    if (depth == 1)
    {
        for (auto i : moves)
        {
            if(b.getPiece(i.to) != epcEmpty) 
                captures++;
        }
        return moves.size();
    }

    u64 nodes = 0;
    for (auto i : moves)
    {
        b.makeMove(i);
        nodes += perft_nodes(b, depth - 1, captures, checks);
        b.unmakeMove();
    }
    return nodes;
}

std::tuple<u64, u64, u64> perft(Board &b, int depth)
{
    u64 captures = 0;
    u64 checks = 0;
    u64 nodes = perft_nodes(b, depth, captures, checks);
    return std::make_tuple(nodes, captures, checks);
}