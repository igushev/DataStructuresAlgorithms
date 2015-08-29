#ifndef RADIX_LSD_BUCKET_SORT_H
#define RADIX_LSD_BUCKET_SORT_H

#include <vector>
#include <list>
#include <limits.h>
#include <math.h>

const int digits = 10;

void radix_LSD_bucket_sort(std::vector<int>& v)
{
  int shift = 1;
  for (int pos = 0; pos < ceil(log(INT_MAX)/log(digits)); ++pos) {
    std::vector<std::list<int> > buckets(digits);

    for (std::vector<int>::iterator i_p = v.begin(); i_p != v.end(); ++i_p) {
      int bucket = (*i_p/shift)%digits;
      buckets[bucket].push_back(*i_p);
    }

    std::vector<int>::iterator i_p = v.begin();
    for (int bucket = 0; bucket < digits; ++bucket)
      for (std::list<int>::iterator bi_p = buckets[bucket].begin(); bi_p != buckets[bucket].end(); *i_p++ = *bi_p++);

    shift *= digits;
  }
}

#endif
