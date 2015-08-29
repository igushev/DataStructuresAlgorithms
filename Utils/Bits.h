#ifndef BITS_H
#define BITS_H

#include <iostream>
#include <bitset>

typedef unsigned long uint32_t;

unsigned ones_count(uint32_t n)
{
  unsigned ones = 0;
  while (n) {
    ++ones;
    n &= n-1;
  }
  return ones;
}

uint32_t create_bits(std::string s)
{
  std::bitset<32> bits(s);
  return bits.to_ulong();
}

std::string print_bits(uint32_t n)
{
  std::bitset<32> bits(n);
  return bits.to_string();
}

#endif
