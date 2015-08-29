#ifndef RADIX_LSD_COUNTING_SORT_H
#define RADIX_LSD_COUNTING_SORT_H

#include <vector>
#include <list>
#include <limits.h>
#include <math.h>

const int digits = 10;

void radix_LSD_counting_sort(std::vector<int>& v)
{
  int shift = 1;
  for (int pos = 0; pos < ceil(log(INT_MAX)/log(digits)); ++pos) {

    std::vector<int> vtemp(v.size());
    std::vector<std::vector<int>::size_type > positions(digits);
    std::vector<std::vector<int>::size_type > counts(digits);

    for (std::vector<int>::iterator i_p = v.begin(); i_p != v.end(); ++i_p) {
      int bucket = (*i_p/shift)%digits;
      ++counts[bucket];
    }

    int position = 0;
    for (int bucket = 0; bucket < digits; ++bucket) {
      positions[bucket] += position;
      position += counts[bucket];
    }

    for (std::vector<int>::iterator i_p = v.begin(); i_p != v.end(); ++i_p) {
      int bucket = (*i_p/shift)%digits;
      vtemp[positions[bucket]] = *i_p;
      ++positions[bucket];
    }

    v = vtemp;
    shift *= digits;
  }
}

#endif
