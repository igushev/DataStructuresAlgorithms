#include "Arrays.h"
#include "Int.h"

int main(int argc, char** args)
{
  if (argc < 2) {
    std::cerr<<"No enouht parameters"<<std::endl;
    exit(-1);
  }

  std::vector<Int> v;
  read_binary_vector(v, args[1]);
  print_vector(v);
}
