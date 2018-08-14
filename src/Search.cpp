#include "Search.h"
#include <iostream>
#include <map>
#include <assert.h>

namespace Search
{

//Rook directions
std::vector<Coord> dirRook = {Coord(0, 1), //The 4 Ray directions rooks can slide to (raymove)
                              Coord(0, -1),
                              Coord(1, 0),
                              Coord(-1, 0)};

//Bishop directions
std::vector<Coord> dirBishop = {Coord(1, 1), //The 4 Ray directions bishops can slide to (raymove)
                                Coord(1, -1),
                                Coord(-1, -1),
                                Coord(-1, 1)};

//Queen directions
std::vector<Coord> dirQueen = {Coord(1, 1), //The 8 Ray directions queens can slide to (raymove)
                               Coord(1, -1),
                               Coord(-1, -1),
                               Coord(-1, 1),
                               Coord(0, 1),
                               Coord(0, -1),
                               Coord(1, 0),
                               Coord(-1, 0)};

//Knight directions
std::vector<Coord> dirKnight = {Coord(1, 2), //The 8 square directions a knight can jump to (squareMove)
                                Coord(2, 1),
                                Coord(2, -1),
                                Coord(1, -2),
                                Coord(-1, 2),
                                Coord(-2, 1),
                                Coord(-2, -1),
                                Coord(-1, -2)};

//King directions
std::vector<Coord> dirKing = {Coord(-1, -1), //The 8 square directions a king can slide to (squareMove)
                              Coord(-1, 0),
                              Coord(-1, 1),
                              Coord(0, 1),
                              Coord(0, -1),
                              Coord(1, -1),
                              Coord(1, 0),
                              Coord(1, 1)};

Coord wPawnPush = Coord(0, 1);
Coord bPawnPush = Coord(0, -1);
std::vector<Coord> wPawnCaptures = {Coord(1, 1), // two direction white pawn captures
                                    Coord(-1, 1)};

std::vector<Coord> bPawnCaptures = {Coord(1, -1), // two direction black pawn captures
                                    Coord(-1, -1)};

std::map<ePieceCode, std::vector<Coord>> cachePos;

void cachePositions(Board &b)
{
    cachePos.clear();
    ePieceCode **board = b.getBoard();
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != epcEmpty)
            {
                cachePos[board[i][j]].emplace_back(j, i);
            }
        }
}

// returns a vector<Coord> of all pieces with same ePieceCode
std::vector<Coord> findPieces(Board &b, int piece)
{
    return cachePos[static_cast<ePieceCode>(piece)];
}

//When a pawn reaches the end of the board, it promotes to a queen piece
void promote(const Board &b)
{
    ePieceCode **board = b.getBoard();
    //Checks all 8 columns of the board
    for (int i = 0; i < 8; i++)
    {
        //checks the side of the board depending on the turn's color and checks if there is the correct pawn color on that side of the board
        if (board[b.isWhite() ? 7 : 0][i] == (b.isWhite() ? epcWpawn : epcBpawn))
        {
            board[b.isWhite() ? 7 : 0][i] = (b.isWhite() ? epcWqueen : epcBqueen); //promotes pawn to queen
        }
    }
}

//semi-"helper" function for the funciton inCheck
//Checks in the directions of the Coord dir from the king if there is an enemy piece thretening the king
//think: checks if the king can see an enemy ray piece that attacks on that line
//rayPieces can move in a line indefinitely, but are blocked by pieces obstructing the path
bool rayCheckHelper(const Board &b, Coord piece, std::vector<Coord> dir, int epcCode)
{
    ePieceCode code = static_cast<ePieceCode>(epcCode);
    //For each direction in vector dir
    for (auto k : dir)
    {
        //Exmines each square in an extending line until break condition is met
        //condition: while the next square in the same direction is empty, examinee that square
        //conditions that break loop: square is a ally piece, opponent, or out of board.
        Coord possibleMove = piece + k;
        while (b.inside(possibleMove) && b.getPiece(possibleMove) == epcEmpty)
        {
            possibleMove = possibleMove + k;
        }
        //if the loops breaks because there is an enemy on the square
        if (b.inside(possibleMove) && b.getPiece(possibleMove) == code)
            return true;
    }
    //if return true is never called then it is false
    return false;
}

//"semi-"helper" function for the function inCheck
//Checks the squares that Coord dir points to see if there is an enemy piece thretening the king
//Pieces can move to a square that the Coord dir points to, if the square is not occupied by ally
bool squareCheckHelper(const Board &b, Coord piece, std::vector<Coord> dir, int epcCode)
{
    ePieceCode code = static_cast<ePieceCode>(epcCode);
    //for each direction in vector dir
    for (auto k : dir)
    {
        //check that square
        Coord possibleMove = piece + k;
        if (b.inside(possibleMove) && b.getPiece(possibleMove) == code)
            return true; //Corresponding enemy piece occupies square
    }
    //if return true is never called
    return false;
}

//Function checks a board and tests if the king is in check
bool inCheck(Board &b, Move m)
{
    bool turnIsWhite = b.isWhite();
    int c = turnIsWhite ? white : black;
    //set pieceV to the correct color
    std::vector<Coord> pieceV = findPieces(b, epcWking + c);

    b.makeMove(m);

    if (pieceV.empty())
        throw std::runtime_error("Found king is not on board.");

    Coord piece = pieceV[0]; //location of king

    c = turnIsWhite ? black : white;
    bool result = rayCheckHelper(b, piece, dirRook, epcWrook + c) || rayCheckHelper(b, piece, dirQueen, epcWqueen + c) || rayCheckHelper(b, piece, dirBishop, epcWbishop + c) || squareCheckHelper(b, piece, dirKnight, epcWknight + c) || squareCheckHelper(b, piece, turnIsWhite ? wPawnCaptures : bPawnCaptures, epcWpawn + c) || squareCheckHelper(b, piece, dirKing, epcWking + c);
    b.unmakeMove();
    return result;
}

//Overloaded function that checks for checking the enemy
bool inCheck(Board &b)
{
    bool turnIsWhite = b.isWhite();
    //set pieceV to the correct color
    std::vector<Coord> pieceV = turnIsWhite ? findPieces(b, epcWking) : findPieces(b, epcBking);
    //set pieceV to the correct color

    Coord piece = pieceV[0]; //location of king
    int c = turnIsWhite ? black : white;
    bool result = rayCheckHelper(b, piece, dirRook, epcWrook + c) || rayCheckHelper(b, piece, dirQueen, epcWqueen + c) || rayCheckHelper(b, piece, dirBishop, epcWbishop + c) || squareCheckHelper(b, piece, dirKnight, epcWknight + c) || squareCheckHelper(b, piece, turnIsWhite ? wPawnCaptures : bPawnCaptures, epcWpawn + c);
    b.unmakeMove();
    return result;
}

ePieceCode getColor(ePieceCode code);

//Purpose: Add all possible moves to v for pieces that move in rays (Rooks, Bishops, Queens)
//rayPieces can move in a line indefinitely, but are blocked by pieces obstructing the path
void rayMove(std::vector<Move> &v, Board &b, std::vector<Coord> &pieceV, std::vector<Coord> dir)
{
    for (auto piece : pieceV)
    {
        //storing location
        for (auto j : dir)
        {
            Coord possibleMove = piece + j;
            //if possible move is inside and (     square is empty         ||            enemy occupy square                       &&   !if move made exposes king to check   )
            if (b.inside(possibleMove) && (b.getPiece(possibleMove) == epcEmpty || getColor(b.getPiece(possibleMove)) == b.opposite()) && !inCheck(b, Move(piece, possibleMove)))
            {
                //Exmines each square in an extending line until break condition is met
                //condition: while the next square in the same direction is empty, examinee that square
                //conditions that break loop: square is a ally piece, opponent, or out of board.
                while (b.inside(possibleMove) && b.getPiece(possibleMove) == epcEmpty && !inCheck(b, Move(piece, possibleMove)))
                {
                    //can move to empty square and continue down the line of direction dir[j]
                    v.emplace_back(piece, possibleMove);
                    possibleMove = possibleMove + j;
                }
                //if the loops breaks because there is an enemy on the square
                //Captures that square from an enemy piece but does not continue down the line
                if (b.inside(possibleMove) && getColor(b.getPiece(possibleMove)) == b.opposite() && !inCheck(b, Move(piece, possibleMove)))
                    v.emplace_back(piece, possibleMove); //capture move
            }
        }
    }
}

ePieceCode getColor(ePieceCode code)
{
    if (code == epcEmpty)
    {
        return epcEmpty;
    }
    return code > black ? ePieceCode::black : ePieceCode::white;
}

//Purpose: Add all possible moves to v for pieces that move to a single square in a direction
//Pieces can move to a square that the Coord dir points to, if the square is not occupied by ally
void squareMove(std::vector<Move> &v, Board &b, std::vector<Coord> &pieceV, std::vector<Coord> dir)
{
    //for each piece of that type
    for (auto piece : pieceV)
    {
        for (unsigned int j = 0; j < 8; j++)
        {
            Coord possibleMove = piece + dir[j]; //the square where dir[j] points to from piece origin
            //if ( possibleMove is in board &&       square is empty        ||         enemy ocuppies square                        && !if move made exposes king to check )))
            if (b.inside(possibleMove) && (b.getPiece(possibleMove) == epcEmpty || getColor(b.getPiece(possibleMove)) == b.opposite()) && !inCheck(b, Move(piece, possibleMove)))
                v.emplace_back(piece, possibleMove); //if square is empty or occupied by enemy, add possibleMove to v
        }
    }
}

//Purpose: adds to v by generating all moves based off 3 conditional types of pawn movements
void pawnMove(std::vector<Move> &v, Board &b, std::vector<Coord> &pieceV)
{
    bool turnIsWhite = b.isWhite();
    Coord push = turnIsWhite ? wPawnPush : bPawnPush;
    std::vector<Coord> captures = turnIsWhite ? wPawnCaptures : bPawnCaptures;

    for (auto piece : pieceV)
    {
        Coord possibleMove = piece + push; //possibleMove set to a pawn push

        if (b.inside(possibleMove) && b.getPiece(possibleMove) == epcEmpty && !inCheck(b, Move(piece, possibleMove))) //tests a pawn push
        {
            v.emplace_back(piece, possibleMove);

            Coord possibleMove2 = possibleMove + push;                                                                                //possibleMove set to special 2 square move
            if ((piece.y == (turnIsWhite ? 1 : 6)) && b.getPiece(possibleMove2) == epcEmpty && !inCheck(b, Move(piece, possibleMove2))) // pawn is on rank file and two moves in front square is empty
                v.emplace_back(piece, possibleMove2);                                                                                 //add Move to v
        }
        //for loop for the two capture directions
        for (Coord cap : captures)
        {
            //capture a piece
            Coord possibleMove = piece + cap;
            if (b.inside(possibleMove) && getColor(b.getPiece(possibleMove)) == b.opposite() && !inCheck(b, Move(piece, possibleMove))) // test opposite color piece in square
                v.emplace_back(piece, possibleMove);                                                                                    //captures
        }
    }
}

void generateMove(std::vector<Move> &v, Board &b, int code)
{
    std::vector<Coord> pieceV = b.isWhite() ? findPieces(b, code) : findPieces(b, code + 7);

    //Based on the ePieceCode, the appropriate move function is called with appropriate parameters
    switch (code)
    {
    //each move function parameters are
    //all possible moves vector v, the Board b, a vector of all piece types, and vector direction the piece moves
    case epcWpawn: //Pawn move
        pawnMove(v, b, pieceV);
        break;
    case epcWknight: //Knight move
        squareMove(v, b, pieceV, dirKnight);
        break;
    case epcWbishop: //Bishop move
        rayMove(v, b, pieceV, dirBishop);
        break;
    case epcWrook: //Rook move
        rayMove(v, b, pieceV, dirRook);
        break;
    case epcWqueen: //Queen move
        rayMove(v, b, pieceV, dirQueen);
        break;
    case epcWking: //king move
        squareMove(v, b, pieceV, dirKing);
        break;
    default:
        throw("Not a known pieceCode.");
    }
    //tests the board to see if a pawn has reached the end of the board or not. if so promotes a piece
    promote(b);
}

std::vector<Move> generateMoveList(Board &b)
{
    std::vector<Move> v;
    cachePositions(b);
    generateMove(v, b, epcWknight);
    generateMove(v, b, epcWbishop);
    generateMove(v, b, epcWqueen);
    generateMove(v, b, epcWrook);
    generateMove(v, b, epcWpawn);
    generateMove(v, b, epcWking);
    return v;
}
} // namespace Search
