#include <iostream>
#include <vector>
#include <utility>
#include "block.h"
#include "cell.h"
using namespace std;

// Block functions
Block::Block( vector<Cell*> cells, char type, int lvl, bool isHeavy, string facing ): 
              cells{cells}, type{type}, lvl{lvl},  isHeavy{isHeavy}, facing{facing} {}
Block::~Block(){
    for(auto &i : cells){
        i->setBlock(nullptr);
    }
}

// find lowerleft
int Block::largestRow() {
  // find largest row number
  int largeRow = cells[0]->getRow();

  for (unsigned int i = 0; i < cells.size(); i++) {
    if (cells[i]->getRow() > largeRow) {
      largeRow = cells[i]->getRow();
    }  
  }
 
  return largeRow;
}

int Block::smallestCol() {
  // find smallest col number
  int smallCol = cells[0]->getCol();

  for (unsigned int i = 0; i < cells.size(); i++) {
    if (cells[i]->getCol() < smallCol) {
      smallCol = cells[i]->getCol();
    }
  }

  return smallCol;
}

vector<pair<int, int>> Block::current() const {
  // set up
  vector<pair<int, int>> cur;
  
  // grab coordinates of each cell currently in block 
  for (unsigned int i = 0; i < cells.size(); i++) {
    pair<int, int> newPair;
    newPair = make_pair(cells[i]->getRow(), cells[i]->getCol());
     
    // store in cur
    cur.emplace_back(newPair);
  }

  return cur;
}

pair<int, int> Block::lowerLeft() {
  // create pair
  pair<int, int> lowleft;

  int row = largestRow();
  int col = smallestCol();
  lowleft = make_pair( row, col );

  return lowleft;
}

bool Block::isEmpty() {
  if ( cells.size() == 0 ) {    // cells is empty
    return true;
  } else {                      // cells is not empty
    return false;
  }
}

void Block::removeCell( Cell* cellPtr ) {
  for ( unsigned int i = 0; i < cells.size(); i++ ) {
    // found the cellPtr in Block at ith element of cells
    if ( cellPtr == cells[i] ) {
      cells.erase( cells.begin() + i );  // erase ith element in cell
      break;
    }
  }
}


// mutators/accessor
void Block::set( vector<Cell*> coord ) { this->cells = coord; }
void Block::setType( char newChar ) { this->type = newChar; }

int Block::getLvl() { return this->lvl; }
char Block::getType() { return this->type; }
string Block::getFacing() { return this->facing; }
bool Block::getIsHeavy() { return this->isHeavy; }


// block movement
vector<pair<int, int>> Block::left() {
  // set up
  vector<pair<int, int>> coord;

  // shift all cells to the left
  for (unsigned int i = 0; i < cells.size(); i++) {
    // shift
    pair<int, int> newPair;
    newPair = make_pair( cells[i]->getRow(), cells[i]->getCol() - 1 );

    // store
    coord.emplace_back( newPair );
  }

  return coord;
}

vector<pair<int, int>> Block::right() {
  // set up
  vector<pair<int, int>> coord;

  // shift all cells to the left
  for (unsigned int i = 0; i < cells.size(); i++) {
    // shift
    pair<int, int> newPair;
    newPair = make_pair( cells[i]->getRow(), cells[i]->getCol() + 1 );

    // store
    coord.emplace_back( newPair );
  }

  return coord;
}

vector<pair<int, int>> Block::down() {
  // set up
  vector<pair<int, int>> coord;

  // shift all cells to the left
  for (unsigned int i = 0; i < cells.size(); i++) {
    // shift
    pair<int, int> newPair;
    newPair = make_pair( cells[i]->getRow() + 1, cells[i]->getCol() );

    // store
    coord.emplace_back( newPair );
  }

  return coord;
}


vector<pair<int, int>> Block::clockwise() {
  // set up
  vector<pair<int, int>> coord;
  int rotLargeRow = cells[0]->getRow();   // largest row in rotated block
  int rotSmallCol = cells[0]->getCol();   // smallest col in rotated block
  
  // rotate the block clockwise using matrix multiplication
  // set first cell as pivot point
  int pivotRow = cells[0]->getRow();
  int pivotCol = cells[0]->getCol();

  for (unsigned int i = 0; i < cells.size(); i++) {
    // current vector
    int row = cells[i]->getRow();
    int col = cells[i]->getCol();

    // find relative vector
    row = row - pivotRow;
    col = col - pivotCol;

    // rotate using matrix multiplication
    int temp = row;
    row = (row * 0) + (col * 1);
    col = (temp * (-1)) + (col * 0);
  
    // return to original coordinates
    row = row + pivotRow;
    col = col + pivotCol;

    // find larestRow and smallestCol in rotated block
    if (row > rotLargeRow) { rotLargeRow = row; }
    if (col < rotSmallCol) { rotSmallCol = col; }
 
    // store values 
    pair<int, int> newPair;
    newPair = make_pair( row, col );
    coord.emplace_back( newPair );
  }

  // maintain smallest rectangle
  int largeRow = largestRow();
  int smallCol = smallestCol();

  int rowDiff = largeRow - rotLargeRow;
  int colDiff = smallCol - rotSmallCol;
  

  for(unsigned int i = 0; i < coord.size(); i++) {
    coord[i].first = coord[i].first + rowDiff;
    coord[i].second = coord[i].second + colDiff;
  }

  return coord;
}

vector<pair<int, int>> Block::counterclockwise() {
  // set up
  vector<pair<int, int>> coord;
  int rotLargeRow = cells[0]->getRow();   // largest row in rotated block
  int rotSmallCol = cells[0]->getCol();   // smallest col in rotated block


  // rotate the block clockwise using matrix multiplication
  // set first cell as pivot point
  int pivotRow = cells[0]->getRow();
  int pivotCol = cells[0]->getCol();

  for (unsigned int i = 0; i < cells.size(); i++) {
    // current vector
    int row = cells[i]->getRow();
    int col = cells[i]->getCol();

    // find relative vector
    row = row - pivotRow;
    col = col - pivotCol;

    // rotate using matrix multiplication
    int temp = row;
    row = (row * 0) + (col * (-1));
    col = (temp * 1) + (col * 0);

    // return to original coordinates
    row = row + pivotRow;
    col = col + pivotCol;

    // find larestRow and smallestCol in rotated block
    if (row > rotLargeRow) { rotLargeRow = row; }
    if (col < rotSmallCol) { rotSmallCol = col; }

    // store values
    pair<int, int> newPair;
    newPair = make_pair( row, col );
    coord.emplace_back( newPair );
  }
  
  // maintain smallest rectangle
  int largeRow = largestRow();
  int smallCol = smallestCol();

  int rowDiff = largeRow - rotLargeRow;
  int colDiff = smallCol - rotSmallCol;

  for(unsigned int i = 0; i < coord.size(); i++) {
    coord[i].first = coord[i].first + rowDiff;
    coord[i].second = coord[i].second + colDiff;
  }

  return coord;
}   
