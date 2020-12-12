#include <iostream>
#include <utility>
#include <string>
#include "graphicdisplay.h"
#include "cell.h"
#include "window.h"
using namespace std;

GraphicDisplay::GraphicDisplay(int n): cellLen{n}  {}

void GraphicDisplay::notify(Subject &teller) {
  int color = Xwindow::Black;
  char type = static_cast<Cell&>(teller).getType();
  int row = static_cast<Cell&>(teller).getRow();
  int col = static_cast<Cell&>(teller).getCol();

  if(type == 'J') color = Xwindow::Red;
  else if(type == 'L') color = Xwindow::Green;
  else if(type == 'T') color = Xwindow::Blue;
  else if(type == 'S') color = Xwindow::Red;
  else if(type == 'Z') color = Xwindow::Green;
  else if(type == 'O') color = Xwindow::Blue;
  else if(type == ' ') color = Xwindow::White;

  x.fillRectangle(col*cellLen+12,row*cellLen+50,cellLen,cellLen,color);
}

void GraphicDisplay::printStatus(int lvl, int score, int highscore){
  string slvl ="Level:      " + to_string(lvl);
  string sscore = "Score:      " + to_string(score);
  string shighscore = "High Score: " + to_string(highscore);

  x.fillRectangle(90,0,20,45,Xwindow::White);
  x.drawString(25, 15, slvl);
  x.drawString(25, 25, sscore);
  x.drawString(25, 35, shighscore);
}

void GraphicDisplay::printNext(char type){  
  int color = Xwindow::Black;
  vector<pair<int,int>> shape;
  
  if(type == 'I'){ 
    color = Xwindow::Black;
    shape.emplace_back(pair<int,int>{0,0});
    shape.emplace_back(pair<int,int>{0,1});
    shape.emplace_back(pair<int,int>{0,2});
    shape.emplace_back(pair<int,int>{0,3});
  }else if(type == 'J'){
    color = Xwindow::Red;
    shape.emplace_back(pair<int,int>{0,0});
    shape.emplace_back(pair<int,int>{1,0});
    shape.emplace_back(pair<int,int>{1,1});
    shape.emplace_back(pair<int,int>{1,2});
  }else if(type == 'L'){ 
    color = Xwindow::Green;
    shape.emplace_back(pair<int,int>{0,2});
    shape.emplace_back(pair<int,int>{1,0});
    shape.emplace_back(pair<int,int>{1,1});
    shape.emplace_back(pair<int,int>{1,2});
  }else if(type == 'T'){ 
    color = Xwindow::Blue;
    shape.emplace_back(pair<int,int>{0,0});
    shape.emplace_back(pair<int,int>{0,1});
    shape.emplace_back(pair<int,int>{0,2});
    shape.emplace_back(pair<int,int>{1,1});
  }else if(type == 'S'){ 
    color = Xwindow::Red;
    shape.emplace_back(pair<int,int>{0,1});
    shape.emplace_back(pair<int,int>{0,2});
    shape.emplace_back(pair<int,int>{1,0});
    shape.emplace_back(pair<int,int>{1,1});
  }else if(type == 'Z'){ 
    color = Xwindow::Green;
    shape.emplace_back(pair<int,int>{0,0});
    shape.emplace_back(pair<int,int>{0,1});
    shape.emplace_back(pair<int,int>{1,1});
    shape.emplace_back(pair<int,int>{1,2});
  }else if(type == 'O'){ 
    color = Xwindow::Blue; 
    shape.emplace_back(pair<int,int>{0,0});
    shape.emplace_back(pair<int,int>{0,1});
    shape.emplace_back(pair<int,int>{1,0});
    shape.emplace_back(pair<int,int>{1,1});
  }

  x.drawString(25, 18*cellLen+65, "Next:");

  for(int i=0; i<2;i++){
    for(int j=0;j<4;j++){
      x.fillRectangle(j*cellLen+25,i*cellLen+cellLen*18+75,cellLen,cellLen,Xwindow::White);
    }
  }
  for(auto &i : shape){
    x.fillRectangle(i.second*cellLen+25,i.first*cellLen+cellLen*18+75,cellLen,cellLen,color);
  }
}

GraphicDisplay::~GraphicDisplay() {}

/*
SubscriptionType GraphicDisplay::subType() const {
  return SubscriptionType::All;
}

void GraphicDisplay::print(Xwindow &x) {
  for(int i=0;i<gridSize;i++){
    for(int j=0;j<gridSize;j++){
      if(theDisplay[i][j]){
        x.fillRectangle(j*cellLen,i*cellLen,cellLen,cellLen,Xwindow::White);
      }else{
        x.fillRectangle(j*cellLen,i*cellLen,cellLen,cellLen,Xwindow::Black);
      }
    }
  }
}*/
