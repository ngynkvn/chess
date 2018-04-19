#include "Board.h"

using namespace std;
/*constructor sets up the board for a new game*/
/*The board is white pieces rows 0-1 and black pieces 6-7*/
Board::Board() : whiteTurn(true)
{
    this->board = new Piece *[8];

    /*setting empty spaces first*/

    Piece startPiece(epcEmpty);
    for (int i = 2; i <= 5; i++)
    {
        this->board[i] = new Piece[8];
        for (int j = 0; j < 8; j++)
        {
            this->board[i][j] = startPiece;
        }
    }

    /*setting pawns*/
    this->board[1] = new Piece[8];
    this->board[6] = new Piece[8];
    for (int i = 0; i < 8; i++)
    {
        startPiece = Piece(epcWpawn); //white pawns
        this->board[1][i] = startPiece;
        startPiece = Piece(epcBpawn); //black pawns
        this->board[6][i] = startPiece;
    }

    /*setting major pieces*/
    this->board[0] = new Piece[8];
    this->board[7] = new Piece[8];
    ePieceCode majorPiecesW[8] = {epcWrook, epcWknight, epcWbishop, epcWking, epcWqueen, epcWbishop, epcWknight, epcWrook};
    ePieceCode majorPiecesB[8] = {epcBrook, epcBknight, epcBbishop, epcBking, epcBqueen, epcBbishop, epcBknight, epcBrook};
    for (int i = 0; i < 8; i++)
    {
        startPiece = Piece(majorPiecesW[i]); //white pieces
        this->board[0][i] = startPiece;
        startPiece = Piece(majorPiecesB[i]); //black pieces
        this->board[7][i] = startPiece;
    }
}

Board::Board(Piece **newBoard)
{
    this->board = newBoard;
    this->board = new Piece *[8];
    for (int row = 0; row < 8; row++)
    {
        this->board[row] = new Piece[8];
        for (int col = 0; col < 8; col++)
        {
            this->board[row][col] = newBoard[row][col];
        }
    }
}

/*returns the 2Darray of pieces that represents the board*/
Piece **Board::getBoard() const
{
    return this->board;
}

/*returns the piece held at that index of the board 2Darray */
Piece Board::getPiece(Coord c) const
{
    return this->board[c.y][c.x];
}

/*sets the piece at the from-coordinates to the index of the board 2Darray
corresponding to the to-coordinates
-then returns a Board object with these changes
-the actual Board has not been affected
-^^will in the future handle taking opponent pieces*/
Board Board::makeMove(Move m) const
{
    Board testerGame(this->board);
    Piece **gameBoard = testerGame.getBoard();
    testerGame.setTurn(!whiteTurn);
    //testerGame.setPrevMove(m); // board.h and add in methods there and make public
    gameBoard[m.to().y][m.to().x] = testerGame.getPiece(m.from());
    gameBoard[m.from().y][m.from().x] = Piece(epcEmpty);
    return testerGame;
}

/*sets the piece at the to-coordinates to the index of the board 2Darray
corresponding to the from-coordinates
-then returns a Board object with these changes
-the actual Board has not been affected
-^^will in the future handle returning opponent pieces*/
Board Board::unmakeMove(Move m) const
{
    Board testerGame = Board(this->board);
    Piece **gameBoard = testerGame.getBoard();
    gameBoard[m.from().y][m.from().x] = testerGame.getPiece(m.to());
    return testerGame;
}

bool Board::inside(Coord c) const { return c.x > -1 && c.x < 8 && c.y > -1 && c.y < 8; }

bool Board::isWhite() const { return whiteTurn; }
void Board::setTurn(bool isWhite) { whiteTurn = isWhite; }
ePieceCode Board::opposite() const { return whiteTurn ? black : white; }
ePieceCode Board::same() const { return whiteTurn ? white : black; }

ostream &operator<<(ostream &os, const Board &board)
{
    // char outChars[] = {' ', 'p', 'k','b','r','q','W',
    //                    ' ', 'P', 'K','B','R','Q','B'};
    std::string prettyPrint[] = {" ", "♙", "♘", "♗", "♖", "♕", "♔",
                                 " ", "♟", "♞", "♝", "♜", "♛", "♚"};
    for (int j = 7; j > -1; j--)
    {
        for (int i = 7; i > -1; i--)
        {
            Piece p = board.getPiece(Coord(i, j));
            if (p.empty())
            {
                os << "..";
            }
            else
            {
                os << prettyPrint[p.getPieceCode()] << " ";
            }
        }
        os << endl;
    }
    os << board.isWhite() << endl;
    os << "It is " << (board.isWhite() ? "white's" : "black's") << " turn" << endl;
    return os;
}
