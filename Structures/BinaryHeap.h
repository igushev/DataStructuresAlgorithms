/**
  \file BinaryHeap.h
  \author Eduard Igushev visit <www.igushev.com> e-mail: <first name at last name dot com>
  \brief Binary Heap C++ implementation

  Warranty and license
  The implementation is provided “as it is” with no warranty.
  Any private and commercial usage is allowed.
  Keeping the link to the source is required.
  Any feedback is welcomed :-)
*/

#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <vector>
#include <iterator>
#include <cmath>

template <class T>
class BinaryHeap {
  std::vector<T> _heap;

public:
  BinaryHeap() {}
  template <class In>
  BinaryHeap(In first, In last);
  ~BinaryHeap() {}

  void Insert(const T&);
  T PopMax();
  const T& Max() const { return _heap.front(); }
  unsigned Count() const { return _heap.size(); }

private:
  typedef typename std::vector<T>::size_type _heap_size_t;

  void _buildHeap();
  void _shiftDown(_heap_size_t node);
  void _shiftUp(_heap_size_t node);
};

template <class T>
template <class In>
BinaryHeap<T>::BinaryHeap(In first, In last)
{
  _heap_size_t n = std::distance(first, last);
  _heap.reserve(n);
  for (In in = first; in != last; ++in)
    _heap.push_back(*in);
  _buildHeap();
}

template <class T>
void BinaryHeap<T>::Insert(const T& value)
{
  _heap.push_back(value);
  _shiftUp(_heap.size()-1);
}

template <class T>
T BinaryHeap<T>::PopMax()
{
  T result = _heap.front();
  _heap.front() = _heap.back();
  _heap.pop_back();
  _shiftDown(0);
  return result;
}

template <class T>
void BinaryHeap<T>::_buildHeap()
{
  for (_heap_size_t i = _heap.size()/2; i >= 0; --i)
    _shiftDown(i);
}

template <class T>
void BinaryHeap<T>::_shiftDown(_heap_size_t node)
{
  _heap_size_t left_child = node*2+1;
  _heap_size_t right_child = node*2+2;

  _heap_size_t replace = node;
  if (right_child < _heap.size())
  {
    bool left = _heap[right_child] < _heap[left_child];
    if (left && _heap[node] < _heap[left_child])
      replace = left_child;
    else if (!left && _heap[node] < _heap[right_child])
      replace = right_child;
  }
  else if (left_child < _heap.size())
  {
    if (_heap[node] < _heap[left_child])
      replace = left_child;
  }

  if (replace == node)
    return;
  std::swap(_heap[node], _heap[replace]);
  _shiftDown(replace);
}

template <class T>
void BinaryHeap<T>::_shiftUp(_heap_size_t node)
{
  if (node == 0)
    return;

  _heap_size_t parent = std::floor((node-1)/2);

  if (_heap[node] < _heap[parent])
    return;
  std::swap(_heap[node], _heap[parent]);
  _shiftUp(parent);
}

#endif
