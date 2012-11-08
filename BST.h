#ifndef __BST_H__
#define __BST_H__

#include "Node.h"
#include <string>
#include <vector>

template <typename T>
class BST {
 private:
  Node<T>* root;
  int getTreeDepth(Node<T>* n);
  void traversalPrint(Node<T>* root);

 public:
  BST<T>();
  ~BST<T>();

  bool find(T v);
  void remove(T v);
  void insert(T v);
  void print();
};

#endif
