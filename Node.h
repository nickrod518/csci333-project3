#ifndef __NODE_H__
#define __NODE_H__

template <typename T>
class Node {
 private:
  T value;
  int balance;
  Node<T>* leftChild;
  Node<T>* rightChild;

 public:
  Node<T>(T v);
  T getValue();

  int getBalance();
  void setBalance(int b);
  void decBalance();
  void incBalance();

  void clearChildren();

  Node<T>*& getLeftChild();
  void setLeftChild(Node<T>& n);

  Node<T>*& getRightChild();
  void setRightChild(Node<T>& n);
};

#endif
