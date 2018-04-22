#include <iostream>
#include <cstdlib>
#include <string.h>

#include "uci.h"

using namespace std;

int main()
{
    string nameOfEngine = "Chess Program";
    string Line; //Line given to the engine
    while (getline(cin, Line))
    {
        if (Line == "uci")
        {
            newUCI();
        }
        else if (Line == "isready")
        {
            inputIsReady();
        }
        else if (Line == "ucinewgame")
        {
            uciNewGame();
        }
        else if (Line.startsWith("setoption"))
        {
            setOption(Line);
        }
        else if (Line == "go")
        {
            inputIsGo();
        }
    }

    return 0;
}

//Prints out the id name, author, and that the uci is ok to run
void UCI::newUCI()
{
    cout << "id name" << nameOfEngine << endl;
    cout << "id author Group 3" << endl;
    cout << "uciok" << endl;
}

//Prints out "readyok" if the UCI isReady
void UCI::inputIsReady()
{
    cout << "readyok" << endl;
}

void UCI::debug()
{
    //The purpose of this method is to turn the debug mode on and off
    //By default the debug should be off
}

void UCI::setOption(string Line)
{
    //Sent when user wants to change the internal parameters
    //No values needed for button type
}

void UCI::uciNewGame()
{
    //The purpose of this method is to indicate to the engine that there is a new game
}

void UCI::inputIsGo()
{
    //The method will start to calculate and ponder when the engine recieves "Go"
}