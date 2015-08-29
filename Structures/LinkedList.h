/**
  \file LinkedList.h
  \author Eduard Igushev visit <www.igushev.com> e-mail: <first name at last name dot com>
  \brief Linked List C++ implementation

  This linked list has STL-stype begin()-end() logic.
  Pay attention that all operations near the end of a list (PushBack, PopBack and Erasing the last one) are quite expensive.

  Warranty and license
  The implementation is provided “as it is” with no warranty.
  Any private and commercial usage is allowed.
  Keeping the link to the source is required.
  Any feedback is welcomed :-)
*/

#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdexcept>

template <class T>
class LinkedList {
  struct NodeBase;
  struct Node;

public:
  struct Iterator {
    void operator++() { _node = _node->next; }
    T& operator*() { return (static_cast<Node*>(_node))->data; }
    bool operator==(const Iterator& it) { return _node == it._node; }
    bool operator!=(const Iterator& it) { return !(*this == it); }
  private:
    Iterator(NodeBase* node) : _node(node) {}
    NodeBase* _node;
    friend class LinkedList<T>;
  };

  LinkedList() : head(&tail), _count(0) {}
  template <class In>
  LinkedList(In first, In last);
  ~LinkedList();

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
  LinkedList<T>* make_copy();
  Iterator kth_last_element(unsigned k);
  Iterator middle_element();
  void remove_dublicates_hash();
  void remove_dublicates_runner();
  void partition_assemble(const T& pivot);
  void partition_switch(const T& pivot);
  void make_loop(Iterator start_loop, Iterator end_loop);
  Iterator start_of_loop();
  bool if_palindrome_stack();
  bool if_palindrome_recursive();
  friend LinkedList<unsigned>* sum_little_endian(LinkedList<unsigned>& number1, LinkedList<unsigned>& number2);
  friend LinkedList<unsigned>* sum_big_endian(LinkedList<unsigned>& number1, LinkedList<unsigned>& number2);

private:
  struct NodeBase {
    NodeBase() : next(0) {}
    NodeBase* next;
  };

  struct Node : public NodeBase {
    Node(const T& value) : data(value) {}
    T data;
  };

  LinkedList(LinkedList<T>&);
  void operator=(LinkedList<T>&);

  NodeBase* _findPrev(NodeBase*);

  void _changeNodes(NodeBase* prev_node1, NodeBase* node1, NodeBase* prev_node2, NodeBase* node2);
  bool _if_palindrome_recursive(NodeBase* slow_runner, NodeBase* fast_runner, NodeBase* &check);

  NodeBase* head;
  NodeBase tail; //this is the element after the last one
  unsigned _count;
};

template <class T>
template <class In>
LinkedList<T>::LinkedList(In first, In last)
  : head(&tail), _count(0)
{
  while (first != last)
    PushBack(*first++);
}

template <class T>
LinkedList<T>::~LinkedList()
{
  for (NodeBase* cur = head; cur != &tail;) {
    Node* del = static_cast<Node*>(cur);
    cur = cur->next;
    delete del;
  }
}

template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::Insert(const Iterator& it, const T& value)
{
  NodeBase *new_node = 0;
  if (it._node != &tail) {
    //just copy current data to the new node and assing new data to the current node
    new_node = new Node(static_cast<Node*>(it._node)->data);
    new_node->next = it._node->next;
    it._node->next = new_node;
    static_cast<Node*>(it._node)->data = value;
    new_node = it._node;
  }
  else if (NodeBase *prev = _findPrev(it._node)) {
    //no the next node -> inserting the element before the tail
    new_node = new Node(value);
    prev->next = new_node;
    new_node->next = it._node;
  }
  else {
    //no the next node and no the previous node -> it's the first element in a list
    new_node = new Node(value);
    new_node->next = &tail;
    head = new_node;
  }

  ++_count;
  return Iterator(new_node);
}

template <class T>
void LinkedList<T>::Erase(const Iterator& it)
{
  if (it._node == &tail)
    throw std::out_of_range("Erase");

  NodeBase* del = 0;
  if (it._node->next != &tail) {
    //just copy data from the next node and delete the current node
    del = it._node->next;
    static_cast<Node*>(it._node)->data = static_cast<Node*>(del)->data;
    it._node->next = del->next;
  }
  else if (NodeBase *prev = _findPrev(it._node)) {
    //no the next node -> deleting element before the tail
    del = it._node;
    prev->next = it._node->next;
  }
  else {
    //no the next node and no the previous node -> it's the unique element in a list
    del = it._node;
    head = &tail;
  }

  --_count;
  delete static_cast<Node*>(del);
}

template <class T>
void LinkedList<T>::PushFront(const T& value)
{
  NodeBase *new_node = new Node(value);
  new_node->next = head;
  head = new_node;
  
  ++_count;
}

template <class T>
void LinkedList<T>::PushBack(const T& value)
{
  NodeBase *new_node = new Node(value);

  if (NodeBase *prev = _findPrev(&tail)) {
    prev->next = new_node;
    new_node->next = &tail;
  }
  else {  //it's the first element in a list
    new_node->next = &tail;
    head = new_node;
  }
  
  ++_count;
}

template <class T>
void LinkedList<T>::PopFront()
{
  if (head == &tail)
    throw std::out_of_range("PopFront");

  NodeBase* del = head;

  head = head->next;

  --_count;
  delete static_cast<Node*>(del);
}

template <class T>
void LinkedList<T>::PopBack()
{
  NodeBase *del = _findPrev(&tail);
  if (!del)
    throw std::out_of_range("PopBack");

  if (NodeBase* prev = _findPrev(del))
    prev->next = &tail;
  else  //it's the unique element in a list
    head = &tail;

  --_count;
  delete static_cast<Node*>(del);
}

template <class T>
typename LinkedList<T>::NodeBase* LinkedList<T>::_findPrev(NodeBase* node)
{
  if (node == head)
    return 0;
  NodeBase* result = head;
  while (result->next != node)
    result = result->next;
  return result;
}

#endif
