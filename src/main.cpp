#include <iostream>
#include "Piece.h"
#include "Move.h"
#include "Board.h"

int main() {
    Move m(1,1,1,2);
    Board b;
    cout << b;
    b.makeMove(m);
    cout << b;
}