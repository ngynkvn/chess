#ifndef MOVE_H
#define MOVE_H

struct Coord
{
    int x;
    int y;
    Coord() : x(-1),y(-1){};
    Coord(int x, int y) : x(x), y(y){};
    Coord operator+(const Coord &other) { return Coord(x + other.x, y + other.y); };
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