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
      Coord from();
      Coord to();
    private:
    int fromX;
    int fromY;
    int toX;
    int toY;
};


#endif