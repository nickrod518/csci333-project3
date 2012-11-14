#include "AVL.h"

int main() {
  AVL<int>* avl1 = new AVL<int>();
  AVL<int>* avl2 = new AVL<int>();
  AVL<int>* avl3 = new AVL<int>();
  AVL<int>* avl4 = new AVL<int>();
  AVL<int>* avl5 = new AVL<int>();

  cout << "right right case" << endl;
  avl1->insert(5);
  avl1->insert(6);
  avl1->insert(7);
  avl1->print();
  cout << "------" << endl;
  
  cout << "right left case" << endl;
  avl2->insert(5);
  avl2->insert(7);
  avl2->insert(6);
  avl2->print();
  cout << "------" << endl;

  cout << "left left case" << endl;
  avl3->insert(5);
  avl3->insert(3);
  avl3->insert(1);
  avl3->print();
  cout << "------" << endl;
  
  cout << "left right case" << endl;
  avl4->insert(5);
  avl4->insert(2);
  avl4->insert(3);
  avl4->print();
  cout << "------" << endl;

  cout << "larger tree case" << endl;
  avl5->insert(4);
  avl5->insert(6);
  avl5->insert(5);
  avl5->insert(3);
  avl5->insert(2);
  avl5->insert(7);
  avl5->insert(12);
  avl5->insert(1);
  avl5->insert(15);
  avl5->insert(17);
  avl5->insert(16);
  avl5->print();
  cout << "------" << endl;
}
