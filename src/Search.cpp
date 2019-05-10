#include "Search.h"
#include <iostream>
#include <map>
#include <assert.h>
#include <algorithm>
#include <functional>
#include "Movement.h"
namespace Search
{

ePieceCode getColor(ePieceCode code)
{
    return code == epcEmpty 
        ? epcEmpty 
        : code > Black ? ePieceCode::Black 
                       : ePieceCode::White;
}

Coord firstPieceOnRay(Coord point, Coord dirRay, const Board &b)
{
    do
    {
        point = point + dirRay;
    } while (b.inside(point) && b.getPiece(point) == epcEmpty);
    return point;
}

bool checkHelper(const Board &b, Coord targetPiece, std::vector<Coord> dirs, int epcCode, bool ray)
{
    auto code = static_cast<ePieceCode>(epcCode);
    return std::any_of(dirs.begin(), dirs.end(), [&](const Coord &dir) {
        Coord possibleMove = ray ? firstPieceOnRay(targetPiece, dir, b) : targetPiece + dir;
        return b.inside(possibleMove) && b.getPiece(possibleMove) == code;
    });
}
template <ePieceCode EnemyColor>
bool checkPawn(const Board &b, Coord targetPiece)
{
    constexpr int DIRECTION_OF_ATTACK = EnemyColor == White ? -1 : 1;
    constexpr ePieceCode enemyPawn = EnemyColor == White ? epcWpawn : epcWpawn;
    constexpr std::array<Coord, 2> captures{Coord(1, DIRECTION_OF_ATTACK), Coord(-1, DIRECTION_OF_ATTACK)};
    for (Coord cap : captures)
    {
        Coord possibleMove = targetPiece + cap;
        if (b.inside(possibleMove) && b.getPiece(possibleMove) == enemyPawn)
        {
            return true;
        }
    }
    return false;
}
bool checkHelper(const Board &b, Coord targetPiece, Movement::MoveSet m)
{
    switch(m.piece) {
        case Pawn:
            return b.isWhite() ? checkPawn<Black>(b, targetPiece) : checkPawn<White>(b, targetPiece);
        default:
            return checkHelper(b, targetPiece, m.directions, m.piece + (b.isWhite() ? White : Black), m.ray);
    }
}

bool inCheck(Board &b, const Move& consideringMove)
{
    bool turnIsWhite = b.isWhite();
    int c = turnIsWhite ? White : Black;

    b.makeMove(consideringMove);
    std::vector<Coord> pieceCoords = Cache::findPieces(b, King + c);
    Coord piece = pieceCoords.at(0);

    bool result = std::any_of(Movement::movements.begin(), Movement::movements.end(), [&](Movement::MoveSet m) {
        return checkHelper(b, piece, m);
    });

    b.unmakeMove();
    return result;
}

template<MoveType M>
void genMoves(Board& b, Coord piece, std::vector<Move>& moves, const std::vector<Coord>& directions) {
    for (auto j : directions)
    {
        Coord possibleMove = piece + j;
        if constexpr(M == Sliding) {
            while (b.inside(possibleMove) && b.getPiece(possibleMove) == epcEmpty)
            {
                moves.emplace_back(piece, possibleMove, M);
                possibleMove = possibleMove + j;
            }
        }
        if (!b.inside(possibleMove))
            continue;
        auto pieceTo = b.getPiece(possibleMove);
        if (Search::getColor(pieceTo) == b.opposite()){
            moves.emplace_back(piece, possibleMove, MoveType::Capture);
        }
        else if (pieceTo == epcEmpty) {
            moves.emplace_back(piece,possibleMove, M);
        }
    }
}

template<ePieceCode Color>
void genPawnMoves(Board& b, Coord piece, std::vector<Move>& moves) {
    constexpr int DIRECTION_OF_ATTACK = Color == White ? 1 : -1;
    constexpr int HOME_ROW = Color == White ? 1 : 6;
    constexpr ePieceCode oppositeColor = Color == White ? Black : White;
    constexpr Coord push(0, DIRECTION_OF_ATTACK);
    constexpr std::array<Coord, 2> captures{Coord(1, DIRECTION_OF_ATTACK), Coord(-1, DIRECTION_OF_ATTACK)};
    Coord possibleMove = piece + push;
    if (b.inside(possibleMove) && b.getPiece(possibleMove) == epcEmpty)
    {
        moves.emplace_back(piece, possibleMove, MoveType::Push);
        
    }

    auto possibleMove2 = possibleMove + push;
    if (piece.second == HOME_ROW 
        && b.getPiece(possibleMove) == epcEmpty 
        && b.getPiece(possibleMove2) == epcEmpty)
    {
        moves.emplace_back(piece, possibleMove2, MoveType::DoublePush);
    }

    for (Coord cap : captures)
    {
        Coord possibleMove = piece + cap;
        if (b.inside(possibleMove) && Search::getColor(b.getPiece(possibleMove)) == oppositeColor)
        {
            moves.emplace_back(piece, possibleMove, MoveType::Capture);
        }
    }
}

std::vector<Move> generateMoveList(Board &b)
{
    auto board_array = b.getBoard();
    std::vector<Move> preLegal;
    for (int i = 0; i < 64; i++) {
        auto p = board_array[i];
        if (b.currColor() == getColor(p)) {
            Coord c(i % 8, i / 8);
            switch(p) {
                case epcWpawn:
                    genPawnMoves<White>(b, c, preLegal);
                    break;
                case epcBpawn:
                    genPawnMoves<Black>(b, c, preLegal);
                    break;
                case epcWqueen:
                case epcBqueen:
                    genMoves<MoveType::Sliding>(b, c, preLegal, Movement::dirQueen);
                    break;
                case epcWbishop:
                case epcBbishop:
                    genMoves<MoveType::Sliding>(b, c, preLegal, Movement::dirBishop);
                    break;
                case epcWrook:
                case epcBrook:
                    genMoves<MoveType::Sliding>(b, c, preLegal, Movement::dirRook);
                    break;
                case epcWking:
                case epcBking:
                    genMoves<MoveType::Square>(b, c, preLegal, Movement::dirKing);
                    break;
                case epcWknight:
                case epcBknight:
                    genMoves<MoveType::Square>(b, c, preLegal, Movement::dirKnight);
                    break;
                default:
                    throw;
            }
        }
    }
    std::vector<Move> legal;
    for (auto m : preLegal) {
        if (!Search::inCheck(b, m)) {
            legal.push_back(m);
        }
    }
    return legal;
}

} // namespace Search
