#ifndef _LEVEL_H_
#define _LEVEL_H_

// may have to change cuz of circular inclusion
//#include "game.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

class Level{
    int lvl;
    bool random; // SOMEONE CALLING NON-RANDOM THEN RANDOM KEYWORD NEEDS TO CHANGE THIS VAR.
    bool isHeavy;
    std::string scriptfile;
 //   Game * game;
    char nextBlock;
    std::vector <std::vector <int>> gameSpecs;//PPL CALLING NON-RANDOM THEN RANDOM NEEDS TO CLEAN THIS
    std::vector <char> level0Seq;
    std::vector <char> nonRandSeq;
    int curblockIndex; // index to keep track of place in vector
public:
    Level (std::string scriptfile, int startLevel);
    ~Level();
    void nonRandom(std::string filename);
    // random
    void createBlock();
    void printBlock() const;
    // level switching
    void levelUp();
    void levelDown();
    void setLevel(int level);
    // accessors
    char getNext() const;
    int getLevel() const;
    bool getIsHeavy() const;
    // mutator
    void setRandom(bool type);
    friend std::ostream &operator<<(std::ostream &out, const Level &);
};

#endif
