#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include <utility>
#include <vector>
#include "subject.h"

class Block;

class Cell : public Subject {
	int row, col;
        char type;
	Block *partOf;
  // Add other private members if necessary 

 public:
	Cell();  // Default constructor
	~Cell();
	Cell(int x, int y, char c = ' ');

	char getType() const;
	int getRow() const;
	int getCol() const;
	Block *getBlock() const;
	void setType(char c);
	void setRow(int r);
	void setCoor(int x, int y);
	void setBlock(Block *newBlock);
};
#endif
