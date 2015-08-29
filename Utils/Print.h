#ifndef PRINT_H
#define PRINT_H

#include <iostream>

template <class Structure>
void Print(Structure& structure)
{
  for (typename Structure::Iterator it = structure.begin(); it != structure.end(); ++it)
    std::cout << *it << ' ';
  std::cout << std::endl;
}

template <class Structure>
void PrintReverse(Structure& structure)
{
  if (structure.begin() == structure.end())
    return;
    
  typename Structure::Iterator it = structure.end();
  do
  {
    --it;
    std::cout << *it << ' ';
  }
  while (it != structure.begin());
  std::cout << std::endl;
}

#endif
