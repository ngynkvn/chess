#include "Board.h"
#include "Search.h"
#include<iostream>
#include <vector>
typedef unsigned long long u64;

//Based off perft function here:
//http://chessprogramming.wikispaces.com/Perft

/*
 * Perft functions allow for the testing of move generation algorithms and verify that they correctly 
 * generate all possible board states from a given position up to a certain depth.
 * We have included helper code to also test amounts of captures and checks to further validify our code.
 */
u64 perft(Board b, int depth, int &captures, int &checks)
{
    if (depth == 1)
    {
        std::vector<Move> moves = Search::generateMoveList(b);
        for (auto i = moves.begin(); i != moves.end(); i++)
        {
            if (b.getPiece((*i).to()) != epcEmpty)
                captures++;
            if (Search::inCheck(b,*i)) 
                checks++;
        }
        return moves.size();
    }

    u64 nodes = 0;
    std::vector<Move> moves = Search::generateMoveList(b);
    for (auto i = moves.begin(); i != moves.end(); i++)
    {
        b.makeMove(*i);
        nodes += perft(b, depth - 1, captures, checks);
        b.unmakeMove();
    }
    return nodes;
}
u64 perft(Board b, int depth, int &captures)
{
    if (depth == 1)
    {
        std::vector<Move> moves = Search::generateMoveList(b);
        for (auto i = moves.begin(); i != moves.end(); i++)
        {
            if (b.getPiece((*i).to()) != epcEmpty)
                captures++;
        }
        return moves.size();
    }

    u64 nodes = 0;
    std::vector<Move> moves = Search::generateMoveList(b);
    for (auto i = moves.begin(); i != moves.end(); i++)
    {
        b.makeMove(*i);
        nodes += perft(b, depth - 1, captures);
        b.unmakeMove();
    }
    return nodes;
}
u64 perft(Board b, int depth)
{
    if (depth == 1)
    {
        std::vector<Move> moves = Search::generateMoveList(b);
        return moves.size();
    }

    u64 nodes = 0;
    std::vector<Move> moves = Search::generateMoveList(b);
    for (auto i = moves.begin(); i != moves.end(); i++)
    {
        b.makeMove(*i);
        nodes += perft(b, depth - 1);
        b.unmakeMove();
    }
    return nodes;
}
