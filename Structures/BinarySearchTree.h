/**
  \file BinarySearchTree.h
  \author Eduard Igushev visit <www.igushev.com> e-mail: <first name at last name dot com>
  \brief Binary Search Tree C++ implementation

  This tree has STL-stype begin()-end() logic and balancing method.

  Warranty and license
  The implementation is provided “as it is” with no warranty.
  Any private and commercial usage is allowed.
  Keeping the link to the source is required.
  Any feedback is welcomed :-)
*/

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <vector>
#include <queue>
#include <math.h>
#include <stack>
#include <iostream>
#include <cstdlib>

template <class T>
class BinarySearchTree {
  struct NodeBase;
  struct Node;

public:
  struct Iterator {
    void operator++();
    void operator--();
    const T& operator*() { return (static_cast<Node*>(_node))->data; }
    bool operator==(const Iterator& it) { return _node == it._node; }
    bool operator!=(const Iterator& it) { return !(*this == it); }
  private:
    Iterator(NodeBase* node) : _node(node) {}
    NodeBase* _node;
    friend class BinarySearchTree<T>;
  };

  BinarySearchTree() : _begin(&_tail), _root(0), _count(0) {}
  template <class In>
  BinarySearchTree(In first, In last);
  BinarySearchTree(BinarySearchTree<T>&);
  ~BinarySearchTree();

  void operator=(BinarySearchTree<T>& tree) { BinarySearchTree<T>(tree).Swap(*this); }
  void Swap(BinarySearchTree<T>&);

  Iterator Find(const T&) const;
  Iterator Insert(const T&);
  void Erase(const Iterator&);
  unsigned Count() const { return _count; }

  Iterator begin() const { return Iterator(_begin); }
  Iterator end() const { return Iterator(&_tail); }
  template <class Visitor>
  void DepthFirstTraversal(Visitor* visitor) const;
  template <class Visitor>
  void BreadthFirstTraversal(Visitor* visitor) const;

  bool Balanced() const;
  void Balance() { *this = *this; }
  void PrintTree() const;

  bool if_search_traversal() const;
  bool if_search_minmax() const;
  void create_level_lists() const;
  Iterator common_ancestor_recursive(Iterator, Iterator) const;
  Iterator common_ancestor_parent(Iterator, Iterator) const;
  bool if_subtree(const BinarySearchTree<T>&) const;
  void find_sum(int) const;

private:
  struct NodeBase {
    NodeBase() : parent(0), left(0), right(0) {}
    NodeBase *parent;
    NodeBase *left;
    NodeBase *right;
  };

  struct Node : public NodeBase {
    Node(const T& value) : data(value) {}
    T data;
  };

  template <class In>
  NodeBase* _construct(In first, In last);
  void _deleteTree(NodeBase*);
  NodeBase* _find(NodeBase*, const T&) const;
  NodeBase* _insert(NodeBase*, const T&);
  void _erase(NodeBase*);
  template <class Visitor>
  void _depthFirstTraversal(NodeBase*, Visitor*) const;
  bool _ifBalanced(NodeBase*, unsigned&) const;
  void _printTree(NodeBase*, int) const;
  void _attachTail() const;
  void _detachTail() const;
  static NodeBase* _min(NodeBase*);
  static NodeBase* _max(NodeBase*);

  struct CommonAncestorResult {
    CommonAncestorResult() : common(0), found1(false), found2(false) {}
    CommonAncestorResult(NodeBase* common_, bool found1_, bool found2_):
      common(common_), found1(found1_), found2(found2_) {}
    NodeBase* common;
    bool found1;
    bool found2;
  };

  bool _if_search_traversal(NodeBase*, NodeBase*&) const;
  bool _if_search_minmax(NodeBase*, NodeBase*, NodeBase*) const;
  void _create_level_lists(NodeBase*, unsigned) const;
  CommonAncestorResult _common_ancestor_recursive(NodeBase*, NodeBase*, NodeBase*) const;
  unsigned _node_level(NodeBase*) const;
  bool _if_subtree(NodeBase* node, NodeBase* root) const;
  static bool _if_identical(NodeBase*, NodeBase*);
  void _find_sum(NodeBase*, unsigned, int) const;
  void _check_sum(unsigned, int) const;
  unsigned _max_height(NodeBase*) const;

  NodeBase* _begin;
  NodeBase* _root;
  mutable NodeBase _tail;
  unsigned _count;
};

template <class T>
void BinarySearchTree<T>::Iterator::operator++()
{
  if (_node->right) {
    _node = BinarySearchTree<T>::_min(_node->right);
    return;
  }

  while (_node->parent->right == _node)
    _node = _node->parent;

  if (_node->parent->left == _node) {
    _node = _node->parent;
    return;
  }
}

template <class T>
void BinarySearchTree<T>::Iterator::operator--()
{
  if (_node->left) {
    _node = BinarySearchTree<T>::_max(_node->left);
    return;
  }

  while (_node->parent->left == _node)
    _node = _node->parent;

  if (_node->parent->right == _node) {
    _node = _node->parent;
    return;
  }
}

template <class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>& tree)
 : _begin(&_tail), _root(0), _count(0)
{
  std::vector<T> elements;
  elements.reserve(tree.Count());
  for (Iterator it = tree.begin(); it != tree.end(); ++it)
    elements.push_back(*it);

  if (elements.size()) {
    _root = _construct(elements.begin(), elements.end());
    _begin = _min(_root);
    _attachTail();
  }
}

template <class T>
template <class In>
BinarySearchTree<T>::BinarySearchTree(In first, In last)
 : _begin(&_tail), _root(0), _count(0)
{
  while (first != last)
    Insert(*first++);

  Balance();
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
  _detachTail();

  if (_root)
    _deleteTree(_root);
}

template <class T>
void BinarySearchTree<T>::Swap(BinarySearchTree<T>& tree)
{
  _detachTail();
  tree._detachTail();
  std::swap(_root, tree._root);
  std::swap(_begin, tree._begin);
  std::swap(_count, tree._count);
  _attachTail();
  tree._attachTail();
}

template <class T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::Find(const T& value) const
{
  _detachTail();

  NodeBase* node = 0;
  if (_root)
    node = _find(_root, value);

  _attachTail();
  if (node)
    return Iterator(node);
  else
    return Iterator(&_tail);
}

template <class T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::Insert(const T& value)
{
  _detachTail();

  NodeBase* node = 0;
  if (_root)
    node = _insert(_root, value);
  else {
    node = _root = _begin = new Node(value);
    ++_count;
  }

  _attachTail();
  return Iterator(node);
}

template <class T>
void BinarySearchTree<T>::Erase(const Iterator& it)
{
  _detachTail();

  _erase(it._node);

  _attachTail();
}

template <class T>
template <class Visitor>
void BinarySearchTree<T>::DepthFirstTraversal(Visitor* visitor) const
{
  if (!_root)
    return;

  _detachTail();

  _depthFirstTraversal(_root, visitor);

  _attachTail();
}

template <class T>
template <class Visitor>
void BinarySearchTree<T>::BreadthFirstTraversal(Visitor* visitor) const
{
  if (!_root)
    return;

  _detachTail();

  std::queue<NodeBase*> nodes;
  nodes.push(_root);

  while (nodes.size()) {
    NodeBase* node = nodes.front();
    nodes.pop();
    visitor->visit(static_cast<const T&>(static_cast<Node*>(node)->data));
    if (node->left)
      nodes.push(node->left);
    if (node->right)
      nodes.push(node->right);
  }

  _attachTail();
}

template <class T>
bool BinarySearchTree<T>::Balanced() const
{
  if (!_root)
    return true;

  _detachTail();

  unsigned max_height;
  bool balanced = _ifBalanced(_root, max_height);

  _attachTail();
  return balanced;
}

template <class T>
void BinarySearchTree<T>::PrintTree() const
{
  _detachTail();

  if (_root)
    _printTree(_root, 0);

  _attachTail();
}

template <class T>
template <class In>
typename BinarySearchTree<T>::NodeBase* BinarySearchTree<T>::_construct(In first, In last)
{
  In middle = (last - first)/2+first;

  NodeBase *node = new Node(*middle);
  ++_count;
  
  if (last - (middle+1) >= 1) {
    node->right = _construct(middle+1, last);
    node->right->parent = node;
  }
  if (middle - first >= 1) {
    node->left = _construct(first, middle);
    node->left->parent = node;
  }

  return node;
}

template <class T>
void BinarySearchTree<T>::_deleteTree(NodeBase* node)
{
  if (node->left)
    _deleteTree(node->left);
  if (node->right)
    _deleteTree(node->right);

  delete static_cast<Node*>(node);
}

template <class T>
typename BinarySearchTree<T>::NodeBase* BinarySearchTree<T>::_find(NodeBase* node, const T& value) const
{
  if (value < static_cast<Node*>(node)->data) {
    if (node->left)
      return _find(node->left, value);
    else
      return 0;
  }
  else if (static_cast<Node*>(node)->data < value) {
    if (node->right)
      return _find(node->right, value);
    else
      return 0;
  }
  else
    return node;
}

template <class T>
typename BinarySearchTree<T>::NodeBase* BinarySearchTree<T>::_insert(NodeBase* node, const T& value)
{
  if (value < static_cast<Node*>(node)->data) {
    if (node->left)
      return _insert(node->left, value);
    else {
      node->left = new Node(value);
      node->left->parent = node;
      if (node == _begin)
        _begin = node->left;
      ++_count;
      return node->left;
    }
  }
  else if (static_cast<Node*>(node)->data < value) {
    if (node->right)
      return _insert(node->right, value);
    else {
      node->right = new Node(value);
      node->right->parent = node;
      ++_count;
      return node->right;
    }
  }
  else
    return node;
}

template <class T>
void BinarySearchTree<T>::_erase(NodeBase* node)
{
  //the node has both children
  if (node->left && node->right) {
    //we should choose either min node in right subtree either max in left subtree
    NodeBase *right_min = _min(node->right);

    //detach right_min from its old place
    if (right_min->parent->right == right_min)
      right_min->parent->right = right_min->right;
    else
      right_min->parent->left = right_min->right;

    //right_min can have only right child
    if (right_min->right)
      right_min->right->parent = right_min->parent;

    //attach instead of the node being erased
    right_min->parent = node->parent;
    right_min->left = node->left;
    right_min->right = node->right;

    if (_root == node)
      _root = right_min;
  }
  //the node has left child only
  else if (node->left) {
    if (node->parent) {
      if (node->parent->right == node)
        node->parent->right = node->left;
      else
        node->parent->left = node->left;
    }
    else //_root == node
      _root = node->left;

    node->left->parent = node->parent;
  }
  //the node has right child only
  else if (node->right) {

    if (node->parent) {
      if (node->parent->right == node)
        node->parent->right = node->right;
      else
        node->parent->left = node->right;
    }
    else //_root == node
      _root = node->right;

    node->right->parent = node->parent;
  }
  //the node has no children
  else {
    if (node->parent) {
      if (node->parent->right == node)
        node->parent->right = 0;
      else
        node->parent->left = 0;
    }
    else { //_root == node
      _root = 0;
      _begin = &_tail;
    }
  }

  if (_begin == node) {
    if (node->right)
      _begin = _min(node->right);
    else
      _begin = node->parent;
  }

  --_count;
  delete static_cast<Node*>(node);
}

template <class T>
template <class Visitor>
void BinarySearchTree<T>::_depthFirstTraversal(NodeBase* node, Visitor* visitor) const
{
  if (node->left)
    _depthFirstTraversal(node->left, visitor);

  visitor->visit(static_cast<const T&>(static_cast<Node*>(node)->data));

  if (node->right)
    _depthFirstTraversal(node->right, visitor);
}

template <class T>
bool BinarySearchTree<T>::_ifBalanced(NodeBase* node, unsigned& max_height) const
{
  unsigned max_height_left = 0, max_height_right = 0;
  bool balanced_left = true, balanced_right = true;

  if (node->left)
    balanced_left = _ifBalanced(node->left, max_height_left);

  if (node->right)
    balanced_right = _ifBalanced(node->right, max_height_right);

  max_height = std::max(max_height_left, max_height_right)+1;

  return (balanced_left && balanced_right && (std::abs((int)max_height_left - (int)max_height_right) <= 1));
}

template <class T>
void BinarySearchTree<T>::_printTree(NodeBase* node, int depth) const
{
  if (node->right)
    _printTree(node->right, depth+1);
  std::cout << std::string(depth*3, ' ') << static_cast<Node*>(node)->data << std::endl;
  if (node->left)
    _printTree(node->left, depth+1);
}

template <class T>
void BinarySearchTree<T>::_attachTail() const
{
  if (_root) {
    NodeBase *max_node = max_node = _max(_root);
    max_node->right = &_tail;
    _tail.parent = max_node;
  }
}

template <class T>
void BinarySearchTree<T>::_detachTail() const
{
  if (_tail.parent) {
    _tail.parent->right = 0;
    _tail.parent = 0;
  }
}

template <class T>
typename BinarySearchTree<T>::NodeBase* BinarySearchTree<T>::_min(NodeBase* node)
{
  NodeBase* result = node;
  while (result->left)
    result = result->left;
  return result;
}

template <class T>
typename BinarySearchTree<T>::NodeBase* BinarySearchTree<T>::_max(NodeBase* node)
{
  NodeBase* result = node;
  while (result->right)
    result = result->right;
  return result;
}

#endif
