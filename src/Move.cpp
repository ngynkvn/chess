#include "Move.h"
#include <iostream>


coordinate operator+(const coordinate& l, const coordinate& r) 
{
  return {l.first + r.first, l.second + r.second};
}
coordinate operator-(const coordinate& l, const coordinate& r) 
{
  return {l.first - r.first, l.second - r.second};
}

bool valid_coordinate(const coordinate& c) {
  auto [x, y] = c;
  return x > -1 && x < 8 && y > -1 && y < 8;
}
/** 
 * Various constructors for creating Move class objects.
 */
Move::Move(int fromX, int fromY, int toX, int toY) : from(fromX, fromY), to(toX, toY) 
{
}
Move::Move(coordinate from, coordinate to) : from(from), to(to)
{
}
Move::Move(coordinate from, coordinate to, MoveType moveType) : from(from), to(to), moveType(moveType)
{
}
Move::Move(std::string input) : Move('h' - input.at(0), input.at(1) - '1', 'h' - input.at(2), input.at(3) - '1') 
{
}
std::ostream &operator<<(std::ostream &os, const coordinate &coordinate)
{
    os << (char)('h' - coordinate.first) << coordinate.second + 1;
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
