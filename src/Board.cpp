#include "Board.h"
#include "Search.h"

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

/*
Creates a new Board object by setting the 2D Piece-array board
to an already existing 2D array
*/
Board::Board(const Board &other) : whiteTurn(other.whiteTurn), prevMove(other.prevMove)
{
    board = new Piece *[8];
    for (int row = 0; row < 8; row++)
    {
        board[row] = new Piece[8];
        for (int col = 0; col < 8; col++)
        {
            board[row][col] = other.board[row][col];
        }
    }
}

Board &Board::operator=(const Board &other)
{
    if (this != &other)
    {
        for (int i = 0; i < 8; i++)
        {
            delete[] board[i];
        }
        delete[] board;
        board = new Piece *[8];
        Piece **b = other.getBoard();
        for (int i = 0; i < 8; i++)
        {
            board[i] = new Piece[8];
            for (int j = 0; j < 8; j++)
            {
                board[i][j] = b[i][j];
            }
        }
        whiteTurn = other.whiteTurn;
        prevMove = other.prevMove;
    }
    return *this;
}

/**
 * Destructor to remove piece array.
 * This is done via a simple for loop to remove each pointer array.
 */
Board::~Board()
{
    for (int i = 0; i < 8; i++)
    {
        delete[] board[i];
    }
    delete[] board;
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
    Board testerGame(*this);
    Piece **gameBoard = testerGame.getBoard();
    testerGame.setTurn(!whiteTurn);
    testerGame.setPrevMove(m); // board.h and add in methods there and make public
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
    Board testerGame = Board(*this);
    Piece **gameBoard = testerGame.getBoard();
    gameBoard[m.from().y][m.from().x] = testerGame.getPiece(m.to());
    return testerGame;
}

/*
Returns true if the coordinate given is within the board
*/
bool Board::inside(Coord c) const { return c.x > -1 && c.x < 8 && c.y > -1 && c.y < 8; }

/*
Returns a boolean variable that clarifies if it's white's move or not
*/
bool Board::isWhite() const { return whiteTurn; }

/*
Sets variable whiteTurn to true if it's white's move and false if not
*/
void Board::setTurn(bool isWhite) { whiteTurn = isWhite; }

/*
Returns previous move
*/
Move Board::getPrevMove() const { return prevMove; }

/*
Sets the previous move to another move object
*/
void Board::setPrevMove(Move m) { prevMove = m; }

/*
Returns the black ePieceCode if it's white's move, white if it's not
*/
ePieceCode Board::opposite() const { return whiteTurn ? black : white; }

/*
Returns the same color ePieceCode of the color turn
*/
ePieceCode Board::same() const { return whiteTurn ? white : black; }

ostream &operator<<(ostream &os, const Board &board)
{
    // char outChars[] = {' ', 'p', 'k','b','r','q','W',
    //                    ' ', 'P', 'K','B','R','Q','B'};
    std::string prettyPrint[] = {" ", "♙", "♘", "♗", "♖", "♕", "♔",
                                 " ", "♟", "♞", "♝", "♜", "♛", "♚"};
    std::string files[] = {"1 |", "2 |", "3 |", "4 |", "5 |", "6 |", "7 |", "8 |"};
    for (int j = 7; j > -1; j--)
    {
        os << files[j];
        for (int i = 7; i > -1; i--)
        {
            Piece p = board.getPiece(Coord(i, j));
            if (p.empty())
            {
                os << ". ";
            }
            else
            {
                os << prettyPrint[p.getPieceCode()] << " ";
            }
        }
        os << endl;
    }
    os << "   ---------------" << endl;
    os << "   a b c d e f g h" << endl;
    os << "It is " << (board.isWhite() ? "white's" : "black's") << " turn" << endl;
    os << (board.isWhite() ? "Black" : "White") << " played " << board.getPrevMove() << endl;
    // os << "Board is valued at " << evaluate(board) << endl;
    // os << "They have " << Search::generateMoveList(board).size() << " moves" << endl;
    return os;
}
