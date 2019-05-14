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
bool validMove(Board& b, Move m)
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
        if(in == "q")
            return;
        m = Move(in);
        } catch (exception& e)
        {}

        if (validMove(b, m))
        {
            b.makeMove(m);
            cout << b << endl;
            if(!Search::generateMoveList(b).empty()){
            cout << "Opponent is thinking.." << endl;
            b.makeMove(mini_max(b, 5));
            cout << b << endl;
            } else {
                break;
            }
        }
    }
    cout << "Game over!" << endl;
}

// void selfPlay()
// {
//     Board b;
//     while(!Search::generateMoveList(b).empty()){
//         cout << b;
//         cout << evaluate(b) << endl;
//         // b = b.makeMove(mini_max(b));
//     }
//     cout << b;
// }

int main()
{
    // Board b;
    // gameLoop();
    Board b;
    b.makeMove(Move("e2e4"));
    b.makeMove(Move("a7a5"));
    b.makeMove(Move("e4e5"));
    Move dp("d7d5");
    dp.moveType = DoublePush;
    b.makeMove(dp);
    cout << b << endl;
    for(auto x : Search::generateMoveList(b))
        cout << x << endl;
	// mini_max(b, 3);
    // b.makeMove(Move("e2e4"));
    // b.makeMove(mini_max(b, 1));
    // b.makeMove(Move("d2d4"));
    // cout << b << endl;
    // b.unmakeMove();
    // cout << b << endl;
//     selfPlay();
//    gameLoop();
}
