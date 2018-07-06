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

//The three unique movements of a white pawn (Push, Capture, and Move2)
std::vector<Coord> dirWpawnPush = {Coord(0, 1)};   // pawn push
std::vector<Coord> dirWpawnCapture = {Coord(1, 1), // two direction white pawn captures
                                      Coord(-1, 1)};
std::vector<Coord> dirWpawnMove2 = {Coord(0, 2)}; //White Pawn on a starting rank has option to move 2 squares

//The three unique movements of a black pawn (Push, Capture, and Move2)
std::vector<Coord> dirBpawnPush = {Coord(0, -1)};   // pawn push
std::vector<Coord> dirBpawnCapture = {Coord(1, -1), // two direction black pawn captures
                                      Coord(-1, -1)};
std::vector<Coord> dirBpawnMove2 = {Coord(0, -2)}; //Black Pawn on a starting rank has option to move 2 squares

std::map<ePieceCode, std::vector<Coord>> cachePos;

void cachePositions(Board& b)
{
    cachePos.clear();
    Piece** board = b.getBoard();
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
        {
            if(!board[i][j].empty()){
                cachePos[board[i][j].getPieceCode()].emplace_back(j,i);
            }
        }
}

// returns a vector<Coord> of all pieces with same ePieceCode
std::vector<Coord> findPieces(Board& b, int piece)
{
    return cachePos.at((ePieceCode)piece);
}

//When a pawn reaches the end of the board, it promotes to a queen piece
void promote(const Board &b)
{
    ePieceCode **board = b.getBoard();
    //Checks all 8 columns of the board
    for (int i = 0; i < 8; i++)
    {
        //checks the side of the board depending on the turn's color and checks if there is the correct pawn color on that side of the board
         if(board[b.isWhite() ? 7 : 0][i] == (b.isWhite() ? epcWpawn : epcBpawn) ){
             board[b.isWhite() ? 7 : 0][i] = (b.isWhite() ? epcWqueen : epcBqueen); //promotes pawn to queen
         }
    }
}

//semi-"helper" function for the funciton inCheck
//Checks in the directions of the Coord dir from the king if there is an enemy piece thretening the king
//think: checks if the king can see an enemy ray piece that attacks on that line
//rayPieces can move in a line indefinitely, but are blocked by pieces obstructing the path
bool rayCheckHelper(const Board &b, Coord piece, std::vector<Coord> dir, ePieceCode code)
{
    //For each direction in vector dir
    for (auto k : dir) {
        //Exmines each square in an extending line until break condition is met
        //condition: while the next square in the same direction is empty, examinee that square
        //conditions that break loop: square is a ally piece, opponent, or out of board.
        Coord possibleMove = piece + k;
        while ((b.inside(possibleMove) && (b.getPiece(possibleMove) == epcEmpty)))
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
bool squareCheckHelper(const Board &b, Coord piece, std::vector<Coord> dir, int code)
{
    //for each direction in vector dir
    for (auto k : dir) {
        //check that square
        Coord possibleMove = piece + k;
        if(b.inside(possibleMove) && b.getPiece(possibleMove) == ePieceCode(code))
            return true; //Corresponding enemy piece occupies square
    }
    //if return true is never called
    return false;
}

//Function checks a board and tests if the king is in check
bool inCheck(Board &b, Move m)
{
    std::vector<Coord> pieceV;
    b.makeMove(m); // This is the modified board if the move is made
    //set pieceV to the correct color
    if (!b.isWhite())
    {
        pieceV = findPieces(b, epcWking); //cast code to correspoding white ePieceCode
    }
    else
    {
        pieceV = findPieces(b, epcBking); //cast code to correspoding black ePieceCode
    }
    if (pieceV.empty())
    {
        std::cout << b << std::endl;
        throw std::runtime_error("uhoh");
    }
    Coord piece = pieceV[0]; //location of king
    bool result;
    if (!b.isWhite())                                         //For White turn
        result = (rayCheckHelper(b, piece, dirRook, epcBrook) //If any of these black pieces are threatening the king then return true
                  || rayCheckHelper(b, piece, dirQueen, epcBqueen) || rayCheckHelper(b, piece, dirBishop, epcBbishop) || squareCheckHelper(b, piece, dirKnight, epcBknight) || squareCheckHelper(b, piece, dirKing, epcBking) || squareCheckHelper(b, piece, dirWpawnCapture, epcBpawn));
    else                                                      //For black turn
        result = (rayCheckHelper(b, piece, dirRook, epcWrook) //If any of these white pieces are threatening the king then return true
                  || rayCheckHelper(b, piece, dirQueen, epcWqueen) || rayCheckHelper(b, piece, dirBishop, epcWbishop) || squareCheckHelper(b, piece, dirKnight, epcWknight) || squareCheckHelper(b, piece, dirKing, epcWking) || squareCheckHelper(b, piece, dirBpawnCapture, epcWpawn));
    b.unmakeMove();
    return result;
}

//Overloaded function that checks for checking the enemy
bool inCheck(Board &b)
{
    std::vector<Coord> pieceV;
    //set pieceV to the correct color
    if (b.isWhite())
    {
        pieceV = findPieces(b, epcBking); //cast code to correspoding white ePieceCode
    }
    else
    {
        pieceV = findPieces(b, epcWking); //cast code to correspoding black ePieceCode
    }
    // std::cout << b2 << std::endl;
    // std::cout << pieceV.size() << std::endl;
    Coord piece = pieceV[0]; //location of king

    if (b.isWhite())                                        //For white turn
        return (rayCheckHelper(b, piece, dirRook, epcWrook) //If any of these black pieces are threatening the king then return true
                || rayCheckHelper(b, piece, dirQueen, epcWqueen) || rayCheckHelper(b, piece, dirBishop, epcWbishop) || squareCheckHelper(b, piece, dirKnight, epcWknight) || squareCheckHelper(b, piece, dirKing, epcWking) || squareCheckHelper(b, piece, dirBpawnCapture, epcWpawn));

    else
        return (rayCheckHelper(b, piece, dirRook, epcBrook) //If any of these white pieces are threatening the king then return true
                || rayCheckHelper(b, piece, dirQueen, epcBqueen) || rayCheckHelper(b, piece, dirBishop, epcBbishop) || squareCheckHelper(b, piece, dirKnight, epcBknight) || squareCheckHelper(b, piece, dirKing, epcBking) || squareCheckHelper(b, piece, dirWpawnCapture, epcBpawn));
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
            if(b.inside(possibleMove) && (b.getPiece(possibleMove) == epcEmpty || getColor(b.getPiece(possibleMove)) == b.opposite()) && !inCheck(b, Move(piece, possibleMove)))
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
                if(b.inside(possibleMove) && getColor(b.getPiece(possibleMove)) == b.opposite() && !inCheck(b, Move(piece, possibleMove)))
                    v.emplace_back(piece, possibleMove); //capture move
            }
        }
    }
}

    ePieceCode getColor(ePieceCode code) {
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
    for (unsigned int i = 0; i < pieceV.size(); i++)
    {
        //check each possible square that dir points to if square is empty or occupties by enemy
        Coord piece = pieceV[i]; //storing location
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
void pawnMove(std::vector<Move> &v, Board &b, std::vector<Coord> &pieceV, std::vector<Coord> push, std::vector<Coord> move2, std::vector<Coord> dir3)
{
    for (auto piece : pieceV) {
        Coord possibleMove = piece + push[0]; //possibleMove set to a pawn push

        //Checks forward square for pawn push direction and checks for special 2 square move
        //if ( move inside board   &&          square is empty         && !if move made exposes king to check )))
        if (b.inside(possibleMove) && b.getPiece(possibleMove) == epcEmpty && !inCheck(b, Move(piece, possibleMove))) //tests a pawn push
        {
            v.emplace_back(piece, possibleMove);

            //conditional 2 pawn jump start move
            //tests if the pawn is on a original starting color and if the second square is empty
            //(inside prev if loop because the square immediatly in front of it must also be empty)
            possibleMove = piece + move2[0];                                                                                      //possibleMove set to special 2 square move
            if ((piece.y == (b.isWhite() ? 1 : 6)) && b.getPiece(possibleMove) == epcEmpty && !inCheck(b, Move(piece, possibleMove))) // pawn is on rank file and two moves in front square is empty
                v.emplace_back(piece, possibleMove); //add Move to v
        }

        //for loop for the two capture directions
        for (int j = 0; j < 2; j++)
        {
            //capture a piece
            possibleMove = piece + dir3[j]; //possibleMove set to a pawn capture direction
            if(b.inside(possibleMove)&&getColor(b.getPiece(possibleMove)) == b.opposite() && !inCheck(b, Move(piece, possibleMove))) // test opposite color piece in square
                v.emplace_back(piece,possibleMove);  //captures
        }
    }
}

void generateMove(std::vector<Move> &v, Board &b, int code)
{
    std::vector<Coord> pieceV;

    // sets pieceV to the correct color
    if (b.isWhite())
        pieceV = findPieces(b, code); //cast code to correspoding white ePieceCode
    else
        pieceV = findPieces(b, code + 7); //cast code to correspoding black ePieceCode

    //Based on the ePieceCode, the appropriate move function is called with appropriate parameters
    switch (code)
    {
    //each move function parameters are
    //all possible moves vector v, the Board b, a vector of all piece types, and vector direction the piece moves
    case epcWpawn: //Pawn move
        if (b.isWhite())
        {
            pawnMove(v, b, pieceV, dirWpawnPush, dirWpawnMove2, dirWpawnCapture);
            break;
        }
        else
        {
            pawnMove(v, b, pieceV, dirBpawnPush, dirBpawnMove2, dirBpawnCapture);
            break;
        }
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
    generateMove(v, b, epcWqueen);
    generateMove(v, b, epcWrook);
    generateMove(v, b, epcWbishop);
    generateMove(v, b, epcWknight);
    generateMove(v, b, epcWpawn);
    generateMove(v, b, epcWking);
    return v;
}
} // namespace Search
