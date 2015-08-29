#ifndef RADIX_MSD_COUNTING_SORT
#define RADIX_MSD_COUNTING_SORT

#include <vector>
#include <list>
#include <limits.h>
#include <math.h>

const int digits = 10;

void _radix_MSD_counting_sort(std::vector<int>& v, std::vector<int>::iterator begin, std::vector<int>::iterator end, int shift)
{
  std::vector<int> vtemp(end - begin);
  std::vector<std::vector<int>::size_type > positions(digits);
  std::vector<std::vector<int>::size_type > counts(digits);

  for (std::vector<int>::iterator i_p = begin; i_p != end; ++i_p) {
    int bucket = (*i_p/shift)%digits;
    ++counts[bucket];
  }

  int position = 0;
  for (int bucket = 0; bucket < digits; ++bucket) {
    positions[bucket] = position;
    position += counts[bucket];
  }

  for (std::vector<int>::iterator i_p = begin; i_p != end; ++i_p) {
    int bucket = (*i_p/shift)%digits;
    vtemp[positions[bucket]] = *i_p;
    ++positions[bucket];
  }

  std::vector<int>::iterator temp_p = vtemp.begin();
  for (std::vector<int>::iterator i_p = begin; i_p != end; *i_p++ = *temp_p++);

  if (shift != 1) {
    std::vector<int>::iterator inner_p = begin;
    for (int bucket = 0; bucket < digits; ++bucket) {
      if (counts[bucket])
        _radix_MSD_counting_sort(v, inner_p, inner_p+counts[bucket], shift/digits);
      inner_p += counts[bucket];
    }
  }
}

void radix_MSD_counting_sort(std::vector<int>& v)
{
  int shift = pow(digits, floor(log(INT_MAX)/log(digits)));
  _radix_MSD_counting_sort(v, v.begin(), v.end(), shift);
}

#endif
