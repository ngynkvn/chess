#include "Search.h"
#include <iostream>

namespace Search
{

std::vector<Coord> dirQueen ={Coord(1,1),
                            Coord(1,-1),
                            Coord(-1,-1),
                            Coord(-1,1),
                            Coord(0,1),
                            Coord(0,-1),
                            Coord(1,0),
                            Coord(-1,0)};

std::vector<Coord> dirBishop  ={Coord(1,1),
                                Coord(1,-1),
                                Coord(-1,-1),
                                Coord(-1,1)};

std::vector<Coord> dirWPawnM = {Coord(0,1)};
std::vector<Coord> dirWPawnC = {Coord(1,1),
                                Coord(-1,1)};
std::vector<Coord> dirWPawnS  = {Coord(0,2)};
std::vector<Coord> dirBPawnM  = {Coord(0,-1)};
std::vector<Coord> dirBPawnC  = {Coord(1,-1),
                                Coord(-1,-1)};
std::vector<Coord> dirBPawnS  = {Coord(0,-2)};

std::vector<Coord> dirKnight  = {Coord(1,2),
                                 Coord(2,1),
                                 Coord(2,-1),
                                 Coord(1,-2),
                                 Coord(-1,2),
                                 Coord(-2,1),
                                 Coord(-2,-1),
                                 Coord(-1,-2)};

std::vector<Coord> dirRook ={Coord(0,1),
                            Coord(0,-1),
                            Coord(1,0),
                            Coord(-1,0)};

std::vector<Coord> dirKing = {Coord(-1, -1),
                              Coord(-1, 0),
                              Coord(-1, 1),
                              Coord(0, 1),
                              Coord(0, -1),
                              Coord(1, -1),
                              Coord(1, 0),
                              Coord(1, 1)};


void rayMove(std::vector<Move> &v, Board b, std::vector<Coord> &pieceV, std::vector<Coord> dir )
{
    Coord ctr;

    for(unsigned int i=0; i<pieceV.size(); i++)
    {
        Coord piece = pieceV[i];
        for(unsigned int j=0; j<dir.size(); j++) // the j< expression is not correct. should be j<dir.size()
        {
            ctr = dir[j];
            Coord possibleMove = piece + dir[j];
            while(b.inside(possibleMove) && (b.getPiece(possibleMove).empty() || b.getPiece(possibleMove).getColor() == b.opposite()) && b.getPiece(possibleMove).getColor() != b.same())
            {
                if(b.getPiece(possibleMove).getColor() == b.opposite())
                {
                    v.push_back(Move(piece,possibleMove));
                    break;
                }
                else
                {
                    v.push_back(Move(piece,possibleMove));
                    possibleMove = possibleMove + ctr;
                }
            }
        }
    }
}

void singleMove(std::vector<Move> &v, Board b, std::vector<Coord> &pieceV, std::vector<Coord> dir )
{
    for(unsigned int i=0; i<pieceV.size(); i++){
        Coord piece = pieceV[i];
        for(unsigned int j=0; j<8; j++){
            Coord possibleMove = piece + dir[j];
            if(b.inside(possibleMove)&&(b.getPiece(possibleMove).empty() || b.getPiece(possibleMove).getColor() == b.opposite()))
            {
                v.push_back(Move(piece,possibleMove));
            }
        }
    }
}

/*
bool inCheck(Board b)
{
    Coord pieceV;
    if(b.isWhite())
        pieceV = findPieces(b, epcWking);
    else
        pieceV = findPieces(b, epcBking);

    for (int i = 0; i < 8; i++)
    {
        Coord possibleMove = pieceV + dirQueen[i];
        if (b.inside(possibleMove) && (b.getPiece(possibleMove).empty() || b.getPiece(possibleMove).getColor() == b.opposite()))
        {
            v.push_back(Move(piece, possibleMove));
        }
    }
}
*/
std::vector<Coord> findPieces(const Board &b, ePieceCode piece)
{
    Piece **board = b.getBoard();
    std::vector<Coord> pieces;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j].getPieceCode() == piece)
            {
                pieces.push_back(Coord(j, i));
            }
        }
    }
    return pieces;
}

//Dumbly adds all possible moves for King without considering castling and whether the move will place him in check.
void kingMoves(std::vector<Move> &v, const Board &b)
{
    std::vector<Coord> pieceV;
    if(b.isWhite())
        pieceV = findPieces(b, epcWking);
    else
        pieceV = findPieces(b, epcBrook);
    singleMove(v, b, pieceV, dirKing);


}

//Tests if a Piece has ever moved in the entire game
bool hasMoved(Piece p){
return false; //temporarily set to false for testing reasons
}


void pawnMove(std::vector<Move> &v, Board b, std::vector<Coord> &pieceV, std::vector <Coord> dir1, std::vector <Coord> dir2, std::vector <Coord> dir3 )
{
    Piece ** board = b.getBoard();
    Piece p;
    for(unsigned int i=0; i<pieceV.size(); i++)
    {
        Coord piece = pieceV[i];
        p = board[piece.y][piece.x];
        Coord possibleMove = piece +dir1[0];
        if(b.inside(possibleMove)&&(b.getPiece(possibleMove).empty()))
        {
            v.push_back(Move(piece,possibleMove));
            possibleMove = piece + dir2[0];
            if(!hasMoved(p) && b.getPiece(possibleMove).empty())
            {
                v.push_back(Move(piece, possibleMove));
            }
        }

        for(int j=0; j<2; j++)
        {
            possibleMove = piece + dir3[j];
            if(b.inside(possibleMove)&&b.getPiece(possibleMove).getColor() == b.opposite())
            {
                v.push_back(Move(piece,possibleMove));
            }
        }

    }
}
void pawnMoves(std::vector<Move> &v, Board b)
{
    std::vector<Coord> pieceV;
    if(b.isWhite())
    {
        pieceV = findPieces(b, epcWpawn);
        pawnMove(v, b, pieceV, dirWPawnM, dirWPawnS, dirWPawnC);
    }
    else
    {
        pieceV = findPieces(b, epcBpawn);
        pawnMove(v, b, pieceV, dirBPawnM, dirBPawnS, dirBPawnC);
    }
}


void knightMoves(std::vector<Move> &v, Board b){
    std::vector<Coord> pieceV;
    if(b.isWhite())
        pieceV = findPieces(b, epcWknight);
    else
        pieceV = findPieces(b, epcBknight);
    singleMove(v, b, pieceV, dirKnight);
}

void rookMoves(std::vector<Move> &v, Board b)
{
    std::vector<Coord> pieceV;
    if(b.isWhite())
        pieceV = findPieces(b, epcWrook);
    else
        pieceV = findPieces(b, epcBrook);
    rayMove(v, b, pieceV, dirRook);
}

void bishopMoves(std::vector<Move> &v, Board b)
{
    std::vector<Coord> pieceV;
    if(b.isWhite())
        pieceV = findPieces(b, epcWbishop);
    else
        pieceV = findPieces(b, epcBbishop);
    rayMove(v, b, pieceV, dirBishop);
}


void queenMoves(std::vector<Move> &v, Board b)
{
    std::vector<Coord> pieceV;
    if(b.isWhite())
        pieceV = findPieces(b, epcWqueen);
    else
        pieceV = findPieces(b, epcBqueen);
    rayMove(v, b, pieceV, dirQueen);
}



std::vector<Move> generateMoveList(const Board &b){
    //std::cout << "I MAKE THE GIRLS GO LIKE";
    std::vector<Move> v;
    pawnMoves(v, b);
    knightMoves(v, b);
    rookMoves(v, b);
    kingMoves(v, b);
    bishopMoves(v, b);
    queenMoves(v,b);
    return v;
}
}
