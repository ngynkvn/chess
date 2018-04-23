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
    Board b;
    // b = b.makeMove(Move("e2e4"))
    //      .makeMove(Move("b7b5"))
    //      .makeMove(Move("f1b5"))
    //      .makeMove(Move("f7f6"))
    //      .makeMove(Move("d1h5"));
    //      cout << b;
    // cout << Search::inCheck(b) << endl;
    // cout << Search::inCheck(b,Move("g4g5")) << endl;
    // cout << b << evaluate(b) << endl;
    // cout << b.makeMove(Move("e2e4"));
    // cout << evaluate(b.makeMove(Move("e2e4"))) << endl;
    // cout << b.makeMove(Move("e2e4")).makeMove(Move("e7e5")) ;
    // cout << evaluate(b.makeMove(Move("e2e4")).makeMove(Move("e7e5"))) << endl;

    selfPlay();
    // gameLoop();
}
