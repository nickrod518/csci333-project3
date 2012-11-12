#include "AVL.h"

int main() {
  AVL<int>* avl = new AVL<int>();

  avl->insert(5);
  cout << "insert success";
  avl->insert(4);
  cout << "insert success";
  avl->insert(6);
  cout << "insert success";
  avl->insert(7);
  cout << "insert success";
  avl->insert(8);
  cout << "insert success";
  avl->print();

  /*
  avl->insert(4);
  avl->print();
  avl->insert(6);
  avl->print();
  avl->insert(5);
  avl->print();
  avl->insert(3);
  avl->print();
  avl->insert(2);
  avl->print();
  avl->insert(7);
  avl->print();
  avl->insert(12);
  avl->print();
  avl->insert(1);
  avl->print();
  */
}
