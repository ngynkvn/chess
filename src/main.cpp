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
bool validMove(Board b, Move m)
{
    std::vector<Move> list = Search::generateMoveList(b);
    return find(list.begin(), list.end(), m) != list.end();
}

/*
Loops the game interface to allow user to select move
and then if AI has available moves to make, the AI responds
*/
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

void selfPlay()
{
    Board b;
    while(Search::generateMoveList(b).size() != 0){
        cout << b;
        b = b.makeMove(mini_max(b));
    }
    cout << b;
}

int main()
{
    // selfPlay();
    gameLoop();
}
