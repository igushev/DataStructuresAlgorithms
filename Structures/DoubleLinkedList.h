/**
  \file DoubleLinkedList.h
  \author Eduard Igushev visit <www.igushev.com> e-mail: <first name at last name dot com>
  \brief Double Linked List C++ implementation

  This double linked list has STL-stype begin()-end() logic.

  Warranty and license
  The implementation is provided “as it is” with no warranty.
  Any private and commercial usage is allowed.
  Keeping the link to the source is required.
  Any feedback is welcomed :-)
*/

#ifndef DOUBLE_LINKED_LIST
#define DOUBLE_LINKED_LIST

#include <stdexcept>

template <class T>
class DoubleLinkedList {
  struct NodeBase;
  struct Node;

public:
  struct Iterator {
    void operator++() { _node = _node->next; }
    void operator--() { _node = _node->prev; }
    T& operator*() { return (static_cast<Node*>(_node))->data; }
    bool operator==(const Iterator& it) { return _node == it._node; }
    bool operator!=(const Iterator& it) { return !(*this == it); }
  private:
    Iterator(NodeBase* node) : _node(node) {}
    NodeBase* _node;
    friend class DoubleLinkedList<T>;
  };

  DoubleLinkedList() : head(&tail), _count(0) {}
  template <class In>
  DoubleLinkedList(In first, In last);
  ~DoubleLinkedList();

  Iterator Insert(const Iterator&, const T&);
  void Erase(const Iterator&);
  unsigned Count() const { return _count; }

  void PushFront(const T&);
  void PushBack(const T&);
  void PopFront();
  void PopBack();

  Iterator begin() { return Iterator(head); }
  Iterator end() { return Iterator(&tail); }

  void reverse();
  DoubleLinkedList<T>* make_copy();

private:
  struct NodeBase {
    NodeBase() : prev(0), next(0) {}
    NodeBase* prev;
    NodeBase* next;
  };

  struct Node : public NodeBase {
    Node(const T& value) : data(value) {}
    T data;
  };

  DoubleLinkedList(DoubleLinkedList<T>&);
  void operator=(DoubleLinkedList<T>&);

  NodeBase* head;
  NodeBase tail; //this is the element after the last one
  unsigned _count;
};

template <class T>
template <class In>
DoubleLinkedList<T>::DoubleLinkedList(In first, In last)
  : head(&tail), _count(0)
{
  while (first != last)
    PushBack(*first++);
}

template <class T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
  for (NodeBase* cur = head; cur != &tail;) {
    Node* del = static_cast<Node*>(cur);
    cur = cur->next;
    delete del;
  }
}

template <class T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::Insert(const Iterator& it, const T& value)
{
  NodeBase *new_node = new Node(value);

  new_node->prev = it._node->prev;
  if (new_node->prev)
    new_node->prev->next = new_node;

  new_node->next = it._node;
  if (new_node->next)
    new_node->next->prev = new_node;

  if (head == it._node)
    head = new_node;

  ++_count;
  return Iterator(new_node);
}

template <class T>
void DoubleLinkedList<T>::Erase(const Iterator& it)
{
  if (it._node == &tail)
    throw std::out_of_range("Erase");

  if (it._node->next)
    it._node->next->prev = it._node->prev;

  if (it._node->prev)
    it._node->prev->next = it._node->next;

  if (head == it._node)
    head = it._node->next;

  --_count;
  delete static_cast<Node*>(it._node);
}

template <class T>
void DoubleLinkedList<T>::PushFront(const T& value)
{
  NodeBase *new_node = new Node(value);
  new_node->next = head;
  head->prev = new_node;
  head = new_node;
  ++_count;
}

template <class T>
void DoubleLinkedList<T>::PushBack(const T& value)
{
  NodeBase *new_node = new Node(value);

  new_node->prev = tail.prev;
  if (new_node->prev)
    new_node->prev->next = new_node;

  new_node->next = &tail;
  tail.prev = new_node;

  if (head == &tail)
    head = new_node;

  ++_count;
}

template <class T>
void DoubleLinkedList<T>::PopFront()
{
  if (head == &tail)
    throw std::out_of_range("PopFront");

  head->next->prev = 0;

  NodeBase* del = head;

  head = head->next;

  --_count;
  delete static_cast<Node*>(del);
}

template <class T>
void DoubleLinkedList<T>::PopBack()
{
  if (head == &tail)
    throw std::out_of_range("PopBack");

  NodeBase* del = tail.prev;

  tail.prev = del->prev;

  if (del->prev)
    del->prev->next = &tail;

  if (head == del)
    head = &tail;

  --_count;
  delete static_cast<Node*>(del);
}

#endif
