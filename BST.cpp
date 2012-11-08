#include "BST.h"
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::string;

template <typename T>
BST<T>::BST() {
  root = 0;
}

template <typename T>
BST<T>::~BST() {
  
}

template <typename T>
bool BST<T>::find(T v) {
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
void BST<T>::insert(T v) {
  Node<T>* temp = new Node<T>(v);
  Node<T>** curr = &root;

  while (*curr != 0) {
    if (v < (*curr)->getValue()) {
      curr = &((*curr)->getLeftChild());
    } else if (v > (*curr)->getValue()) {
      curr = &((*curr)->getRightChild());
    }
  }
  *curr = temp;
}

template <typename T>
void BST<T>::remove(T v) {
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

      // in-order successor
      Node<T>* IOS = (*curr)->getRightChild();
      while (IOS->getLeftChild() != 0) {
        IOS = IOS->getLeftChild();
      }
      IOS->setLeftChild(*((temp)->getLeftChild()));
      *curr = IOS;
      delete temp;

      /* in-order predecessor
      Node<T>* IOP = (*curr)->getLeftChild();
      while (IOP->getRightChild() != 0) {
        IOP = IOP->getRightChild();
      }
      IOP->setRightChild(*((temp)->getRightChild()));
      *curr = IOP;
      delete temp;
      */
    }
  }
}

template <typename T>
void BST<T>::print() {
  cout << "in order traversal:" << endl;
  inOrderTraversal(root);

  cout << "post order traversal:" << endl;
  postOrderTraversal(root);
}

template <typename T>
int BST<T>::getTreeDepth(Node<T>* n) {
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
void BST<T>::inOrderTraversal(Node<T>* root) {
  if(root != 0) {
    inOrderTraversal(root->getLeftChild());
    std::cout << root->getValue() << std::endl;
    inOrderTraversal(root->getRightChild());
  }
}

template <typename T>
void BST<T>::postOrderTraversal(Node<T>* root) {
  if(root != 0) {
    postOrderTraversal(root->getLeftChild());
    postOrderTraversal(root->getRightChild());
    std::cout << root->getValue() << std::endl;
  }
}

template class BST<int>;
template class BST<double>;
template class BST<string>;
