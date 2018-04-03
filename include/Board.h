#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include "Piece.h"
#include "Move.h"

using namespace std;

class Board
{
    public:
        Board();
        Piece** getBoard();
        Piece getPiece(Coord c);
        Board makeMove(Move m);
        Board unmakeMove(Move m);

    private:
        Piece** board = 0;

};

/*constructor sets up the board for a new game*/
/*The board is white pieces rows 0-1 and black pieces 6-7*/
Board::Board()
{
    this->board = 0;
    this->board = new Piece*[8];

    /*setting empty spaces first*/
    Piece startPiece = new Piece(Piece::epcEmpty);
    for(int i=2; i<=5;i++)
    {
        this->board[i] = new Piece[8];
        for(int j=0;j<8;j++)
            this->board[i][j] = startPiece;
    }

    /*setting pawns*/
    this->board[1] = new Piece[8];
    this->board[6] = new Piece[8];
    for(int i=0; i<8;i++)
    {
        startPiece = new Piece(Piece::epcWpawn); //white pawns
        this->board[1][i] = startPiece;
        startPiece = new Piece(Piece::epcBpawn); //black pawns
        this->board[6][i] = startPiece;
    }

    /*setting major pieces*/
    this->board[0] = new Piece[8];
    this->board[7] = new Piece[8];
    ePieceCode majorPiecesW[8] = {Piece::epcWrook,Piece::epcWknight,Piece::epcWbishop,Piece::epcWking,Piece::epcWqueen,Piece::epcWbishop,Piece::epcWknight,Piece::epcWrook};
    ePieceCode majorPiecesB[8] = {Piece::epcBrook,Piece::epcBknight,Piece::epcBbishop,Piece::epcBking,Piece::epcBqueen,Piece::epcBbishop,Piece::epcBknight,Piece::epcBrook};
    for(int i=0; i<8;i++)
    {
        startPiece = new Piece(majorPiecesW[i]); //white pieces
        this->board[0][i] = startPiece;
        startPiece = new Piece(majorPiecesB[i]); //black pieces
        this->board[7][i] = startPiece;
    }

}

/*returns the 2Darray of pieces that represents the board*/
Piece** Board::getBoard()
{
    return this->board;
}

/*returns the piece held at that index of the board 2Darray */
Piece Board::getPiece(Coord c)
{
    return this->board[c.y][c.x];
}

/*sets the piece at the from-coordinates to the index of the board 2Darray
corresponding to the to-coordinates
-then returns the board 2Darray*/
Piece** Board::makeMove(Move m)
{
    this->board[m.getTo().y][m.getTo().x] = this->getPiece(m.getFrom());
    return this->board;
}

/*sets the piece at the to-coordinates to the index of the board 2Darray
corresponding to the from-coordinates
-then returns the board 2Darray*/
Piece** Board::unmakeMove(Move m)
{
    this->board[m.getFrom().y][m.getFrom().x] = this->getPiece(m.getTo());
    return this->board;
}

#endif // BOARD_H
