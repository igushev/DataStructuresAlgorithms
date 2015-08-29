#include "Arrays.h"
#include "Int.h"

int main(int argc, char** args)
{
  if (argc < 3) {
    std::cerr<<"Not enouht parameters"<<std::endl;
    exit(-1);
  }

  int size = atoi(args[2]);
  if (!size) {
    std::cerr<<"No size of array"<<std::endl;
    exit(-1);
  }

  std::vector<Int> v;
  generate_vector(v, size);
  write_binary_vector(v, args[1]);
}
