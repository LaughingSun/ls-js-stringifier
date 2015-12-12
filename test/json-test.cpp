
#include <cstdlib>
#include <iostream>

#include "stringifier.hpp"

int
main ( int argc, char* argv[] ) {
  int stringified = Stringifier( argc - 1, &argv[1] );
  
  std::cout << "Nothing to do: " << argv[0] << std::endl;
  
  return 0;
}

