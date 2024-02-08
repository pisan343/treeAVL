#include <iostream>

using namespace std;

class TreeAVL;

class Node {
  friend class TreeAVL;
  // print a Node*
  friend ostream &operator<<(ostream &out, const Node *np);
  friend ostream &printSideways(ostream &out, const Node *curr, int level);

private:
  int value;
  Node *left = nullptr;
  Node *right = nullptr;
  Node *parent = nullptr;
  int height = 0;

  Node(int value);
};

class TreeAVL {

  // print a TreeAVL object
  friend ostream &operator<<(ostream &out, const TreeAVL &tp);

private:
  Node *root = nullptr;

  void fixParentHeights(Node *curr);

  void fixUnbalancedNode(Node *curr);
  void rotateLeft(Node *curr);
  void rotateRight(Node *curr);
  void rotateLeftRight(Node *curr);
  void rotateRightLeft(Node *curr);

  bool rightHeavy(Node *curr);
  bool leftHeavy(Node *curr);
  int height(Node *curr) const;

public:
  // destructor
  ~TreeAVL();

  // insert a new value
  void insert(int value);

  // check if a value is in the tree
  bool contains(int value) const;

  // return the height of the tree
  int height() const;

  // return a string representation fo the tree useful for assert statements
  string to_string() const;
};