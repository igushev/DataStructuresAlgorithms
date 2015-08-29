#ifndef INT_H
#define INT_H

#include <iostream>

class Int {
  int _value;
  static unsigned _count;

public:
  static unsigned Count() { return _count; }

  Int() : _value(0) { ++_count; }
  Int(const int& value) : _value(value) { ++_count; }
  Int(const Int& value) : _value(value._value) { ++_count; }
  ~Int() { --_count; }

  bool operator< (const Int& value) const { return _value < value._value; }
  operator int() { return _value; }
  operator const int() const { return _value; }

  friend std::istream& operator>>(std::istream&, Int&);
  friend std::ostream& operator<<(std::ostream&, Int&);
};

std::istream& operator>>(std::istream& input_stream, Int& int_object)
{
  input_stream >> int_object._value;
  return input_stream;
}

std::ostream& operator<<(std::ostream& output_stream, Int& int_object)
{
  output_stream << int_object._value;
  return output_stream;
}

unsigned int_hash_func(const Int& value)
{
  return value;
}

/*static*/
unsigned Int::_count = 0;

#endif
