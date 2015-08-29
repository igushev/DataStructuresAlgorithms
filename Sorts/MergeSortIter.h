#ifndef MERGE_SORT_ITER_H
#define MERGE_SORT_ITER_H

#include <vector>
#include <utility>

/**
  Mistakes:
  Forgot to check on boundary
  Forgot to copy from temp vector
*/

inline void _check(const unsigned& size, unsigned& i)
{
  if (i >= size)
    i = size;
}

template <class T>
void merge_sort_iterative(std::vector<T>& v)
{
  std::vector<T> v_temp(v.size());
  std::vector<T> *v_in = &v;
  std::vector<T> *v_out = &v_temp;
  
  unsigned block_size = 1;
  while (block_size < v.size()) {
    unsigned blocks_start = 0;
    while (blocks_start < v.size()) {

      unsigned cur1 = blocks_start;
      _check(v.size(), cur1);
      unsigned end1 = cur1+block_size;
      _check(v.size(), end1);
      unsigned cur2 = end1;
      _check(v.size(), cur2);
      unsigned end2 = cur2+block_size;
      _check(v.size(), end2);

      unsigned out = blocks_start;
      while (cur1 < end1 || cur2 < end2) {
        if ((cur1 < end1 && cur2 < end2 && (*v_in)[cur1] < (*v_in)[cur2]) || !(cur2 < end2)) {
          (*v_out)[out] = (*v_in)[cur1];
          ++cur1;
        }
        else {
          (*v_out)[out] = (*v_in)[cur2];
          ++cur2;
        }
        ++out;
      }

      blocks_start += block_size*2;
    }
    std::swap(v_in, v_out);

    block_size *= 2;
  }

  if (v_out == &v)
    std::copy(v_temp.begin(), v_temp.end(), v.begin());
}

#endif
