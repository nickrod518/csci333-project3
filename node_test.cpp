#include "Node.h"
#include <string>
#include <iostream>

using std::string;

int main() {
  Node<string>* ns = new Node<string>(string("hello world!"));
  Node<int>* ni = new Node<int>(5);
  Node<double>* nd = new Node<double>(3.1459);

  std::cout << ns->getValue()<< std::endl;
  std::cout << ni->getValue()<< std::endl;
  std::cout << nd->getValue()<< std::endl;

  std::cout << ns->getBalance()<< std::endl;
  std::cout << ni->getBalance()<< std::endl;
  std::cout << nd->getBalance()<< std::endl;

  ns->incBalance();
  ni->decBalance();
  nd->setBalance(2);

  std::cout << ns->getBalance()<< std::endl;
  std::cout << ni->getBalance()<< std::endl;
  std::cout << nd->getBalance()<< std::endl;

  return 0;
}
