#include <iostream>
#include <utility>
#include "subject.h"
#include "observer.h"
#include "cell.h"
#include "block.h"
using namespace std;

Cell::Cell() {}
Cell::Cell(int x, int y, char c) : row{ x }, col{ y }, type{ c }, partOf{nullptr} {}
Cell::~Cell() {
    if(partOf != nullptr){
        partOf->removeCell(this);
    }
    //cout << "if done" << endl;
}

char Cell::getType() const { return type; }
int Cell::getCol() const { return col; }
int Cell::getRow() const { return row; }
Block* Cell::getBlock() const { return partOf; }
void Cell::setType(char c) {
    type = c;
    notifyObservers();
}
void Cell::setRow(int r){
    row = r;
}
void Cell::setCoor(int x, int y) {
    row = x;
    col = y;
}
void Cell::setBlock(Block* newBlock){
    partOf = newBlock;
}
