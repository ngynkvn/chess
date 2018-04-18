#include "Move.h"

Move::Move(int fromX, int fromY, int toX, int toY) : fromX(fromX), fromY(fromY), toX(toX), toY(toY) {}
Move::Move(Coord from, Coord to) : fromX(from.x), fromY(from.y), toX(to.x), toY(to.y) {}

Coord Move::from()
{
    Coord c(fromX, fromY);
    return c;
}

Coord Move::to()
{
    Coord c(toX, toY);
    return c;
}