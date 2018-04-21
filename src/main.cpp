#include <iostream> 
#include "Move.h"
#include "Board.h"
#include "Search.h"
#include "Evaluation.h"
int main() {
    // Move m(3,1,3,3);
    Board b;
    b = b.makeMove(mini_max(b));
    // b = b.makeMove(mini_max(b,4, -10000, 10000, true).first);
    // b = b.makeMove(mini_max(b,4, -10000, 10000, true).first);
    // b = b.makeMove(mini_max(b,4, -10000, 10000, true).first);
    // b = b.makeMove(Move(7,6,7,5));
    // b = b.makeMove(Move(2,0,7,5));
    // b = b.makeMove(Move(2, 6, 2, 4));
    cout << b;
    // std::vector<Move> list = Search::generateMoveList(b);
    //whites turn
    // for(auto i = list.begin(); i != list.end(); i++)
    // {
    //     // std::string prettyPrint[] = {" ", "♙", "♘", "♗", "♖", "♕", "♔",
    //     //                      " ", "♟", "♞", "♝", "♜", "♛", "♚"};
    //     // Move move = *i;
    //     // cout << prettyPrint[b.getPiece(move.from()).getPieceCode()] <<" Moved from:" << move.from() << " to: " << move.to() << endl;
    //     // cout << Search::generateMoveList(b.makeMove(*i)).size() << endl;
        // cout << (b.makeMove(*i)) << endl;
    // }
}
