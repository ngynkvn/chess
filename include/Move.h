#ifndef MOVE_H
#define MOVE_H

struct Coord {
    int x;
    int y;
    Coord(int x, int y) : x(x), y(y) {};
};

class Move 
{
    public:
      Move(int, int, int, int);
      Move(Coord, Coord);
      Coord getFrom();
      Coord getTo();
    private:
    int fromX;
    int fromY;
    int toX;
    int toY;
};


#endif