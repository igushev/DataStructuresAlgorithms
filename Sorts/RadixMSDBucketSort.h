#ifndef RADIX_MSD_BUCKET_SORT_H
#define RADIX_MSD_BUCKET_SORT_H

#include <vector>
#include <list>
#include <limits.h>
#include <math.h>

const int digits = 10;

void _radix_MSD_bucket_sort(std::vector<int>& v, std::vector<int>::iterator begin, std::vector<int>::iterator end, int shift)
{
  std::vector<std::list<int> > buckets(digits);

  for (std::vector<int>::iterator i_p = begin; i_p != end; ++i_p) {
    int bucket = (*i_p/shift)%digits;
    buckets[bucket].push_back(*i_p);
  }

  std::vector<int>::iterator i_p = begin;
  for (int bucket = 0; bucket < digits; ++bucket) {
    std::vector<int>::iterator inner_p = i_p;
    for (std::list<int>::iterator bi_p = buckets[bucket].begin(); bi_p != buckets[bucket].end(); *i_p++ = *bi_p++);
    if (shift != 1 && inner_p != i_p)
      _radix_MSD_bucket_sort(v, inner_p, i_p, shift/digits);
  }
}

void radix_MSD_bucket_sort(std::vector<int>& v)
{
  int shift = pow(digits, floor(log(INT_MAX)/log(digits)));
  _radix_MSD_bucket_sort(v, v.begin(), v.end(), shift);
}

#endif
