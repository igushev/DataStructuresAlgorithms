#include "Arrays.h"
#include "Int.h"

int main(int argc, char** args)
{
  if (argc < 2) {
    std::cerr<<"Not enouht parameters"<<std::endl;
    exit(-1);
  }

  unsigned size = argc - 2;
  std::vector<Int> v;
  v.reserve(size);
  for (unsigned i = 2; i < argc; ++i)
    v.push_back(atoi(args[i]));

  write_vector(v, args[1]);
}
