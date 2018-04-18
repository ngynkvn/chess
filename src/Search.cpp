#include "Search.h"
#include <iostream>

namespace Search
{

bool hasMoved(Piece p){

}

// evaluates whether if moving a piece will IMMEDIATLY expose the king to a thretening piece
bool ifMoveInCheck(Piece p){

}

//loop through and find pawn pieces and add epcWpawn x,y coord to vector coord
void pawnMoves(std::vector<Move> &v, const Board &b)
{
    Piece pawns[8];
    //std::vector<int> coord; //this is going to be organized as col, row to be x,y
    //int epcWpawnCtr = 0;
    Piece ** board = b.getBoard();
    //note: I am assuming board[row][col] is where row is y and col is x
    for (int row=0;row<8;row++)
    {
        for (int col=0;col<8;col++)
        {
            Piece p = board[row][col];
            if (p.getPieceCode()==epcWpawn) //found a white pawn
            {
                epcWpawnCtr++;
                Move m;
                //Move m2; // I don't know how if i can reconstruct m so just for now here cause idk
                //pawns[i++] = board[row][col]; //kevin code
                int nextRow = row, nextRow2 = row;
                nextRow--; //next row from the perspective of white
                nextRow2--; nextRow2--; //next next row from the perspective of white
                int coll=col, cola=col, colr=col;
                coll--;colr++; //left and right

                if(nextRow>=0 && nextRow <= 7){

                    // Determines if there is a valid move to the square up and left
                    if(coll >=0 && coll <=7){
                        Piece l = board[nextRow][coll]; // the square that is up left of the pawn from perspective of white
                        if(!ifMoveInCheck(p)){
                            if(l.getPieceCode()== 7) // in piece.h black = 7
                            {
                                m(col,row,coll,nextRow); // this is x,y,x,y from perspective of white
                                v.push_back(m);
                            }
                        }
                    }

                    if(cola>=0 && cola <=7){
                        Piece a = board[nextRow][col]; // the square that is directly up of the pawn from perspective of white
                        if(!ifMoveInCheck(p)){
                            if(a.getPieceCode()== -1) // in piece.h empty square = -1
                            {
                                Piece a2 = board[nextRow2][col]; // the two square move
                                m(col,row,cola,nextRow); // this is x,y,x,y from perspective of white
                                v.push_back(m);
                                if(a2.getPieceCode()==-1 && !hasMoved(p)){
                                    m(col,row,col,nextRow2); // this is x,y,x,y from perspective of white
                                    v.push_back(m2);
                                }
                            }
                        }
                    }
                    if(colr>=0 && colr <=7){
                        Piece r = board[nextRow][colr]; // the square that is up right of the pawn from perspective of white
                        if(!ifMoveInCheck(p)){
                            if(r.getPieceCode()== 7) // in piece.h black = 7
                            {
                                m(col,row,colr,nextRow); // this is x,y,x,y from perspective of white
                                v.push_back(m);
                            }
                        }
                    }
                }
                    //Code that needs to implement ompesant rule. I don't know how to see previous move
                    //YOUR CODE HERE

            }
        }
    }


    for (i = 0; i < pawns.length; i++){
    }

    
}

std::vector<Move> generateMoveList(const Board &b)
{
    std::vector<Move> v;
    pawnMoves(v, b);
    knightMoves
    return v;
}

}
