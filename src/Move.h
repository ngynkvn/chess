#ifndef MOVE_H
#define MOVE_H

#include <ostream>


enum MoveType {
    Sliding,
    Square,
    Push,
    DoublePush,
    Capture,
    Castle,
    EP,
};

/** 
 * coordinate is a simple x,y struct to allow for easy interfacing to the Board class. Can be constructed from either integers
 * or rank and file. Note that coordinate does not test the validity of a position as that is left up to the board to confirm.
 */
//TODO rm
using coordinate = std::pair<int, int>;
coordinate operator+(const coordinate& l, const coordinate& r);
coordinate operator-(const coordinate& l, const coordinate& r);
std::ostream &operator<<(std::ostream &os, const coordinate &coordinate);
/** 
 * Move consists of a FROM coordinate and a TO coordinate to signify movement of pieces. This is helpful for when
 * pieces need to be moved as it is necessary to know the location the piece comes from and it's destination.
 * Overloaded operators allow for comparison and an overloaded ostream operator prints out the move in rank-file format.
 */
class Move
{
public:
  Move(int, int, int, int);
  Move(coordinate, coordinate);
  Move(coordinate, coordinate, MoveType);
  Move(std::string);
  coordinate from;
  coordinate to;
  MoveType moveType;
  bool operator==(const Move &m) const { return m.from == from && m.to == to; }
  bool operator!=(const Move &m) const { return !(operator==(m)); }
  friend std::ostream &operator<<(std::ostream &, const Move &);
};


#endif
