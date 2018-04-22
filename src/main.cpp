#include <iostream>
#include "Move.h"
#include "Board.h"
#include "Search.h"
#include "Evaluation.h"
#include <algorithm>
using namespace std;

/*
Returns whether or not the move given in the parameters
is actually a possible move on the given board
*/
bool validMove(Board b,Move m)
{
    std::vector<Move> list = Search::generateMoveList(b);
    return find(list.begin(), list.end(), m) != list.end();
}

/*
User Interface for the game
*/
int main()
{
    Board b;
    string in;
    cout << b << endl;
    while (true)
    {
        cout << "Your move:";
        cin >> in;
        Move m(in);
        if(validMove(b,m))
        {
            b = b.makeMove(m);
            cout << b << endl;
            cout << "Opponent is thinking.." << endl;
            b = b.makeMove(mini_max(b));
            cout << b << endl;
        }
    }
}
