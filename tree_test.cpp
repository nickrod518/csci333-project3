#include "AVL.h"

int main() {
  AVL<int>* avl1 = new AVL<int>();
  AVL<int>* avl2 = new AVL<int>();

  cout << "test 1" << endl;
  avl1->insert(5);
  avl1->insert(4);
  avl1->insert(6);
  avl1->insert(7);
  avl1->insert(8);
  avl1->print();
  cout << "------" << endl;

  cout << "test 2" << endl;
  avl2->insert(4);
  avl2->insert(6);
  avl2->insert(5);
  avl2->insert(3);
  avl2->insert(2);
  avl2->insert(7);
  avl2->insert(12);
  avl2->insert(1);
  avl2->print();
  cout << "------" << endl;
}
