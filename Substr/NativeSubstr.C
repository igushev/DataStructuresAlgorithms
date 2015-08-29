#include "NativeSubstr.h"

#include <iostream>

int main(int argc, char** args)
{
  if (argc < 3) {
    std::cerr << "Not enouth parameters" << std::endl;
    return -1;
  }

  std::string text(args[1]);
  std::string pattern(args[2]);

  int result = native_substr( text, pattern );

  if (result == -1) {
    std::cout << "No entry" << std::endl;
  }
  else {
    std::cout << "Entry at position " << result << std::endl;
  }
}
