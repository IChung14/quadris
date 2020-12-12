#include "control.h"
#include <vector>
using namespace std;

int main( int argc, char* argv[] ) {
  // set up
  vector<string> comdLinArgs;
  
  for (int i = 0; i < argc; i++) {
    comdLinArgs.emplace_back( argv[i] );
  }
  
  control( comdLinArgs );
  std::cout << "terminating" << std::endl;
}
