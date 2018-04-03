#ifndef PIECE_H
#define PIECE_H


enum ePieceType
{
    no_type, // empty
    wPawn,
    bPawn,
    knight,
    bishop,
    rook,
    queen,
    king,
};

enum ePieceCode
{
    epcEmpty   = no_type,
    white = 0,
    epcWpawn   = wPawn,
    epcWoff    = bPawn, // may be used as off the board blocker in mailbox
    epcWknight = knight,
    epcWbishop = bishop,
    epcWrook   = rook,
    epcWqueen  = queen,
    epcWking   = king,

    black  = 10, // color code, may used as off the board blocker in mailbox
    epcBoff    = wPawn  + black, // may be used as off the board blocker in mailbox
    epcBpawn   = bPawn  + black,
    epcBknight = knight + black,
    epcBbishop = bishop + black,
    epcBrook   = rook   + black,
    epcBqueen  = queen  + black,
    epcBking   = king   + black,
};

class Piece {
private:
    ePieceCode pieceCode;
public:
    Piece(ePieceCode);
    int getColor();
    int getPiece();
    // implement getters and constructor.
    // please make and use Piece as an IMMUTABLE data type (no modification allowed.)
};

#endif