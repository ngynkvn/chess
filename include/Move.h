#ifndef MOVE_H
#define MOVE_H

class Move 
{
    public:
      Coord from();
      Coord to();
    private:
      Coord from;
      Coord to;
};

struct Coord {
    int x;
    int y;
    Coord(int x, int y) : x(x), y(y) {};
};

#endif