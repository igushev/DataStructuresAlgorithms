#include "HashTable.h"

#include "../Utils/Int.h"

#include <cstdlib>

typedef HashTable<Int, unsigned (*)(const Int& value)> hash_table_t;

void PrintTable(hash_table_t& hash_table)
{
  std::cout << "Count: " << hash_table.Count() << "; Int count: " << Int::Count() << std::endl;
  hash_table.PrintTable();
  std::cout << std::endl;
}

int main(int argc, char** args)
{
  const unsigned count = 15;
  const unsigned max = 100;

  hash_table_t hash_table(10, int_hash_func);

  std::cout << "Generating:" << std::endl;
  for (int i = 0; i < count; ++i) {
    Int el = rand()%max;
    std::cout << el << ' ';
    hash_table.Insert(el);
  }
  std::cout << std::endl << std::endl;

  std::cout << "After generating:" << std::endl;
  PrintTable(hash_table);

  std::cout << "Finding elements:" << std::endl;
  for (int i = 0; i < max; ++i) {
    if (hash_table.Find(i))
      std::cout << i << ' ';
  }
  std::cout << std::endl << std::endl;

  for (int i = 0; i < max; ++i)
    hash_table.Erase(i);

  std::cout << "After erasing:" << std::endl;
  PrintTable(hash_table);
}

