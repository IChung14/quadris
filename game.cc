#include "game.h"
#include <string>
#include <iostream>

#include "graphicdisplay.h"

using namespace std;

int Game::highScore = 0;

Game::Game(string scriptfile, bool graphOn, int startLevel) : graph{graphOn?new GraphicDisplay():nullptr}, board{this->graph}, score{0}, l{scriptfile, startLevel},graphOn{graphOn} { // switch for graphOn
    isLost = false;
    board.assignGame(this);
    board.assignLevel(&l);
    board.createBlock();
    
    if(graphOn){
        graph->printStatus(l.getLevel(),score,highScore);
        graph->printNext(l.getNext());
    }
    cout << *this << endl;
}

Game::~Game(){} // what to do here

void Game::callFunction(string name){
    if (!isLost){
        if (name == "left" || name == "right" || name == "down" || name == "clockwise" || name == "counterclockwise" || name == "drop"){
            // check if move successful
            if(board.move(name) == false){
                lost(); // lost game
            }
            else{
                cout << *this;
            }
        }
        else if (name == "levelup"){
            l.levelUp();
            cout << *this;
        }
        else if (name == "leveldown"){
            l.levelDown();
            cout << *this;
        }
        else if (name == "norandom"){
            if (l.getLevel() > 2){
                string file;
                cin >> file; // takes in file name
                cout << "Set to norandom generation" << endl;
                l.nonRandom(file);
            }
            else{
                cout << "Can only use nonrandom command at level 3 and 4" << endl;
            }
        }
        else if (name == "random"){
            cout << "Set back to random generation" << endl;
            l.setRandom(true);
        }
        /* else if (name == "hint"){
           board.hint();
           }*/
        else if (name.length() == 1){ // creating each block for testing
            board.setBlock(name);
            cout << *this;
        }
        else{
            cerr << "Incorrect command" << endl;
        }
        if (!isLost){
	    cout << *this; // prints if game not lost

            if (graph != nullptr){
                graph->printStatus(l.getLevel(),score,highScore);
                graph->printNext(l.getNext());
            }
	}
    }
}

void Game::lost(){
    isLost = true;
    cout << "========================================================" << endl;
    cout << "Game lost" << endl;
    cout << "Your score: " << score << endl;
    // update highscore
    if (score > highScore){
        highScore = score;
        cout << "New Highscore!!!" << endl;
    }
    cout << "Restart the game by entering restart or Ctrl+D to exit" << endl;
    cout << "========================================================" << endl;
}

void Game::scoreLine(int num){
    int earned;
    earned = (l.getLevel() + num) * (l.getLevel() + num);
    score = score + earned;
}

void Game::scoreBlock(int blockLvl){
    int earned;
    earned = (blockLvl + 1) * (blockLvl + 1);
    score = score + earned;
}

ostream &operator<<(ostream &out, const Game &g){
    // print out status bar

    out << "Level:     " << g.l.getLevel() << endl; 
    out << "Score:     " << g.score << endl;
    out << "Hi Score:  " << g.highScore << endl; 
    out << "-----------" << endl;
    // print out game borad
    out << g.board;
    // print out next block
    out << g.l;
    return out;
}
