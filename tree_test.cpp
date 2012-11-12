#include "AVL.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
  AVL<int>* avl = new AVL<int>();

  avl->insert(4);
  avl->insert(6);
  avl->insert(5);
  avl->insert(3);
  avl->insert(2);
  avl->insert(7);
  avl->insert(12);
  avl->insert(1);

  avl->print();
  cout << "-----" << endl;

  avl->remove(2);
  avl->remove(1);
  avl->remove(7);
  avl->remove(6);
  avl->remove(4);

  avl->print();
  cout << "-----" << endl;
}
