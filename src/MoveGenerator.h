#if !defined(MOVEGEN_H)
#define MOVEGEN_H

#include "Board.h"
class MoveGenerator {
    protected:
        Board board;
        Board& b = board; //TODO zzz REMOVE this i just did this bc im lazy
        bool ray;
        std::vector<Coord> directions;
        std::vector<Move>* moves;
    public:
        virtual void genMove(Coord) = 0;
        virtual ~MoveGenerator() = 0;
};
inline MoveGenerator::~MoveGenerator() { }  // defined even though it's pure virtual; it's faster this way; trust me

class BaseMoveGenerator : public MoveGenerator {
    public:
        BaseMoveGenerator(Board& board, bool ray, std::vector<Coord>& directions, std::vector<Move>* moves) {
            this->board = board;
            this->ray = ray;
            this->directions = directions;
            this->moves = moves;
        };
        void genMove(Coord);
};
class PawnMoveGenerator : public MoveGenerator {
    public:
        PawnMoveGenerator(Board& board, std::vector<Move>* moves) {
            this->board = board;
            this->moves = moves;
        };
        void genMove(Coord);
};

#endif // MOVEGEN_H