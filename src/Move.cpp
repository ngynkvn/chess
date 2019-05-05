#include "Move.h"
#include <iostream>


Coord operator+(const Coord& l, const Coord& r) 
{
  return {l.first + r.first, l.second + r.second};
}
Coord operator+=(const Coord& l, const Coord& r) 
{
  return {l.first + r.first, l.second + r.second};
}
Coord operator-(const Coord& l, const Coord& r) 
{
  return {l.first - r.first, l.second - r.second};
}
/** 
 * Various constructors for creating Move class objects.
 */
Move::Move(int fromX, int fromY, int toX, int toY) : from(fromX, fromY), to(toX, toY) 
{
}
Move::Move(Coord from, Coord to) : from(from), to(to)
{
}
Move::Move(std::string input) : Move('h' - input.at(0), input.at(1) - '1', 'h' - input.at(2), input.at(3) - '1') 
{
}
std::ostream &operator<<(std::ostream &os, const Coord &coord)
{
    os << (char)('h' - coord.first) << coord.second + 1;
    return os;
}
std::ostream &operator<<(std::ostream &os, const Move &move)
{
    if (move == Move(-1, -1, -1, -1))
    {
        os << "no move";
        return os;
    }
    os << move.from << move.to;
    return os;
}
