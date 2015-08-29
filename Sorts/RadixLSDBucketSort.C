#include "RadixLSDBucketSort.h"

#include "../Utils/Arrays.h"

int main(int argc, char** args)
{
  if (argc < 3) {
    std::cerr<<"Not enouht parameters"<<std::endl;
    exit(-1);
  }

  std::vector<int> v;
  read_binary_vector(v, args[1]);
  radix_LSD_bucket_sort(v);
  write_binary_vector(v, args[2]);
}
