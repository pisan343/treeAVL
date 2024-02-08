#include "treeavl.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>

int main() {
  TreeAVL tp;
  stringstream ss;

  tp.insert(20);
  tp.insert(10);
  tp.insert(30);
  assert(tp.to_string() == "[[20],[10,30]]");
  tp.insert(40);
  tp.insert(50);
  // single rotation
  assert(tp.to_string() == "[[20],[10,40],[30,50]]");
  tp.insert(15);
  tp.insert(18);
  // double rotation
  tp.insert(25);
  tp.insert(27);
  tp.insert(26);
  assert(tp.to_string() == "[[20],[15,27],[10,18,25,40],[26,30,50]]");
  cout << tp << endl;
}