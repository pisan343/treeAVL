#include "treeavl.h"
#include <cassert>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

// helper function to print vectors and vector of vectors
template <class T> ostream &operator<<(ostream &out, const vector<T> &v) {
  out << "[";
  if (v.size() > 0) {
    out << v[0];
    for (int i = 1; i < v.size(); i++) {
      out << "," << v[i];
    }
  }
  out << "]";
  return out;
}
ostream &operator<<(ostream &out, const Node *np) {
  return out << "[" << np->value << "]";
}

ostream &operator<<(ostream &out, const TreeAVL &tp) {
  //   return out << tp.to_string();
  printSideways(out, tp.root, 0);
  return out;
}

ostream &printSideways(ostream &out, const Node *curr, int level) {
  const static char SP = ' ';
  const static int ReadabilitySpaces = 4;
  if (!curr)
    return out;
  printSideways(out, curr->right, ++level);
  out << setfill(SP) << setw(level * ReadabilitySpaces) << SP;
  out << curr->value << endl;
  printSideways(out, curr->left, level);
  return out;
}

Node::Node(int value) : value{value}, height{1} {}

TreeAVL::~TreeAVL() {}

void TreeAVL::insert(int value) {
  if (root == nullptr) {
    root = new Node(value);
    return;
  }
  Node *curr = root;
  while (true) {
    if (value < curr->value) {
      if (curr->left == nullptr) {
        curr->left = new Node(value);
        curr->left->parent = curr;
        curr = curr->left;
        break;
      }
      curr = curr->left;
    } else if (value > curr->value) {
      if (curr->right == nullptr) {
        curr->right = new Node(value);
        curr->right->parent = curr;
        curr = curr->right;
        break;
      }
      curr = curr->right;
    } else {
      assert(value == curr->value);
      return; // no duplicates
    }
  }
  // update heights
  fixParentHeights(curr);
}

void TreeAVL::fixParentHeights(Node *curr) {
  while (curr->parent != nullptr) {
    Node *theParent = curr->parent;
    int leftHeight = height(theParent->left);
    int rightHeight = height(theParent->right);
    theParent->height = 1 + max(leftHeight, rightHeight);
    if (abs(leftHeight - rightHeight) > 1) {
      fixUnbalancedNode(theParent);
    }
    curr = theParent;
  }
}

bool TreeAVL::rightHeavy(Node *curr) {
  assert(curr != nullptr);
  return height(curr->right) - height(curr->left) > 0;
}

bool TreeAVL::leftHeavy(Node *curr) {
  assert(curr != nullptr);
  return height(curr->left) - height(curr->right) > 0;
}

int TreeAVL::height(Node *curr) const {
  return (curr == nullptr) ? 0 : curr->height;
}

void TreeAVL::rotateLeft(Node *curr) {
  int h = height(curr->left);
  Node *theParent = curr->parent;
  Node *rightChild = curr->right;
  Node *rightChildsLeftChild = curr->right->left;
  curr->right = rightChildsLeftChild;
  rightChild->left = curr;
  curr->parent = rightChild;
  if (rightChildsLeftChild != nullptr) {
    rightChildsLeftChild->parent = curr;
  }
  rightChild->parent = theParent;
  curr->height = h + 1;
  rightChild->height = h + 2;
  if (rightChildsLeftChild != nullptr) {
    rightChildsLeftChild->height = h;
  }
  if (theParent != nullptr) {
    if (theParent->left == curr) {
      theParent->left = rightChild;
    } else {
      assert(theParent->right == curr);
      theParent->right = rightChild;
    }
  }
}
void TreeAVL::rotateRight(Node *curr) {
  int h = height(curr->right);
  Node *theParent = curr->parent;
  Node *leftChild = curr->left;
  Node *leftChildsRightChild = curr->left->right;
  curr->left = leftChildsRightChild;
  leftChild->right = curr;
  curr->parent = leftChild;
  if (leftChildsRightChild != nullptr) {
    leftChildsRightChild->parent = curr;
  }
  leftChild->parent = theParent;
  curr->height = h + 1;
  leftChild->height = h + 2;
  if (leftChildsRightChild != nullptr) {
    leftChildsRightChild->height = h;
  }
  if (theParent != nullptr) {
    if (theParent->left == curr) {
      theParent->left = leftChild;
    } else {
      assert(theParent->right == curr);
      theParent->right = leftChild;
    }
  }
}

void TreeAVL::rotateLeftRight(Node *curr) {
  rotateLeft(curr->left);
  rotateRight(curr);
}

void TreeAVL::rotateRightLeft(Node *curr) {
  rotateRight(curr->right);
  rotateLeft(curr);
}

void TreeAVL::fixUnbalancedNode(Node *curr) {
  // right-right heavy
  if (rightHeavy(curr) && rightHeavy(curr->right)) {
    rotateLeft(curr);
  } else if (leftHeavy(curr) && leftHeavy(curr->left)) {
    rotateRight(curr);
  } else if (leftHeavy(curr) && rightHeavy(curr->left)) {
    rotateLeftRight(curr);
  } else {
    assert(rightHeavy(curr) && leftHeavy(curr->right));
    rotateRightLeft(curr);
  }
}

// do a level order traversal and convert the tree into a string
string TreeAVL::to_string() const {
  stringstream ss;
  vector<vector<int>> result;
  if (root == nullptr) {
    ss << result;
    return ss.str();
  }
  queue<Node *> q;
  q.push(root);
  while (!q.empty()) {
    vector<int> level;
    int n = q.size();
    for (int i = 0; i < n; i++) {
      Node *qt = q.front();
      q.pop();
      level.push_back(qt->value);
      if (qt->left != nullptr) {
        q.push(qt->left);
      }
      if (qt->right != nullptr) {
        q.push(qt->right);
      }
    }
    result.push_back(level);
  }
  ss << result;
  return ss.str();
}