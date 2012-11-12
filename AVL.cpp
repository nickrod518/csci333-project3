#include "AVL.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::string;

template <typename T>
AVL<T>::AVL() {
  root = 0;
}

template <typename T>
AVL<T>::~AVL() {

}

template <typename T>
bool AVL<T>::find(T v) {
  Node<T>** curr = &root;

  while (*curr != 0) {
    if (v < (*curr)->getValue()) {
      curr = &((*curr)->getLeftChild());
    } else if (v > (*curr)->getValue()) {
      curr = &((*curr)->getRightChild());
    } else {
      return true;
    }
  }
  return false;
}

template <typename T>
void AVL<T>::insert(T v) {
  Node<T>* temp = new Node<T>(v);
  Node<T>** curr = &root;
  // keep track of suspect critical node's parent
  Node<T>** parent = 0;

  while (*curr != 0) {

    if (v < (*curr)->getValue()) {
      // if balance of -1 and inserting in left subtree...
      if ((*curr)->getBalance() < 0) {
        // ...store this parent
        parent = curr;
      }
      curr = &((*curr)->getLeftChild());

    } else if (v > (*curr)->getValue()) {
      // if balance of 1 and inserting in right subtree...
      if ((*curr)->getBalance() > 0) {
        // ...store this parent
        parent = curr;
      }
      curr = &((*curr)->getRightChild());
    }
  }
  *curr = temp;

  // there is a suspect node
  if (parent != 0) {

    if ((*parent)->getBalance() < -1) {
      // left right case
      if (((*parent)->getLeftChild())->getBalance() > 0) {
        rotateLeft(&((*parent)->getLeftChild()));
      }
      // left left case
      rotateRight(parent);

    } else if ((*parent)->getBalance() > 1) {
      // right left case
      if (((*parent)->getRightChild())->getBalance() < 0) {
        rotateLeft(&((*parent)->getRightChild()));
      }
      // right right case
      rotateLeft(parent);

    } else {
      // it was a false alarm
    }
  }
}

template <typename T>
void AVL<T>::remove(T v) {
  Node<T>** curr = &root;

  // find the node
  while (*curr != 0 && (*curr)->getValue() != v) {
    if (v < (*curr)->getValue()) {
      curr = &((*curr)->getLeftChild());
    } else if (v > (*curr)->getValue()) {
      curr = &((*curr)->getRightChild());
    }
  }

  // the node doesn't exist, so exit
  if ((*curr)->getValue() != v) {
    return;

  // remove node...
  } else {
    Node<T>* temp = *curr;

    // node is a leaf
    if ((*curr)->getLeftChild() == 0
        && (*curr)->getRightChild() == 0) {
      *curr = 0;
      delete temp;

    // node has one child
    } else if ((*curr)->getLeftChild() == 0
        || (*curr)->getRightChild() == 0) {
      if ((*curr)->getLeftChild() == 0) {
        *curr = (*curr)->getRightChild();
      } else {
        *curr = (*curr)->getLeftChild();
      }
      delete temp;

    // node has left and right child
    } else {

      // randomize removal method
      if (rand() % 2 == 1) {

        // in-order successor
        Node<T>* IOS = (*curr)->getRightChild();
        while (IOS->getLeftChild() != 0) {
          IOS = IOS->getLeftChild();
        }
        IOS->setLeftChild(*((temp)->getLeftChild()));
        *curr = IOS;
        delete temp;

      } else {
        // in-order predecessor
        Node<T>* IOP = (*curr)->getLeftChild();
        while (IOP->getRightChild() != 0) {
          IOP = IOP->getRightChild();
        }
        IOP->setRightChild(*((temp)->getRightChild()));
        *curr = IOP;
        delete temp;
      }
    }
  }
}

template <typename T>
void AVL<T>::print() {
  /*
  cout << "pre order traversal:" << endl;
  preOrderTraversal(root);

  cout << "in order traversal:" << endl;
  inOrderTraversal(root);
  */

  cout << "post order traversal:" << endl;
  postOrderTraversal(root);
}

template <typename T>
int AVL<T>::getTreeDepth(Node<T>* n) {
  if (n == 0) {
    return 0;
  } else {
    int leftDepth = getTreeDepth(n->getLeftChild());
    int rightDepth = getTreeDepth(n->getRightChild());
    
    if (leftDepth > rightDepth) {
      return leftDepth + 1;
    } else {
      return rightDepth + 1;
    }
  }
}

template <typename T>
int AVL<T>::getBalance(Node<T>* n) {
  if (n == 0) {
    return 0;
  } else {
    int leftDepth = getTreeDepth(n->getLeftChild());
    int rightDepth = getTreeDepth(n->getRightChild());

    return rightDepth - leftDepth;
  }
}

template <typename T>
void AVL<T>::rotateLeft(Node<T>** parent) {
  Node<T>* cn = *parent;
  Node<T>* temprc = cn->getRightChild();

  // update pointers
  if (temprc->getLeftChild() != 0) {
    Node<T>* templc = temprc->getLeftChild();
    cn->setRightChild(*templc);
  }
  temprc->setLeftChild(*cn);
  *parent = temprc;

  // update balances
  temprc->decBalance();
}

template <typename T>
void AVL<T>::rotateRight(Node<T>** parent) {
  Node<T>* cn = *parent;
  Node<T>* templc = cn->getLeftChild();

  // update pointers
  if (templc->getRightChild() != 0) {
    Node<T>* temprc = templc->getRightChild();
    cn->setLeftChild(*temprc);
  }
  templc->setRightChild(*cn);
  *parent = templc;

  // update balances
  templc->incBalance();
}

template <typename T>
void AVL<T>::preOrderTraversal(Node<T>* curr) {
  if (curr != 0) {
    std::cout << curr->getValue() << ", " << curr->getBalance() << std::endl;
    preOrderTraversal(curr->getLeftChild());
    preOrderTraversal(curr->getRightChild());
  }
}

template <typename T>
void AVL<T>::inOrderTraversal(Node<T>* curr) {
  if (curr != 0) {
    inOrderTraversal(curr->getLeftChild());
    std::cout << curr->getValue() << ", " << curr->getBalance() << std::endl;
    inOrderTraversal(curr->getRightChild());
  }
}

template <typename T>
void AVL<T>::postOrderTraversal(Node<T>* curr) {
  if (curr != 0) {
    postOrderTraversal(curr->getLeftChild());
    postOrderTraversal(curr->getRightChild());
    std::cout << curr->getValue() << ", " << curr->getBalance() << std::endl;
  }
}

template class AVL<int>;
template class AVL<double>;
template class AVL<string>;
