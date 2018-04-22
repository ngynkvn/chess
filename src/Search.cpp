#include "Search.h"
#include <iostream>

namespace Search
{

std::vector<Coord> dirRook = {Coord(0, 1),          //The 4 Ray directions rooks can slide to (raymove)
                              Coord(0, -1),
                              Coord(1, 0),
                              Coord(-1, 0)};

std::vector<Coord> dirBishop = {Coord(1, 1),        //The 4 Ray directions bishops can slide to (raymove)
                                Coord(1, -1),
                                Coord(-1, -1),
                                Coord(-1, 1)};

std::vector<Coord> dirQueen = {Coord(1, 1),       //The 8 Ray directions queens can slide to (raymove)
                               Coord(1, -1),
                               Coord(-1, -1),
                               Coord(-1, 1),
                               Coord(0, 1),
                               Coord(0, -1),
                               Coord(1, 0),
                               Coord(-1, 0)};

std::vector<Coord> dirKnight = {Coord(1, 2),        //The 8 square directions a knight can jump to (squareMove)
                                Coord(2, 1),
                                Coord(2, -1),
                                Coord(1, -2),
                                Coord(-1, 2),
                                Coord(-2, 1),
                                Coord(-2, -1),
                                Coord(-1, -2)};

std::vector<Coord> dirKing = {Coord(-1, -1),        //The 8 square directions a king can slide to (squareMove)
                              Coord(-1, 0),
                              Coord(-1, 1),
                              Coord(0, 1),
                              Coord(0, -1),
                              Coord(1, -1),
                              Coord(1, 0),
                              Coord(1, 1)};

//The three unique movements of a white pawn (Push, Capture, and Move2)
std::vector<Coord> dirWpawnPush = {Coord(0, 1)};
std::vector<Coord> dirWpawnCapture = {Coord(1, 1),
                                    Coord(-1, 1)};
std::vector<Coord> dirWpawnMove2 = {Coord(0, 2)}; //White Pawn on a starting rank has option to move 2 squares

//The three unique movements of a black pawn (Push, Capture, and Move2)
std::vector<Coord> dirBpawnPush = {Coord(0, -1)};
std::vector<Coord> dirBpawnCapture = {Coord(1, -1),
                                    Coord(-1, -1)};
std::vector<Coord> dirBpawnMove2 = {Coord(0, -2)};  //Black Pawn on a starting rank has option to move 2 squares

// returns a vector<Coord> of all pieces with same ePieceCode
std::vector<Coord> findPieces(Board b, ePieceCode piece)
{
    Piece **board = b.getBoard();
    std::vector<Coord> pieces;

    //Searches all squares
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

bool rayCheckHelper(Board b, Coord piece, std::vector<Coord> dir, ePieceCode code)
{
    for(unsigned int k =0; k< dir.size(); k++)
    {
        Coord possibleMove = piece + dir[k];

        while ((b.inside(possibleMove) && (b.getPiece(possibleMove).empty())))
        {
            possibleMove = possibleMove + dir[k];
        }
        if(b.inside(possibleMove) && b.getPiece(possibleMove) == code)
            return true;
    }
    return false;
}

bool squareCheckHelper(Board b, Coord piece, std::vector<Coord> dir, ePieceCode code)
{
    for(unsigned int k=0; k<dir.size(); k++)
    {
        Coord possibleMove = piece +dir[k];
        if(b.inside(possibleMove) && b.getPiece(possibleMove) == code)
            return true;
    }
    return false;
}

//Function checks a board and tests if the king is in check
bool inCheck(Board b, Move m)
{
    std::vector <Coord> pieceV;
    Board b2 = b.makeMove(m);  // This is the board if the move is made

    //set pieceV to the correct color
    if(b.isWhite()){
        pieceV = findPieces(b2, epcWking); //cast code to correspoding white ePieceCode
    }
    else {
        pieceV = findPieces(b2, epcBking); //cast code to correspoding black ePieceCode
    }
    // std::cout << b2 << std::endl;
    // std::cout << pieceV.size() << std::endl;
    Coord piece = pieceV[0];

    if(b.isWhite())
     return (rayCheckHelper(b2, piece, dirRook,epcBrook)
            || rayCheckHelper(b2, piece, dirQueen, epcBqueen)
            || rayCheckHelper(b2, piece, dirBishop, epcBbishop)
            || squareCheckHelper(b2, piece, dirKnight, epcBknight)
            || squareCheckHelper(b2, piece, dirKing, epcBking)
            || squareCheckHelper(b2, piece, dirWpawnCapture, epcBpawn));
    else
     return (rayCheckHelper(b2, piece, dirRook, epcWrook)
            || rayCheckHelper(b2, piece, dirQueen, epcWqueen)
            || rayCheckHelper(b2, piece, dirBishop, epcWbishop)
            || squareCheckHelper(b2, piece, dirKnight, epcWknight)
            || squareCheckHelper(b2, piece, dirKing, epcWking)
            || squareCheckHelper(b2, piece, dirBpawnCapture, epcWpawn));
    return false;
}

bool inCheck(Board b)
{
    std::vector <Coord> pieceV;
    //set pieceV to the correct color
    if(b.isWhite()){
        pieceV = findPieces(b, epcBking); //cast code to correspoding white ePieceCode
    }
    else {
        pieceV = findPieces(b, epcWking); //cast code to correspoding black ePieceCode
    }
    // std::cout << b2 << std::endl;
    // std::cout << pieceV.size() << std::endl;
    Coord piece = pieceV[0];

        if(b.isWhite())
         return (rayCheckHelper(b, piece, dirRook,epcBrook)
                || rayCheckHelper(b, piece, dirQueen, epcBqueen)
                || rayCheckHelper(b, piece, dirBishop, epcBbishop)
                || squareCheckHelper(b, piece, dirKnight, epcBknight)
                || squareCheckHelper(b, piece, dirKing, epcBking)
                || squareCheckHelper(b, piece, dirWpawnCapture, epcBpawn));

        else
         return (rayCheckHelper(b, piece, dirRook, epcWrook)
                || rayCheckHelper(b, piece, dirQueen, epcWqueen)
                || rayCheckHelper(b, piece, dirBishop, epcWbishop)
                || squareCheckHelper(b, piece, dirKnight, epcWknight)
                || squareCheckHelper(b, piece, dirKing, epcWking)
                || squareCheckHelper(b, piece, dirBpawnCapture, epcWpawn));
    return false;
}


//Purpose: Add all possible moves to v for pieces that move in rays (Rooks, Bishops, Queens)
//rayMove pieces can "slide" (move) in directions given by dir until square is occupied.
void rayMove(std::vector<Move> &v, Board b, std::vector<Coord> &pieceV, std::vector<Coord> dir)
{
    for (unsigned int i = 0; i < pieceV.size(); i++)
    {
        Coord piece = pieceV[i]; //storing location
        for (unsigned int j = 0; j < dir.size(); j++)
        {
            Coord possibleMove = piece + dir[j];
            if(b.inside(possibleMove) && (b.getPiece(possibleMove).empty() || b.getPiece(possibleMove).getColor() == b.opposite()) && !inCheck(b, Move(piece, possibleMove)))
            {
                //Examines each square in the direction dir[j]
                //while the square is empty or opposite (color)
                //Note: When the possibleMove is occupied by same color piece. break while loop (do not examine rest of the squares in that direction)
                while (b.inside(possibleMove) && (b.getPiece(possibleMove).empty() || b.getPiece(possibleMove).getColor() == b.opposite()))
                {
                    //if square is occupied by enemy, option to occupy square. break while loop
                    if (b.getPiece(possibleMove).getColor() == b.opposite())
                    {
                        // Board b2 = b.makeMove(Move(piece, possibleMove));
                        // std::cout<<b2<<endl;
                        v.push_back(Move(piece, possibleMove));
                        break;
                    }
                    //else add possibleMove and slide to the next square in the same direction
                    else
                    {
                        v.push_back(Move(piece, possibleMove));
                        possibleMove = possibleMove + dir[j];
                    }
                }
            }

        }
    }
}

//Purpose: Add all possible moves to v for pieces that move to a single square in a direction
//squareMove pieces can move to only the first square for each direction ray
void squareMove(std::vector<Move> &v, Board b, std::vector<Coord> &pieceV, std::vector<Coord> dir)
{
    for (unsigned int i = 0; i < pieceV.size(); i++)
    {
        Coord piece = pieceV[i]; //storing location
        for (unsigned int j = 0; j < 8; j++)
        {
            Coord possibleMove = piece + dir[j];
            if (b.inside(possibleMove) && (b.getPiece(possibleMove).empty() || b.getPiece(possibleMove).getColor() == b.opposite()) && !inCheck(b, Move(piece, possibleMove)))
                v.push_back(Move(piece, possibleMove)); //if square is empty or occupied by enemy, add possibleMove to v
        }
    }
}

//Purpose: adds to v by generating all moves based off 3 conditional types of movements
void pawnMove(std::vector<Move> &v, Board b, std::vector<Coord> &pieceV, std::vector<Coord> push, std::vector<Coord> move2, std::vector<Coord> dir3)
{
    for (unsigned int i = 0; i < pieceV.size(); i++)
    {
        Coord piece = pieceV[i];
        Coord possibleMove = piece + push[0]; //possibleMove set to a pawn push

        //Checks forward square for pawn push direction and checks for special 2 square move
        if (b.inside(possibleMove) && !inCheck(b, Move(piece, possibleMove)) && (b.getPiece(possibleMove).empty()) && !inCheck(b, Move(piece, possibleMove))) //tests a pawn push
        {
            v.push_back(Move(piece, possibleMove));

            possibleMove = piece + move2[0]; //possibleMove set to special 2 square move
            if ((piece.y == (b.isWhite() ? 1 : 6)) && b.getPiece(possibleMove).empty()) // ???? KEVINNNN THIS SHOULDNT BE WORKING
                v.push_back(Move(piece, possibleMove));
        }

        //for loop for the two capture directions
        for(int j=0; j<2; j++)
        {
            possibleMove = piece + dir3[j]; //possibleMove set to a pawn capture direction
            if(b.inside(possibleMove)&& !inCheck(b, Move(piece, possibleMove))&&b.getPiece(possibleMove).getColor() == b.opposite() && !inCheck(b, Move(piece, possibleMove))) // test opposite color piece in square
                    v.push_back(Move(piece,possibleMove));
        }
    }
}
void generateMove(std::vector<Move> &v, Board b, int code)
{
    std::vector<Coord> pieceV;

    // sets pieceV to the correct color
    if (b.isWhite())
        pieceV = findPieces(b, (ePieceCode)code); //cast code to correspoding white ePieceCode
    else
        pieceV = findPieces(b, (ePieceCode)(code+7)); //cast code to correspoding black ePieceCode

    //Based on the ePieceCode, the appropriate move function is called with appropriate parameters
    switch(code)
    {
        //each move function parameters are
        //all possible moves vector v, the Board b, a vector of all piece types, and vector direction the piece moves
        case 1: //Pawn move
            if(b.isWhite())
                {pawnMove(v, b, pieceV, dirWpawnPush, dirWpawnMove2, dirWpawnCapture); break;}
            else
                {pawnMove(v, b, pieceV, dirBpawnPush, dirBpawnMove2, dirBpawnCapture); break;}
        case 2://Knight move
            squareMove(v, b, pieceV, dirKnight); break;
        case 3://Bishop move
            rayMove(v, b, pieceV, dirBishop); break;
        case 4://Rook move
            rayMove(v, b, pieceV, dirRook); break;
        case 5://Queen move
            rayMove(v, b, pieceV, dirQueen); break;
        case 6://king move
            squareMove(v, b, pieceV, dirKing); break;

    }
}

std::vector<Move> generateMoveList(const Board &b)
{
    std::vector<Move> v;

    //generates all the possible moves for the code's ePieceCode representation
    //1-6 of enum ePieceCode are piece types with a corresponding number
    for(int code=1; code<7; code++)
    {
        generateMove(v, b, code);
    }
    return v;
}
}
