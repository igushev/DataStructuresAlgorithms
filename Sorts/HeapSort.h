#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <vector>
#include <utility>

/**
  Mistakes:
  Forgot to change left and right after changing top
  Condition i >= 0 for unsigned i which leads to infinite loop
*/

template<class T>
void _shift_down(std::vector<T>& v, unsigned top, unsigned size)
{
  unsigned left = 2*top+1;
  unsigned right = 2*top+2;
  while ((left < size && v[top] < v[left]) || (right < size && v[top] < v[right])) {
    if (right < size && v[left] < v[right]) {
      std::swap(v[top], v[right]);
      top = right;
    }
    else {
      std::swap(v[top], v[left]);
      top = left;
    }

    left = 2*top+1;
    right = 2*top+2;
  }
}

template <class T>
void heap_sort(std::vector<T>& v)
{
  unsigned size = v.size();
  //build the heap
  for (unsigned i = size/2; i != -1; --i)
    _shift_down(v, i, size);

  //sorting
  while (size > 1) {
    std::swap(v[0], v[size-1]);
    _shift_down(v, 0, size-1);
    --size;
  }
}

#endif
