#include <iostream>
#include "Move.h"
#include "Board.h"
#include "Search.h"

int main() {
    Move m(1,1,1,2);
    Board b;
    cout << b;
    Search::generateMoveList(b);
    // b.makeMove(m);
    // cout << b;
}