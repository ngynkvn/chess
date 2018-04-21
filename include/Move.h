#ifndef MOVE_H
#define MOVE_H

#include <ostream>

struct Coord
{
  int x;
  int y;
  Coord() : x(-1), y(-1){};
  Coord(int x, int y) : x(x), y(y){};
  Coord operator+(const Coord &other) { return Coord(x + other.x, y + other.y); };
  bool operator==(const Coord &c) { return c.x == x && c.y == y; }
  friend std::ostream &operator<<(std::ostream &, const Coord &);
};

class Move
{
public:
  Move(int, int, int, int);
  Move(Coord, Coord);
  Move(std::string);
  Coord from() const;
  Coord to() const;
  bool operator==(const Move &m) const { return m.from() == Coord(fromX, fromY) && m.to() == Coord(toX, toY); }
  friend std::ostream &operator<<(std::ostream &, const Move &);

private:
  int fromX;
  int fromY;
  int toX;
  int toY;
};

#endif
