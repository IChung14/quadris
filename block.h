#ifndef BLOCK_H
#define BLOCK_H
#include <vector>
#include <utility>
#include <iostream>

struct Cell;

// abstract box
class Block {
  std::vector<Cell*> cells;
  char type;
  const int lvl;
  const bool isHeavy = false;
  std::string facing = "north"; 

  // helpers
  int largestRow();
  int smallestCol();


 public:
  // ctor  
  Block( std::vector<Cell*> cells, char type, int lvl, bool isHeavy = false, std::string facing = "north" );
  ~Block();
  // block functions
  std::vector<std::pair<int, int>> predict( std::string command );  // returns expected coordinates of the 
                                                               //  block after the executing the given command

  std::vector<std::pair<int, int>> current() const;  // returns current coordinates

  void set( std::vector<Cell*> coord ); // sets the cells field to equal provided coord 

  std::pair<int, int> lowerLeft(); // returns a pair, representing the coordinates of the lowerleft 
                                   //   corner of the rectangle containing the block
  
  bool isEmpty();  // returns true is cells is empty
  void removeCell( Cell* cellPtr );  // removes given cell ptr from cells
  
  // accessor/mutators
  void setType( char newChar );

  int getLvl();
  char getType();
  std::string getFacing();
  bool getIsHeavy();



  // block movement functions
  std::vector<std::pair<int, int>> left();
  std::vector<std::pair<int, int>> right();
  std::vector<std::pair<int, int>> down();
  std::vector<std::pair<int, int>> clockwise();
  std::vector<std::pair<int, int>> counterclockwise();
};  
#endif
