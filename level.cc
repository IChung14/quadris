#include "level.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

Level::Level(string scriptfile, int startLevel) : lvl{startLevel}, random{true}, isHeavy{false}, scriptfile{scriptfile}, curblockIndex{0} {
    // read in scriptfile ie. level 0
    fstream file;
    file.open(scriptfile);
    while(!file.eof()){ // getting all contents in txt file into vector
        char c;
        file >> c;
        level0Seq.push_back(c);
    }
    // read in gamespecs
    int row = 0;
    int count = 0; // count how many integer read
    fstream f;
    f.open("gamespecs.txt");
    gameSpecs.push_back(vector <int>()); // first line
    while(true){
        int i;
        if(count < 8){ // finish reading a line
            f >> i;
            if(f.eof()) break;
            gameSpecs[row].push_back(i);
            count++;
        }
        else{ // otherwise make new row 
            count = 0;
            row++;
            gameSpecs.push_back(vector <int>());
        }
    }
    gameSpecs.pop_back();
    // initializing nextBlock
    if (lvl == 0) nextBlock = level0Seq[0];
    else createBlock();
    cout << nextBlock << "here" << endl;
}

Level::~Level(){} //??

void Level::nonRandom(string filename){
    random = false;
    fstream file;
    // read from file and putting contents in vector
    file.open(filename);
    while(!file.eof()){
        char c;
        file >> c;
        nonRandSeq.push_back(c);
    }
    curblockIndex = -1; // reinitialize to one less for createBlock
}

// could separate reading and creating to specialize
void Level::createBlock(){
    fstream file;
    if (!random){ // non-random
        curblockIndex++;
        // loop over file
        if(curblockIndex == int(nonRandSeq.size()-1)){
            curblockIndex = 0;
        }
        nextBlock = nonRandSeq[curblockIndex];
    }
    else if (lvl == 0){ // if level 0
       curblockIndex++;
        // loop over file
        if(curblockIndex == int(level0Seq.size()-1)){
            curblockIndex = 0;
        }
        nextBlock = level0Seq[curblockIndex];
    }
    else{ // random
            //print gameSpecs
        /*    for(int i=0; i<3; i++){
                for(int j=0; j<8; j++){
                    cout << gameSpecs[i][j] << " ";
                }
                cout << endl;}
          */  
        // using rand to generate block
        int den = gameSpecs[lvl-1][0]; // GCD
        int randomNum = rand() % den; // generate random num from range 0-(denominator-1)
        curblockIndex = 1;
        int cumsum = gameSpecs[lvl-1][curblockIndex]; // cummulative sum of numerator
        while (true){
            if (randomNum < cumsum){
                if (curblockIndex == 1) nextBlock = 'I';
                else if (curblockIndex == 2) nextBlock = 'J';
                else if (curblockIndex == 3) nextBlock = 'L';
                else if (curblockIndex == 4) nextBlock = 'O';
                else if (curblockIndex == 5) nextBlock = 'S';
                else if (curblockIndex == 6) nextBlock = 'Z';
                else if (curblockIndex == 7) nextBlock = 'T';
                else{ // error proofing, don't have to keep
                    cout << "Error here: " << curblockIndex << endl;
                }
                break;
            }
            else{
                curblockIndex++;
                cumsum = cumsum + gameSpecs[lvl-1][curblockIndex];
            }
        }
    }
}

void Level::levelDown(){
    if (lvl == 0){
        cerr << "Already at level 0. Don't have lower level." << endl;
    }
    else{
        lvl--;
    }
    // not heavy for levels not 3&4
    if (lvl < 3){
        isHeavy = false;
    }
}

void Level::levelUp(){
    if (lvl == int(gameSpecs.size())){
        cout << lvl << endl;
        cout << gameSpecs.size() << endl;
        cerr << "Already at highest level." << endl;
    }
    else{
        lvl++;
    }
    // enforcing heavy for level 3 & 4
    if (lvl == 3){
        isHeavy = true;
    }
}

void Level::setLevel(int level){
    lvl = level; 
    if(lvl == 3 || lvl == 4){ // set heavy
        isHeavy = true;
    }
}

char Level::getNext() const{
    return nextBlock;
}

int Level::getLevel() const{
    return lvl;
}

bool Level::getIsHeavy() const{
    return isHeavy;
}

void Level::setRandom(bool type){
    random = type;
}

void Level::printBlock() const{
    switch (nextBlock){
        case 'I':
            cout << "IIII" << endl;
            break;
        case 'J':
            cout << "J" << "\n" << "JJJ" << endl;
            break;
        case 'L':
            cout << "  L" << "\n" << "LLL" << endl;
            break;
        case 'O':
            cout << "OO" << "\n" << "OO" << endl;
            break;
        case 'S':
            cout << " SS" << "\n" << "SS" << endl;
            break;
        case 'Z':
            cout << "ZZ" << "\n" << " ZZ" << endl;
            break;
        case 'T':
            cout << "TTT" << "\n" << " T " << endl;
            break;
    }
}

std::ostream &operator<<(std::ostream &out, const Level & l){
    out << "-----------" << endl;
    out << "Next:" << endl;
    l.printBlock(); // print next block
    return out;
}
