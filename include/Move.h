#ifndef MOVE_H
#define MOVE_H

#include <ostream>

struct Coord
{
    int x;
    int y;
    Coord() : x(-1),y(-1){};
    Coord(int x, int y) : x(x), y(y){};
    Coord operator+(const Coord &other) { return Coord(x + other.x, y + other.y); };
    friend std::ostream &operator<<(std::ostream &, const Coord &);
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
