#include "LinkedList.h"

#include "../Utils/Int.h"
#include "../Utils/Print.h"

void PrintList(LinkedList<Int>& list)
{
  std::cout << "Count: " << list.Count() << "; Int count: " << Int::Count() << std::endl;
  Print(list);
}

int main(int argc, char** args)
{
  const unsigned count = 5;

  LinkedList<Int> list;
  std::cout << "Inserting elements at the begining:" << std::endl;
  for (unsigned i = 0; i < count; ++i) {
    list.Insert(list.begin(), i);
    PrintList(list);
  }
  std::cout << std::endl;

  std::cout << "Inserting elements at the end:" << std::endl;
  for (unsigned i = 0; i < count; ++i) {
    list.Insert(list.end(), i);
    PrintList(list);
  }
  std::cout << std::endl;

  std::cout << "Inserting elements at the middle:" << std::endl;
  LinkedList<Int>::Iterator it = list.begin();
  for (unsigned j = 0; j < count; ++j)
    ++it;
  for (unsigned i = 0; i < count; ++i) {
    it = list.Insert(it, i);
    PrintList(list);
  }
  std::cout << std::endl;

  std::cout << "Deleting elements:" << std::endl;
  for (unsigned i = 0; i < count*3; ++i) {
    list.Erase(list.begin());
    PrintList(list);
  }
  std::cout << std::endl;

  std::cout << "Pushing elements at the beggining:" << std::endl;
  for (int i = 0; i < count; ++i)
  {
    list.PushFront(i);
    PrintList(list);
  }
  std::cout << std::endl;

  std::cout << "Poping elements from the beginning:" << std::endl;
  for (int i = 0; i < count; ++i)
  {
    list.PopFront();
    PrintList(list);
  }
  std::cout << std::endl;

  std::cout << "Pushing elements at the end:" << std::endl;
  for (int i = 0; i < count; ++i)
  {
    list.PushBack(i);
    PrintList(list);
  }
  std::cout << std::endl;

  std::cout << "Poping elements from the end:" << std::endl;
  for (int i = 0; i < count; ++i)
  {
    list.PopBack();
    PrintList(list);
  }
  std::cout << std::endl;
}
