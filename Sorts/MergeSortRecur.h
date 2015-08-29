#ifndef MERGE_SORT_RECUR_H
#define MERGE_SORT_RECUR_H

#include <vector>
#include <utility>

/**
  Mistakes:
  Used begin as pointer and forgot about it
*/

template <class T>
void _merge(std::vector<T>& v, unsigned begin, unsigned middle, unsigned end)
{
  unsigned cur1 = begin;
  unsigned end1 = middle;
  unsigned cur2 = middle;
  unsigned end2 = end;
  std::vector<T> v_temp(end-begin);
  unsigned out = 0;
  while (cur1 < end1 || cur2 < end2) {
    if ((cur1 < end1 && cur2 < end2 && v[cur1] < v[cur2]) || !(cur2 < end2)) {
      v_temp[out] = v[cur1];
      ++cur1;
    }
    else {
      v_temp[out] = v[cur2];
      ++cur2;
    }
    ++out;
  }
  std::copy(v_temp.begin(), v_temp.end(), v.begin()+begin);
}

template <class T>
void _merge_sort_recursive(std::vector<T>& v, unsigned begin, unsigned end)
{
  unsigned middle = (end-begin)/2+begin;
  if (middle - begin > 1)
    _merge_sort_recursive(v, begin, middle);
  if (end - middle > 1)
    _merge_sort_recursive(v, middle, end);
  _merge(v, begin, middle, end);
}

template <class T>
void merge_sort_recursive(std::vector<T>& v)
{
  _merge_sort_recursive(v, 0, v.size());
}

#endif
