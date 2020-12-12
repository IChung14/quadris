#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"
#include "window.h"
class Cell;

class GraphicDisplay: public Observer {
  int cellLen;
  Xwindow x;
 public:
  GraphicDisplay(int n = 40);
  void printStatus(int lvl, int score, int highscore);
  void printNext(char type);
  void notify(Subject &teller) override;

  ~GraphicDisplay();

};

#endif
