#ifndef RADIX_MSD_IN_PLACE_SORT_H
#define RADIX_MSD_IN_PLACE_SORT_H

#include <vector>
#include <list>
#include <limits.h>
#include <math.h>

const int digits = 10;

void _radix_MSD_in_place_sort(std::vector<int>& v, std::vector<int>::iterator begin, std::vector<int>::iterator end, int shift)
{
  std::vector<int>::size_type delta = begin - v.begin();
  std::vector<std::vector<int>::size_type > begins(digits);
  std::vector<std::vector<int>::size_type > positions(digits);
  std::vector<std::vector<int>::size_type > counts(digits);

  for (std::vector<int>::iterator i_p = begin; i_p != end; ++i_p) {
    int bucket = (*i_p/shift)%digits;
    ++counts[bucket];
  }

  int position = 0;
  for (int bucket = 0; bucket < digits; ++bucket) {
    begins[bucket] = position;
    positions[bucket] = position;
    position += counts[bucket];
  }

  for (std::vector<int>::iterator i_p = begin; i_p != end;) {
    int bucket = (*i_p/shift)%digits;
    if (!(i_p - begin >= begins[bucket] && i_p - begin < begins[bucket] + counts[bucket])) {
      int temp = *i_p;
      *i_p = v[positions[bucket]+delta];
      v[positions[bucket]+delta] = temp;
      ++positions[bucket];
    }
    else
      ++i_p;
  }

  if (shift != 1) {
    std::vector<int>::iterator inner_p = begin;
    for (int bucket = 0; bucket < digits; ++bucket) {
      if (counts[bucket])
        _radix_MSD_in_place_sort(v, inner_p, inner_p+counts[bucket], shift/digits);
      inner_p += counts[bucket];
    }
  }
}

void radix_MSD_in_place_sort(std::vector<int>& v)
{
  int shift = pow(digits, floor(log(INT_MAX)/log(digits)));
  _radix_MSD_in_place_sort(v, v.begin(), v.end(), shift);
}

#endif
