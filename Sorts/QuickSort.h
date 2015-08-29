#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <vector>
#include <utility>

/**
  Mistakes:
  Wrong increment during finding pivot, therefore one pivot was changed with bigger element
*/

template<class T>
unsigned _quick_sort_pivot(std::vector<T>& v, unsigned begin, unsigned end)
{
  unsigned pivot = begin;
  for (unsigned i = begin+1; i < end; ++i)
    if (v[i] < v[begin]) {
      ++pivot;
      std::swap(v[i], v[pivot]);
    }
  std::swap(v[pivot], v[begin]);
  return pivot;
}

template<class T>
void _quick_sort(std::vector<T>& v, unsigned begin, unsigned end)
{
  unsigned pivot = _quick_sort_pivot(v, begin, end);
  if (pivot - begin > 1)
    _quick_sort(v, begin, pivot);
  if (end - (pivot+1) > 1)
    _quick_sort(v, pivot+1, end);
}

template<class T>
void quick_sort(std::vector<T>& v)
{
  _quick_sort(v, 0, v.size());
}

#endif
