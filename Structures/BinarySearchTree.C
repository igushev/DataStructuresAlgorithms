#include "BinarySearchTree.h"

#include <algorithm>
#include "../Utils/Arrays.h"
#include "../Utils/Int.h"
#include "../Utils/Print.h"

#include <stdlib.h>

void PrintTree(BinarySearchTree<Int>& tree)
{
  std::cout << "Count: " << tree.Count() << "; Int count: " << Int::Count() << std::endl;
  std::cout << "Balanced: " << (tree.Balanced()?"yes":"no") << std::endl;
  Print(tree);
  PrintReverse(tree);
  tree.PrintTree();
  std::cout << std::endl;
}

struct Visitor {
  void visit(const Int& element) { std::cout << element << ' '; }
};

int main(int argc, char** args)
{
  if (argc < 2) {
    std::cerr << "Not enough parameters" << std::endl;
    return -1;
  }

  std::vector<int> v;
  read_binary_vector(v, args[1]);

  BinarySearchTree<Int> tree;//(v.begin(), v.end());
  std::cout << "After creating:" << std::endl;
  PrintTree(tree);

  int max = v[0];
  for (unsigned i = 0; i < v.size(); ++i) {
    if (max < v[i])
      max = v[i];

    std::cout << "Inserting: " << v[i] << std::endl;
    tree.Insert(v[i]);
    std::cout << "After inserting:" << std::endl;
    PrintTree(tree);
  }
  std::cout << std::endl << std::endl;

  Visitor visitor;

  std::cout << "Finding elements:" << std::endl;
  for (int i = 0; i <= max; ++i) {
    typename BinarySearchTree<Int>::Iterator it = tree.Find(i);
    if (it != tree.end())
      std::cout << *it << ' ';
  }
  std::cout << std::endl << std::endl;

  std::cout << "Depth First Traversal:" << std::endl;
  tree.DepthFirstTraversal(&visitor);
  std::cout << std::endl << std::endl;

  std::cout << "Breadth First Traversal:" << std::endl;
  tree.BreadthFirstTraversal(&visitor);
  std::cout << std::endl << std::endl;

  tree.Balance();
  std::cout << "After balancing:" << std::endl;
  PrintTree(tree);

  std::cout << "Finding elements:" << std::endl;
  for (int i = 0; i <= max; ++i) {
    typename BinarySearchTree<Int>::Iterator it = tree.Find(i);
    if (it != tree.end())
      std::cout << *it << ' ';
  }
  std::cout << std::endl << std::endl;

  std::cout << "Depth First Traversal:" << std::endl;
  tree.DepthFirstTraversal(&visitor);
  std::cout << std::endl << std::endl;

  std::cout << "Breadth First Traversal:" << std::endl;
  tree.BreadthFirstTraversal(&visitor);
  std::cout << std::endl << std::endl;

  typename BinarySearchTree<Int>::Iterator it = tree.begin();;
  int i = 0;
  while (tree.Count()) {
    it = tree.begin();
    std::cout << "Erasing: " << *it << std::endl;
    tree.Erase(it);
    std::cout << "After erasing:" << std::endl;
    PrintTree(tree);
    ++i;
  }
}
