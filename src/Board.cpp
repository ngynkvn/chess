#include <iostream>
#include "Board.h"
#include "Search.h"

using namespace std;
/*constructor sets up the board for a new game*/
/*The board is white pieces rows 0-1 and black pieces 6-7*/
Board::Board()
{
    this->board = new ePieceCode* [8];
    history.emplace_back(Move(-1,-1,-1,-1));
    /*setting empty spaces first*/
    for (int i = 2; i <= 5; i++)
    {
        this->board[i] = new ePieceCode[8];
        for (int j = 0; j < 8; j++)
        {
            this->board[i][j] = epcEmpty;
        }
    }

    /*setting pawns*/
    this->board[1] = new ePieceCode[8];
    this->board[6] = new ePieceCode[8];
    for (int i = 0; i < 8; i++)
    {
        this->board[1][i] = epcWpawn;
        this->board[6][i] = epcBpawn;
    }

    /*setting major pieces*/
    this->board[0] = new ePieceCode[8];
    this->board[7] = new ePieceCode[8];
    ePieceCode majorPiecesW[8] = {epcWrook, epcWknight, epcWbishop, epcWking, epcWqueen, epcWbishop, epcWknight, epcWrook};
    ePieceCode majorPiecesB[8] = {epcBrook, epcBknight, epcBbishop, epcBking, epcBqueen, epcBbishop, epcBknight, epcBrook};
    for (int i = 0; i < 8; i++)
    {
        this->board[0][i] = majorPiecesW[i];
        this->board[7][i] = majorPiecesB[i];
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
        board = new ePieceCode *[8];
        ePieceCode **b = other.getBoard();
        for (int i = 0; i < 8; i++)
        {
            board[i] = new ePieceCode[8];
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
ePieceCode **Board::getBoard() const
{
    return this->board;
}

/*returns the piece held at that index of the board 2Darray */
ePieceCode& Board::getPiece(Coord c) const
{
    return board[c.y][c.x];
}

/*sets the piece at the from-coordinates to the index of the board 2Darray
corresponding to the to-coordinates
-then returns a Board object with these changes
-the actual Board has not been affected
-^^will in the future handle taking opponent pieces*/
Board & Board::makeMove(Move m)
{
    setTurn(!whiteTurn);
    history.push_back(m);
    captures.emplace_back(getPiece(m.to()));
    board[m.to().y][m.to().x] = getPiece(m.from());
    board[m.from().y][m.from().x] = epcEmpty;
    return *this;
}

/*sets the piece at the to-coordinates to the index of the board 2Darray
corresponding to the from-coordinates
-then returns a Board object with these changes
-the actual Board has not been affected
-^^will in the future handle returning opponent pieces*/
void Board::unmakeMove()
{
    setTurn(!whiteTurn);
    Move prev = history.back();
    history.pop_back();
    board[prev.from().y][prev.from().x] = (*this).getPiece(prev.to());
    board[prev.to().y][prev.to().x] = captures.back();
    captures.pop_back();
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
Move Board::getPrevMove() const { return history.back(); }

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
//     char outChars[] = {' ', 'p', 'k','b','r','q','W',
//                        ' ', 'P', 'K','B','R','Q','B'};
    std::string outChars[] = {" ", "♙", "♘", "♗", "♖", "♕", "♔",
                                 " ", "♟", "♞", "♝", "♜", "♛", "♚"};
    std::string files[] = {"1 |", "2 |", "3 |", "4 |", "5 |", "6 |", "7 |", "8 |"};
    for (int j = 7; j > -1; j--)
    {
        os << files[j];
        for (int i = 7; i > -1; i--)
        {
            ePieceCode p = board.getPiece(Coord(i, j));
            p == epcEmpty ? os << ". " : os << outChars[p] << " ";
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
