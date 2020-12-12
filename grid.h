#ifndef __GRID_H__
#define __GRID_H__
#include <iostream>
#include <vector>
#include "cell.h"

class GraphicDisplay;
class Level;
class Block;
class Game;
class Grid {
  std::vector<std::vector<Cell>> gameBoard;  // The actual grid. 
  std::vector<Block *> blocks;    // Size of the grid.
  Level *l;
  Game *g;
  int starCount;
  bool isLineGone;
  GraphicDisplay *gd;
  // The text display.
  // Add private members, if necessary.

 public:
  Grid(GraphicDisplay *gd);
  ~Grid();
  
  void assignLevel(Level *l);
  void assignGame(Game *g);
  bool move(std::string cmd);
  void createBlock();
  //void hint();
  void setBlock(std::string cmd);
/*
  void I();
  void J();
  void L();*/
  friend std::ostream &operator<<(std::ostream &out, const Grid &g);
 private:
  void placeStar();
  bool checkSide(std::vector<std::pair<int,int>> &p) const;
  bool checkHit(std::vector<std::pair<int,int>> &p) const;
  bool checkLine();
  void removeLine(int row);
  void moveCells(std::vector<std::pair<int,int>> &pred, std::vector<std::pair<int,int>> &cur, std::vector<Cell *> &predCell);
  
};

#endif
