#include <iostream>
#include "Move.h"
#include "Board.h"
#include "Search.h"
#include "Evaluation.h"
int main() {
    Move m(3,1,3,3);
    Board b;
    cout << b << endl;
    cout << evaluate(b) << endl;
    Search::generateMoveList(b);
    b = b.makeMove(m);
    cout << b;
    cout << evaluate(b);
}