#ifndef ARRAYS_H
#define ARRAYS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

template <class T>
void read_vector(std::vector<T>& v, const char* fname)
{
  unsigned size;
  std::ifstream finput(fname, std::ios::in);
  finput >> size;
  v.resize(size);
  for (unsigned i = 0; i < size; ++i)
    finput >> v[i];
  finput.close();
}

template <class T>
void write_vector(std::vector<T>& v, const char* fname)
{
  unsigned size = v.size();
  std::ofstream foutput(fname, std::ios::out);
  foutput << size << std::endl;
  for (unsigned i = 0; i < size; ++i)
    foutput << v[i] << std::endl;
  foutput.close();
}

template <class T>
void read_binary_vector(std::vector<T>& v, const char* fname)
{
  unsigned size;
  std::ifstream finput(fname, std::ios::binary | std::ios::in);
  finput.read((char*)&size, sizeof(T));
  v.resize(size);
  finput.read((char*)&(v[0]), sizeof(T)*size);
  finput.close();
}

template <class T>
void write_binary_vector(std::vector<T>& v, const char* fname)
{
  unsigned size = v.size();
  std::ofstream foutput(fname, std::ios::binary | std::ios::out);
  foutput.write((char*)&size, sizeof(T));
  foutput.write((char*)&(v[0]), sizeof(T)*size);
  foutput.close();
}

template <class T>
void generate_vector(std::vector<T>& v, unsigned size, unsigned max = 100)
{
  v.resize(size);
  for (unsigned i = 0; i < size; ++i)
    v[i] = rand()%max;
}

template <class T>
void print_vector(std::vector<T>& v)
{
  for (unsigned i = 0; i < v.size(); ++i)
    std::cout<<i<<" - "<<v[i]<<std::endl;
}

#endif
