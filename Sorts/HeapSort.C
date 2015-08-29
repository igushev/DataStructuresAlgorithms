#include "HeapSort.h"

#include "../Utils/Arrays.h"
#include "../Utils/Int.h"

int main(int argc, char** args)
{
  if (argc < 3) {
    std::cerr<<"Not enouht parameters"<<std::endl;
    exit(-1);
  }

  std::vector<Int> v;
  read_binary_vector(v, args[1]);
  heap_sort(v);
  write_binary_vector(v, args[2]);
}
