#ifndef __AVL_H__
#define __AVL_H__

#include "Node.h"
#include <string>
#include <vector>

using std::vector;

template <typename T>
class AVL {
 private:
  Node<T>* root;
  int getTreeDepth(Node<T>* n);
  int getBalance(Node<T>* n);
  void rotateLeft(Node<T>** parent);
  void rotateRight(Node<T>** parent);
  void preOrderTraversal(Node<T>* curr);
  void inOrderTraversal(Node<T>* curr);
  void postOrderTraversal(Node<T>* curr);

 public:
  AVL<T>();
  ~AVL<T>();

  bool find(T v);
  void remove(T v);
  void insert(T v);
  void print();
};

#endif
