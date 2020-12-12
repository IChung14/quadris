#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include "grid.h"
#include "level.h"
#include "cell.h"
#include "block.h"
#include "game.h"
#include "graphicdisplay.h"

using namespace std;

Grid::Grid(GraphicDisplay *gd):starCount{0}, isLineGone{false}, gd{gd}{
  for(int i=0;i<18;i++){
    gameBoard.emplace_back(vector<Cell>());
    for(int j=0;j<11;j++){
      gameBoard[i].emplace_back(Cell(i,j));
      gameBoard[i][j].attach(gd);
    }
  }
}

Grid::~Grid() {
    for(auto &i : blocks){
	delete i;
    }
}

void Grid::assignLevel(Level *lvl){
    l = lvl;
}

void Grid::assignGame(Game *g){
    this->g = g;
}

void Grid::setBlock(string blockType){
    pair<int, int> lowleft = blocks[0]->lowerLeft();
    vector<pair<int, int>> pred;
    vector<pair<int, int>> cur = blocks[0]->current();
    vector<Cell *> predCell;

    if(blockType == "I"){
        for(int i=0;i<4;i++){
            pred.emplace_back(lowleft);
            lowleft.second ++;
        }
    }else if(blockType == "J"){
        pred.emplace_back(lowleft);
        pred.emplace_back(pair<int,int> (lowleft.first-1,lowleft.second));
        pred.emplace_back(pair<int,int> (lowleft.first,lowleft.second+1));
        pred.emplace_back(pair<int,int> (lowleft.first,lowleft.second+2));
    }else if(blockType == "L"){
        pred.emplace_back(lowleft);
        pred.emplace_back(pair<int,int> (lowleft.first,lowleft.second+1));
        pred.emplace_back(pair<int,int> (lowleft.first,lowleft.second+2));
        pred.emplace_back(pair<int,int> (lowleft.first-1,lowleft.second+2));
    }else if(blockType == "O"){
        pred.emplace_back(lowleft);
        pred.emplace_back(pair<int,int> (lowleft.first,lowleft.second+1));
        pred.emplace_back(pair<int,int> (lowleft.first-1,lowleft.second));
        pred.emplace_back(pair<int,int> (lowleft.first-1,lowleft.second+1));
    }else if(blockType == "T"){
        pred.emplace_back(pair<int,int> (lowleft.first-1,lowleft.second));
        pred.emplace_back(pair<int,int> (lowleft.first-1,lowleft.second+1));
        pred.emplace_back(pair<int,int> (lowleft.first-1,lowleft.second+2));
        pred.emplace_back(pair<int,int> (lowleft.first,lowleft.second+1));
    }else if(blockType == "S"){
        pred.emplace_back(lowleft);
        pred.emplace_back(pair<int,int> (lowleft.first,lowleft.second+1));
        pred.emplace_back(pair<int,int> (lowleft.first-1,lowleft.second+1));
        pred.emplace_back(pair<int,int> (lowleft.first-1,lowleft.second+2));
    }else if(blockType == "Z"){
        pred.emplace_back(pair<int,int> (lowleft.first-1,lowleft.second));
        pred.emplace_back(pair<int,int> (lowleft.first-1,lowleft.second+1));
        pred.emplace_back(pair<int,int> (lowleft.first,lowleft.second+1));
        pred.emplace_back(pair<int,int> (lowleft.first,lowleft.second+2));
    }
    
    if (checkSide(pred) || checkHit(pred)) {
        cerr << "invalid "<< blockType << " conversion" << endl;
        return;
    }
    blocks[0]->setType(blockType[0]);
    moveCells(pred,cur,predCell);
    blocks[0]->set(predCell);
}

bool Grid::move(string cmd) {
	vector<pair<int, int>> cur = blocks[0]->current();
	vector<pair<int, int>> pred;
	vector<Cell *> predCell;
	
	if(cmd == "right"){
	    pred = blocks[0]->right();
	}else if(cmd == "left"){
	    pred = blocks[0]->left();
	}else if(cmd == "down"){
	    pred = blocks[0]->down();
	}else if(cmd == "clockwise"){
	    pred = blocks[0]->clockwise();
	}else if(cmd == "counterclockwise"){
	    pred = blocks[0]->counterclockwise();
	}else if(cmd == "drop"){
	    pred = blocks[0]->down();
	}

	if (checkSide(pred)) {
		cerr << "invalid move" << endl;
		return true;
	}
	if(checkHit(pred)){
	    if(cmd == "clockwise" || cmd == "counterclockwise"){
		cerr << "invalid rotation" << endl;
		return true;
	    }else if(cmd == "down" || cmd == "drop"){
	        if(!checkLine()) return false;
            }else{
                cerr << "invalid movement" << endl;
		return true;
            }
	    
	    if(isLineGone == false && l->getLevel() >= 3){
		starCount++;
	    }else{
		isLineGone = false;
		starCount = 0;
	    }

	    if(starCount >= 5 && l->getLevel() >= 3){
                placeStar();
                if(!checkLine()) {
		    return false;
		}
		starCount = 0;
	    }
	    
	    createBlock();
            return true;
	    
	}
	
	moveCells(pred,cur,predCell);
        blocks[0]->set(predCell);
	if(blocks[0]->getIsHeavy()){
	    cur = pred;
	    predCell.clear();

            for(auto &i : pred){
                i.first++;
            }
            if(checkHit(pred)){
                if(!checkLine()) return false;
		if(isLineGone == false && l->getLevel() >= 3){
	            starCount++;
        	}else{
		    isLineGone = false;
            	    starCount = 0;
        	}
     
        	if(starCount >= 5 && l->getLevel() >= 3){
	            placeStar();
        	    if(!checkLine()) {
                	return false;
	            }
        	    starCount = 0;
	        }
                createBlock();
		return true;
            }
	    moveCells(pred,cur,predCell);
            blocks[0]->set(predCell);
        }
            
	
	if(cmd == "drop"){
	    move(cmd);
	}
	return true;
}

void Grid::placeStar(){
	for(int i=0;i<18;i++){
		if(gameBoard[i][5].getType() != ' '){
			gameBoard[i-1][5].setType('*');
			return;
		}
	}
	gameBoard[17][5].setType('*');
}

void Grid::moveCells(vector<pair<int,int>> &pred, vector<pair<int,int>> &cur, vector<Cell *> &predCell){
    for (auto &i : cur) {
		gameBoard[i.first][i.second].setType(' ');
		gameBoard[i.first][i.second].setBlock(nullptr);
	}
	for (auto &i : pred) {
		gameBoard[i.first][i.second].setType(blocks[0]->getType());
		predCell.emplace_back(&gameBoard[i.first][i.second]);
		gameBoard[i.first][i.second].setBlock(blocks[0]);
	}
}

//checks if the move is out of side boundary
bool Grid::checkSide(vector<pair<int,int>> &p) const {
	for (auto &i : p) {
		if (i.second < 0 || i.second >10){
		    return true;
		}
	}
	return false;
}
bool Grid::checkHit(vector<pair<int,int>> &p) const {
    for (auto &i : p) {
        if (i.first < 0 || i.first >17){
		    return true;
	    }
	    if (gameBoard[i.first][i.second].getType() != ' ' && gameBoard[i.first][i.second].getBlock() != blocks[0]) {
		   	return true;
		}
    }
    
    return false;
}

bool Grid::checkLine(){
    vector<pair<int,int>> cur = blocks[0]->current();
    int lowestRemoved = 0;
    bool is_filled = true;
    int lineCount = 0;
    
    for(int i=0; i<18 ; i++){
        for(int j=0;j<11;j++){
            if(gameBoard[i][j].getType() == ' '){
                is_filled = false;
                break;
            }
        }
        if(is_filled){
	    if(lowestRemoved < i) lowestRemoved = i;
            removeLine(i);
            lineCount++;
        }
        is_filled = true;
    }

    if(lineCount > 0){
        g->scoreLine(lineCount);
	isLineGone = true;
	int initialRow = lowestRemoved;

	for(int i=0;i<=lowestRemoved;i++){
            for(int j=0;j<11;j++){
                if(!initialRow&&gameBoard[i][j].getType()!=' '){
		    initialRow = i;
		    i = 18;
		    break;
		}
            }
        }
	if(initialRow - lineCount <= 3){
	    initialRow = 4;
	}else{
	    initialRow -= lineCount;
	}

	for(int i= initialRow;i<=lowestRemoved;i++){
	    for(int j=0;j<11;j++){
		if(initialRow) gameBoard[i][j].notifyObservers();
	    }
	}
    }

    for(int i=0;i<int(blocks.size());i++){
        if(blocks[i]->isEmpty()){
            g->scoreBlock(blocks[i]->getLvl());
	    delete blocks[i];
	    blocks.erase(blocks.begin()+i);
        }
    }
    
    for(int i=0;i<4;i++){
        for(int j=0;j<11;j++){
            if(gameBoard[i][j].getType() != ' '){
                return false;
            }
        }
    }
    return true;
}

void Grid::removeLine(int row){
    gameBoard.erase(gameBoard.begin() + row);
    gameBoard.emplace(gameBoard.begin(), vector<Cell>());
    for(int j=0;j<11;j++){
        gameBoard[0].emplace_back(Cell(0,j));
	gameBoard[0][j].attach(gd);
    }
    for(int i=row; i > 0; i --){
        for(int j=0;j<11;j++){
            gameBoard[i][j].setRow(i);
        }
    }
}

void Grid::createBlock() {
	vector<Cell*> cells;

	switch (l->getNext()) { //need accessor
	case 'Z':
		cells.emplace_back(&gameBoard[2][5]);
		cells.emplace_back(&gameBoard[2][6]);
		cells.emplace_back(&gameBoard[3][6]);
		cells.emplace_back(&gameBoard[3][7]);
		break;
	case 'T':
		cells.emplace_back(&gameBoard[2][5]);
		cells.emplace_back(&gameBoard[2][6]);
		cells.emplace_back(&gameBoard[2][7]);
		cells.emplace_back(&gameBoard[3][6]);
		break;
	case 'O':
		cells.emplace_back(&gameBoard[2][5]);
		cells.emplace_back(&gameBoard[2][6]);
		cells.emplace_back(&gameBoard[3][5]);
		cells.emplace_back(&gameBoard[3][6]);
		break;
	case 'L':
		cells.emplace_back(&gameBoard[2][7]);
		cells.emplace_back(&gameBoard[3][5]);
		cells.emplace_back(&gameBoard[3][6]);
		cells.emplace_back(&gameBoard[3][7]);
		break;
	case 'S':
		cells.emplace_back(&gameBoard[2][6]);
		cells.emplace_back(&gameBoard[2][7]);
		cells.emplace_back(&gameBoard[3][5]);
		cells.emplace_back(&gameBoard[3][6]);
		break;
	case 'J':
		cells.emplace_back(&gameBoard[2][5]);
		cells.emplace_back(&gameBoard[3][5]);
		cells.emplace_back(&gameBoard[3][6]);
		cells.emplace_back(&gameBoard[3][7]);
		break;
	case 'I':
		cells.emplace_back(&gameBoard[3][5]);
		cells.emplace_back(&gameBoard[3][6]);
		cells.emplace_back(&gameBoard[3][7]);
		cells.emplace_back(&gameBoard[3][8]);
		break;
	}
	for (auto &i : cells) {
		i->setType(l->getNext());
	}

	blocks.emplace(blocks.begin(), new Block(cells, l->getNext(), l->getLevel(), l->getIsHeavy()));

	for (auto &i : cells) {
		i->setBlock(blocks[0]);
	}
	l->createBlock();
}


ostream &operator<<(ostream &out, const Grid &g) {
	for (auto &i : g.gameBoard) {
		cout << "|";
		for (auto &j : i) {
			out << j.getType();
		}
		cout << "|" << endl;
	}

	return out;
}
