/**
  \file HashTable.h
  \author Eduard Igushev visit <www.igushev.com> e-mail: <first name at last name dot com>
  \brief Hash Table C++ implementation

  This Hash Table implementation allows to configure how many elements would stored directly in the table and in each allocated page.
  During erasing the place is just marked as empty and will be used for the next added element (with same hash).

  Warranty and license
  The implementation is provided “as it is” with no warranty.
  Any private and commercial usage is allowed.
  Keeping the link to the source is required.
  Any feedback is welcomed :-)
*/

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <iostream>

template <class T, class HashFunc, unsigned table_page_size = 2, unsigned linked_page_size = 10>
class HashTable {
  class Node;
  class Page;

public:
  HashTable(unsigned size, const HashFunc& _hash_func);
  ~HashTable();

  bool Find(const T& value) const;
  void Insert(const T& value);
  void Erase(const T& value);
  unsigned Count() const { return _count; }

  void PrintTable() const;

private:

  class Node {
  public:
    Node()
      : _has_data(false) {}
    ~Node()
      { if (_has_data) EraseData(); }
    void PutData(const T& value)
      { new(_data) T(value); _has_data = true; }
    void EraseData()
      { (reinterpret_cast<T*>(_data))->~T(); _has_data = false; }
    bool HasData() const
      { return _has_data; }
    T& Data()
      { return *(reinterpret_cast<T*>(_data)); }
    const T& Data() const
      { return *(reinterpret_cast<const T*>(_data)); }

  private:
    char _data[sizeof(T)];
    bool _has_data;
  };

  struct Page {
    Page(unsigned page_size) : nodes(page_size), next_page(false) {}
    std::vector<Node> nodes;
    Page* next_page;
  };

  HashTable(HashTable<T, HashFunc, table_page_size, linked_page_size>&);
  void operator=(HashTable<T, HashFunc, table_page_size, linked_page_size>&);

  const Node* _find(const T& value) const;

  std::vector<Page> _table;
  HashFunc _hash_func;
  unsigned _count;
};

template <class T, class HashFunc, unsigned table_page_size, unsigned linked_page_size>
HashTable<T, HashFunc, table_page_size, linked_page_size>::HashTable(unsigned size, const HashFunc& hash_func)
  : _table(size, Page(table_page_size)), _hash_func(hash_func), _count(0)
{
}

template <class T, class HashFunc, unsigned table_page_size, unsigned linked_page_size>
HashTable<T, HashFunc, table_page_size, linked_page_size>::~HashTable()
{
  for (unsigned i = 0; i < _table.size(); ++i) {
    Page* page = _table[i].next_page;

    while (page) {
      Page* next_page = page->next_page;
      delete page;
      page = next_page;
    }
  }
}

template <class T, class HashFunc, unsigned table_page_size, unsigned linked_page_size>
bool HashTable<T, HashFunc, table_page_size, linked_page_size>::Find(const T& value) const
{
  if (_find(value))
    return true;
  else
    return false;
}

template <class T, class HashFunc, unsigned table_page_size, unsigned linked_page_size>
void HashTable<T, HashFunc, table_page_size, linked_page_size>::Insert(const T& value)
{
  if (_find(value))
    return;

  unsigned pos = _hash_func(value)%_table.size();
  Page* page = &_table[pos];

  while (true) {
    for (unsigned i = 0; i < page->nodes.size(); ++i)
      if (!page->nodes[i].HasData()) {
        page->nodes[i].PutData(value);
        ++_count;
        return;
      }

    if (!page->next_page)
      page->next_page = new Page(linked_page_size);

    page = page->next_page;
  }
}

template <class T, class HashFunc, unsigned table_page_size, unsigned linked_page_size>
void HashTable<T, HashFunc, table_page_size, linked_page_size>::Erase(const T& value)
{
  Node* node = const_cast<Node*>(_find(value));
  if (!node)
    return;

  node->EraseData();
  --_count;
}

template <class T, class HashFunc, unsigned table_page_size, unsigned linked_page_size>
const typename HashTable<T, HashFunc, table_page_size, linked_page_size>::Node*
  HashTable<T, HashFunc, table_page_size, linked_page_size>::_find(const T& value) const
{
  unsigned pos = _hash_func(value)%_table.size();
  const Page* page = &_table[pos];

  while (page) {
    for (unsigned i = 0; i < page->nodes.size(); ++i)
      if (page->nodes[i].HasData() && page->nodes[i].Data() == value)
        return &(page->nodes[i]);

    page = page->next_page;
  }

  return 0;
}

template <class T, class HashFunc, unsigned table_page_size, unsigned linked_page_size>
void HashTable<T, HashFunc, table_page_size, linked_page_size>::PrintTable() const
{
  for (unsigned i = 0; i < _table.size(); ++i) {
    std::cout << "Table position " << i << std::endl;
    const Page* page = &_table[i];

    while (page) {
      std::cout <<
        std::string(3, ' ') << ((page == &_table[i])?"Table page:":"Linked page:") << std::endl <<
        std::string(3, ' ');
      for (unsigned j = 0; j < page->nodes.size(); ++j)
        if (page->nodes[j].HasData())
          std::cout << page->nodes[j].Data() << ' ';
        else
          std::cout << "- ";
      std::cout << std::endl;

      page = page->next_page;
    }
  }
}
#endif


