#ifndef MOVE_H
#define MOVE_H

#include <ostream>

/** 
 * Coord is a simple x,y struct to allow for easy interfacing to the Board class. Can be constructed from either integers
 * or rank and file. Note that coord does not test the validity of a position as that is left up to the board to confirm.
 */
struct Coord
{
  int x;
  int y;
  Coord() : x(-1), y(-1){};
  Coord(int x, int y) : x(x), y(y){};
  Coord(char letter, int y) : x('h'-letter), y(y - 1){};
  Coord operator+(const Coord &other) { return Coord(x + other.x, y + other.y); };
  Coord operator-(const Coord &other) { return Coord(x - other.x, y - other.y); };
  bool operator==(const Coord &c) { return c.x == x && c.y == y; }
  friend std::ostream &operator<<(std::ostream &, const Coord &);
};

/** 
 * Move consists of a FROM coordinate and a TO coordinate to signify movement of pieces. This is helpful for when
 * pieces need to be moved as it is necessary to know the location the piece comes from and it's destination.
 * Overloaded operators allow for comparison and an overloaded ostream operator prints out the move in rank-file format.
 */
class Move
{
public:
  Move(int, int, int, int);
  Move(Coord, Coord);
  Move(std::string);
  Coord from() const;
  Coord to() const;
  bool operator==(const Move &m) const { return m.from() == Coord(fromX, fromY) && m.to() == Coord(toX, toY); }
  bool operator!=(const Move &m) const { return !(m.from() == Coord(fromX, fromY)) || !(m.to() == Coord(toX, toY)); }
  friend std::ostream &operator<<(std::ostream &, const Move &);

private:
  int fromX;
  int fromY;
  int toX;
  int toY;
};

#endif
