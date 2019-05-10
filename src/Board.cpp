#include <iostream>
#include "Board.h"
#include "Search.h"
#include <array>


/*constructor sets up the board for a new game*/
/*The board is white pieces rows 0-1 and black pieces 6-7*/
Board::Board()
{
    this->board.fill(epcEmpty);
    history.emplace_back(Move(-1,-1,-1,-1));
    /*setting pawns*/
    for (int i = 0; i < 8; i++)
    {
        this->board[8 + i] = epcWpawn;
        this->board[48 + i] = epcBpawn;
    }
    /*setting major pieces*/
    ePieceCode majorPiecesW[8] = {epcWrook, epcWknight, epcWbishop, epcWking, epcWqueen, epcWbishop, epcWknight, epcWrook};
    ePieceCode majorPiecesB[8] = {epcBrook, epcBknight, epcBbishop, epcBking, epcBqueen, epcBbishop, epcBknight, epcBrook};
    for (int i = 0; i < 8; i++)
    {
        this->board[i] = majorPiecesW[i];
        this->board[56 + i] = majorPiecesB[i];
    }
}

/*sets the piece at the from-coordinates to the index of the board 2Darray
corresponding to the to-coordinates
-then returns a Board object with these changes
-the actual Board has not been affected
-^^will in the future handle taking opponent pieces*/
Board & Board::makeMove(const Move& m)
{
    setTurn(!whiteTurn);
    history.push_back(m);
    auto [fromX, fromY] = m.from;
    auto [toX, toY] = m.to;
    captures.emplace_back(getPiece(m.to));
    board[(toY << 3) + toX] = getPiece(m.from);
    board[(fromY << 3) + fromX] = epcEmpty;
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
    auto [fromX, fromY] = prev.from;
    auto [toX, toY] = prev.to;
    board[(fromY << 3) + fromX] = (*this).getPiece(prev.to);
    board[(toY << 3) + toX] = captures.back();
    captures.pop_back();
}
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
ePieceCode Board::opposite() const { return whiteTurn ? Black : White; }

/*
Returns the same color ePieceCode of the color turn
*/
ePieceCode Board::same() const { return whiteTurn ? White : Black; }

std::ostream &operator<<(std::ostream &os, const Board &board)
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
            p == epcEmpty ? os << ". " : os << outChars[p];
        }
        os << std::endl;
    }
    os << "   ---------------" << std::endl;
    os << "   a b c d e f g h" << std::endl;
    os << "It is " << (board.isWhite() ? "white's" : "black's") << " turn" << std::endl;
    os << (board.isWhite() ? "Black" : "White") << " played " << board.getPrevMove() << std::endl;
    // os << "Board is valued at " << evaluate(board) << std::endl;
    // os << "They have " << Search::generateMoveList(board).size() << " moves" << std::endl;
    return os;
}
