#include <iostream>
#include "Move.h"
#include "Board.h"
#include "Search.h"
#include "Evaluation.h"
#include <algorithm>
using namespace std;

bool validMove(Board b, Move m)
{
    std::vector<Move> list = Search::generateMoveList(b);
    return find(list.begin(), list.end(), m) != list.end();
}

void gameLoop()
{
    Board b;
    string in;
    cout << b << endl;
    while (true)
    {
        Move m(-1,-1,-1,-1);

        try {
        cout << "Your move:";
        cin >> in;
        m = Move(in);
        } catch (exception e)
        {}

        if (validMove(b, m))
        {
            b = b.makeMove(m);
            cout << b << endl;
            if(Search::generateMoveList(b).size() != 0){
            cout << "Opponent is thinking.." << endl;
            b = b.makeMove(mini_max(b));
            cout << b << endl;
            } else {
                break;
            }
        }
    }
    cout << "Game over!" << endl;
}

int main()
{
    // Board b;
    gameLoop();
}
