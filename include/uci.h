#ifndef UCI_H
#define UCI_H

#include "Move.h"
#include "Piece.h"
#include "Board.h"
#include <vector>

class UCI
{
  public:
    UCI();
    static void newUCI();
    static void inputIsReady();
    void debug();
    void setOption(string);
    void uciNewGame();
    void inputIsGo();
private:
    string nameOfEngine;
    string Line;
};

#endif