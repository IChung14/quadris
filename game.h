#ifndef __GAME_H__
#define __GAME_H__

// may need to change cuz of circular inclusion
#include "grid.h"
#include "level.h"
#include <iostream>
#include <string>
#include "graphicdisplay.h"

class Game{
    GraphicDisplay *graph;
    Grid board;
    int score;
    static int highScore;
    Level l;
    bool graphOn;
    bool isLost;
public:
    Game(std::string scriptfile = "sequence.txt", bool graphOn = true, int startLevel = 0); // added startLevel
    ~Game();
    void lost();
    void callFunction(std::string name);
    void scoreLine(int num);
    void scoreBlock(int blockLvl);
    friend std::ostream &operator<<(std::ostream &out, const Game &g);
};

#endif
