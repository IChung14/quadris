#include <iostream>
#include <memory>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include "control.h"
using namespace std;

// forward declaration
static void fromFile(string fileName, vector<string>& commandList, Game& thisGame, bool* restartPtr);


// convertStringInt(num)
//  converts a string to an int
static int convertStringInt(string num) {
  int numValue;
  istringstream ss(num);
  ss >> numValue;
  return numValue;
}


// commandString(comd, commandList)
//  turns the input into a valid command (aka command from the commandlist)
//   returns a vector of one element (if single match found)
//    else returns an empty vector 
static vector<string> commandString(string comd, vector<string> commandList) {
  // set up
  vector<string> reducedList;  // stores the vector we will return
  unsigned int comdLen = comd.length();
  string command;
  
  // remove string that are not long enough
  for (unsigned int i = 0; i < commandList.size(); i++) {  
    // only emplace strings that are long enough
    if ( comdLen <= commandList[i].length() ) {
      reducedList.emplace_back( commandList[i] );
    }
  }


  // start removing non-matching commands from commandList
  for (unsigned int i = 0; i < comdLen; i++) {
    vector<string> tempList;

    // remove all commands that don't have the same ith character
    for (unsigned int j = 0; j < reducedList.size(); j++) {
      string temp = reducedList[j];

      if ( comd[i] == temp[i] ) {  // ith characters match
        tempList.emplace_back( temp );
      }
    }
    reducedList = tempList;
  }

  return reducedList;
}


// interpret(input)
//  takes the input and interprets what command it represents
//  excluding prefix input must match all first n letters 
//    of command it represents
//  input must not be ambiguous
//  otherwise return empty vector
static vector<string> interpret (string input, vector<string>& commandList) {      // incomplete
  // set up
  vector<string> commands;
  int inputLen = input.length();
  ostringstream prefixPart; // part of the string that contains the prefix
  ostringstream comdPart;   // part of the string that conatins the command

  int prefix;   // the prefix
  vector<string> comd;  // the command

  // split input string in prefix part and command part 
  int n = 0;
 
  for (int i = 0; i < inputLen; i++) { // grab prefix part
    // grab prefix
    if ((input[i] >= '0') && (input[i] <= '9')) {
      prefixPart << input[i];
    // reached first non-number
    } else {
      n = i;
      break;
    }
  }

  for (int i = n; i < inputLen; i++) { // grab command part
    comdPart << input[i];
  }


  // get prefix and comd
  comd = commandString( comdPart.str(), commandList ); 

  // valid command
  if ( comd.size() == 1 ) {  // filter out ambiguous or no-existant commands
    if ( prefixPart.str() == "" ) { // no prefix
      prefix = 1;
    } else {
      prefix = convertStringInt( prefixPart.str() );
    }

    // fill commands
    for (int i = 0; i < prefix; i++) {
      commands.emplace_back(comd[0]);
    }

  // ambiguous command (input could represent multiple commands)
  } else if ( comd.size() == 1 ) {
    cout << "Input is ambiguous" << endl;
      
  // command does not exist
  } else {
    cout << "Not valid command" << endl;
  }

  return commands;
}


// interpExec(input) 
//  calls the interpret to interpret the user's input
//  then passes the interpreted commands to Game using game's callFunction
//  or if the command is sequence
//    read in a file name and pass the file name to from file
static void interpExec(string input, vector<string>& commandList, Game& thisGame, bool* restartPtr) {
  // interpret command
  vector<string> commands;
  commands = interpret(input, commandList);

  // executes commands
  for (unsigned int i = 0; i < commands.size(); i++) {
    // command is restart
    if (commands[i] == "restart") {
      *restartPtr = true;
 
    // command is sequence
    } else if (commands[i] == "sequence") {
      string fileName;
      cin >> fileName;
      fromFile(fileName, commandList, thisGame, restartPtr);

    // command is not sequence
    } else {
      // cout << "command: " << commands[i] << endl;
      thisGame.callFunction(commands[i]);
    }
  }
}


// fromFile(file)
//  takes input from given file
// note: infinite loop if file calls itself
static void fromFile(string fileName, vector<string>& commandList, Game& thisGame, bool* restartPtr) {
  // open file
  ifstream file(fileName);

  // file failed to open
  if (file.fail()) {
    cerr << "file failed to open" << endl;
  }

  // read input from file
  string fileInput;

  while (file >> fileInput) {
    // interpret and execute command
    interpExec(fileInput, commandList, thisGame, restartPtr);
  } 
 
  file.close();
}



void control( vector<string>& comdLinArgs ) {
  // retrieve list of valid commands
  string comdMenu = "command.txt";   // text file containing list of commands
  vector<string> commandList;  // list of all valid commands
  string command;
  ifstream menu( comdMenu );

  while (menu >> command) {
    commandList.emplace_back( command );
  }


  // game loop
  bool continueGame = true;

  while ( continueGame == true ) {
    // restart loop
    bool restart = false;

    while ( restart == false ) {
      // create Game
      string defaultScript = "sequence.txt";
      bool defaultGraph = true;
      int defaultStart = 0;
      
      for (unsigned int i = 0; i < comdLinArgs.size(); i++) {
         // seed
         if ( comdLinArgs[i] == "-seed" ) {
           int seed;
           i++;
           seed = convertStringInt( comdLinArgs[i] );
           srand( seed );
           
         // scriptfile  
         } else if ( comdLinArgs[i] == "-scriptfile" ) {
           i++;
           defaultScript = comdLinArgs[i];
           
         // graph
         } else if ( comdLinArgs[i] == "-text" ) {
           defaultGraph = false;
         
         // level
         } else if ( comdLinArgs[i] == "-startlevel" ) {
           i++;
           defaultStart = convertStringInt( comdLinArgs[i] ); 
         }
      }
      
      Game thisGame(defaultScript, defaultGraph, defaultStart);       // create game
 
 
      // command loop
      string input;
  
      while ((restart == false) && (cin >> input)) {
        // interpret and execute command
        interpExec(input, commandList,  thisGame, &restart);
      }
    
      // exit condition
      if (cin.eof()) {
        continueGame = false;
        restart = true;
      }
    }
  }
}
