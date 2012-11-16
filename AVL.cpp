#include "AVL.h"
#include <sstream>
#include <stdlib.h>

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
  // keep track of pointer to suspect critical node
  Node<T>** parent = 0;
  // keep track of previous node
  Node<T>* prev = 0;

  // find where to put the node
  while (*curr != 0) {
    prev = *curr;

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
  // insert the node
  *curr = temp;

  // update balance on new node's parent
  if (prev != 0) {
    if (v < prev->getValue())
      prev->decBalance();
    else
      prev->incBalance();
  }

  // check if suspect node is critical
  if (parent != 0 && v < (*parent)->getValue()) {
    // left right case
    if ((*parent)->getLeftChild()->getBalance() > 0) {
      rotateLeft(&((*parent)->getLeftChild()));
      rotateRight(parent);
    // left left case
    } else {
      rotateRight(parent);
    }

  // check if suspect node is critical
  } else if (parent != 0 && v > (*parent)->getValue()) {
    // right left case
    if ((*parent)->getRightChild()->getBalance() > 0) {
      rotateRight(&((*parent)->getRightChild()));
      rotateLeft(parent);
    // right right case
    } else {
      rotateLeft(parent);
    }

  // there are no critical nodes so adjust balances
  } else {
    curr = &root;
    while ((*curr)->getValue() != v) {
      // set balance
      (*curr)->setBalance(getBalance(*curr));
      if (v < (*curr)->getValue()) {
        curr = &((*curr)->getLeftChild());
      } else if (v > (*curr)->getValue()) {
        curr = &((*curr)->getRightChild());
      }
    }
  }
}

template <typename T>
void AVL<T>::remove(T v) {
  Node<T>** curr = &root;
  // store path
  Node<T>** parent;
  vector< Node<T>** > path;

  // find the node
  while (*curr != 0 && (*curr)->getValue() != v) {
    // store visited nodes
    parent = curr;
    path.push_back(parent);

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

    // node has one child
    } else if ((*curr)->getLeftChild() == 0
        || (*curr)->getRightChild() == 0) {
      if ((*curr)->getLeftChild() == 0) {
        *curr = (*curr)->getRightChild();
      } else {
        *curr = (*curr)->getLeftChild();
      }

    // node has left and right child
    } else {

      Node<T>* ioParent = *curr;

      // randomize removal method
      if (rand() % 2 == 1) {

        // in-order successor
        Node<T>* ios = (*curr)->getRightChild();
        while (ios->getLeftChild() != 0) {
          ios = ios->getLeftChild();
        }
        ios->setLeftChild(*((temp)->getLeftChild()));
        *curr = ios;

        // update balances
        ioParent->setBalance(getBalance(ioParent));
        ios->setBalance(getBalance(ios));

      } else {
        // in-order predecessor
        Node<T>* iop = (*curr)->getLeftChild();
        while (iop->getRightChild() != 0) {
          iop = iop->getRightChild();
        }
        iop->setRightChild(*((temp)->getRightChild()));
        *curr = iop;

        // update balances
        ioParent->setBalance(getBalance(ioParent));
        iop->setBalance(getBalance(iop));
      }
    }
    delete temp;

    // check path for balance and rotate as necessary
    while (!path.empty()) {
      parent = path.back();
      path.pop_back();

      // check if node is critical
      if (parent != 0 && v < (*parent)->getValue()) {
        // left right case
        if (getBalance((*parent)->getLeftChild()) > 0) {
          rotateLeft(&((*parent)->getLeftChild()));
          rotateRight(parent);
        // left left case
        } else {
          rotateRight(parent);
        }

      // check if node is critical
      } else if (parent != 0 && v > (*parent)->getValue()) {
        // right left case
        if (getBalance((*parent)->getRightChild()) < 0) {
          rotateRight(&((*parent)->getRightChild()));
          rotateLeft(parent);
        // right right case
        } else {
          rotateLeft(parent);
        }

      // node is not critical, so adjust its balance
      } else {
          (*parent)->setBalance(getBalance(*parent));
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
int AVL<T>::getDepth(Node<T>* n) {
  if (n == 0) {
    return 0;
  } else {
    int leftDepth = getDepth(n->getLeftChild());
    int rightDepth = getDepth(n->getRightChild());
    
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
    int leftDepth = getDepth(n->getLeftChild());
    int rightDepth = getDepth(n->getRightChild());

    return rightDepth - leftDepth;
  }
}

template <typename T>
void AVL<T>::rotateLeft(Node<T>** parent) {
  cout << "left rotation" << endl;
  Node<T>* cn = *parent;
  Node<T>* temprc = cn->getRightChild();

  // update pointers
  if (temprc->getLeftChild() != 0) {
    Node<T>* templc = temprc->getLeftChild();
    cn->setRightChild(*templc);
    temprc->setLeftChild(*cn);
    *parent = temprc;
  } else {
    temprc->setLeftChild(*cn);
    *parent = temprc;
    cn->clearChildren();
  }

  // update balances
  temprc->setBalance(0);
  cn->decBalance();
}

template <typename T>
void AVL<T>::rotateRight(Node<T>** parent) {
  cout << "right rotation" << endl;
  Node<T>* cn = *parent;
  Node<T>* templc = cn->getLeftChild();

  // update pointers
  if (templc->getRightChild() != 0) {
    Node<T>* temprc = templc->getRightChild();
    cn->setLeftChild(*temprc);
    templc->setRightChild(*cn);
    *parent = templc;
  } else {
    templc->setRightChild(*cn);
    *parent = templc;
    cn->clearChildren();
  }

  // update balances
  templc->setBalance(0);
  cn->incBalance();
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
