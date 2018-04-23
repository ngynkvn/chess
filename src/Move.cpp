#include "Move.h"
#include <iostream>

/** 
 * Various constructors for creating Move class objects.
 */
Move::Move(int fromX, int fromY, int toX, int toY) : fromX(fromX), fromY(fromY), toX(toX), toY(toY) 
{
}
Move::Move(Coord from, Coord to) : Move(from.x, from.y, to.x, to.y) 
{
}
Move::Move(std::string input) : Move('h' - input.at(0), input.at(1) - '1', 'h' - input.at(2), input.at(3) - '1') 
{
}

//Returns the from coordinates that the pieces are coming from
Coord Move::from() const
{
    Coord c(fromX, fromY);
    return c;
}

//Returns the to coordinates that the piece is going to
Coord Move::to() const
{
    Coord c(toX, toY);
    return c;
}

std::ostream &operator<<(std::ostream &os, const Coord &coord)
{
    os << (char)('h' - coord.x) << coord.y + 1;
    return os;
}
std::ostream &operator<<(std::ostream &os, const Move &move)
{
    if (move == Move(-1, -1, -1, -1))
    {
        os << "no move";
        return os;
    }
    os << move.from() << move.to();
    return os;
}
