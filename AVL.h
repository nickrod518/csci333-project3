#ifndef __AVL_H__
#define __AVL_H__

#include "Node.h"
#include <string>
#include <vector>

template <typename T>
class AVL {
 private:
  Node<T>* root;
  int getTreeDepth(Node<T>* n);
  int getBalance(Node<T>* n);
  void leftRotate(Node<T>** parent);
  void rightRotate(Node<T>** parent);
  void inOrderTraversal(Node<T>* root);
  void postOrderTraversal(Node<T>* root);

 public:
  AVL<T>();
  ~AVL<T>();

  bool find(T v);
  void remove(T v);
  void insert(T v);
  void print();
};

#endif
