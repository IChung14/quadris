#include "subject.h"
#include "observer.h"

Subject::~Subject(){}

void Subject::attach(Observer *o) {observers.emplace_back(o); }

void Subject::notifyObservers() {
  for(auto &ob : observers){
      if (ob != nullptr) ob->notify(*this);
  }
}

