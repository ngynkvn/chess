#include <iostream>
#include "Move.h"
#include "Board.h"
#include "Search.h"
#include "Evaluation.h"
int main() {
    Move m(3,1,3,3);
    Board b;
    std::vector<Move> list = Search::generateMoveList(b);
    b = b.makeMove(list[0]);
    list = Search::generateMoveList(b);
    for(auto i = list.begin(); i != list.end(); i++)
    {
        cout << b.makeMove(*i) << endl;
    }
}
