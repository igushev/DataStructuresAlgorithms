#include "BinaryHeap.h"

#include "../Utils/Int.h"

#include <iostream>
#include <stdlib.h>

int main(int argc, char** args)
{
  const unsigned count = 25;
  const unsigned max = 100;

  BinaryHeap<Int> binary_heap;
  std::cout << "Inserting:" << std::endl;
  for (int i = 0; i < count; ++i) {
    Int el = rand()%max;
    std::cout << el << ' ';
    binary_heap.Insert(el);
  }
  std::cout << std::endl;

  std::cout << "Max and poping max:" << std::endl;
  while (binary_heap.Count()) {
    Int max = binary_heap.Max();
    std::cout << "max: " << max << " count: " << binary_heap.Count();
    Int pop = binary_heap.PopMax();
    std::cout << " pop: " << pop << " count: " << binary_heap.Count() << std::endl;
    if (pop != max)
     std::cerr << "pop != max" << std::endl;
  }
  std::cout << std::endl;
}
