#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <cstdlib>

template <class T>
class matrix_t : public std::vector< std::vector<T> > {
public:
  typedef std::pair<unsigned, unsigned> sizes_t;
};

template <class T>
void generate_matrix(matrix_t<T>& matrix, const typename matrix_t<T>::sizes_t& sizes, unsigned max = 100)
{
  matrix.resize(sizes.first);
  for (unsigned i = 0; i < sizes.first; ++i) {
    matrix[i].resize(sizes.second);
    for (unsigned j = 0; j < sizes.second; ++j)
      matrix[i][j] = rand()%max;
  }
}

template <class T>
typename matrix_t<T>::sizes_t check_sizes(const matrix_t<T>& matrix)
{
  typename matrix_t<T>::sizes_t sizes(matrix.size(), 0);
  for (unsigned i = 0; i < sizes.first; ++i)
    if (!i)
      sizes.second = matrix[i].size();
    else if (matrix[i].size() != sizes.second)
      throw std::runtime_error("Wrong format");
  return sizes;
}

template <class T>
void print_matrix(const matrix_t<T>& matrix)
{
  typename matrix_t<T>::sizes_t sizes = check_sizes(matrix);
  for (unsigned j = 0; j < sizes.second; ++j) {
    for (unsigned i = 0; i < sizes.first; ++i) {
      std::cout.width(2);
      std::cout << matrix[i][j] << ' ';
    }
    std::cout << std::endl;
  }
}

#endif
