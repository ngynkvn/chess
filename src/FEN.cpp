#include "Piece.h"
#include "Move.h"
#include "Board.h"
#include <ostream>
#include <vector>
#include <string>
#include <cctype>
#include <sstream>
#include <array>

_Board _Board::from_fen(std::string fen)
{
    _Board board;
    pieceCode epc[255];
    epc['p'] = pieceCode::Bpawn;
    epc['q'] = pieceCode::Bqueen;
    epc['r'] = pieceCode::Brook;
    epc['k'] = pieceCode::Bking;
    epc['n'] = pieceCode::Bknight;

    epc['P'] = pieceCode::Wpawn;
    epc['Q'] = pieceCode::Wqueen;
    epc['R'] = pieceCode::Wrook;
    epc['K'] = pieceCode::Wking;
    epc['N'] = pieceCode::Wknight;

    std::istringstream iss(fen);

    std::string b_str, active, castles, ep, half_move, full_move;

    iss >> b_str;
    iss >> active;
    iss >> castles;
    iss >> ep;
    iss >> half_move;
    iss >> full_move;

    size_t i = 0;
    for (auto it = b_str.begin(); it != b_str.end(); it++)
    {
        auto c = *it;
        if (std::isalpha(c))
        {
            board.state[i++] = epc[c];
        }
        else if (std::isdigit(c))
        {

            i += (*it) - '0';
        }
    }
    return board;
}