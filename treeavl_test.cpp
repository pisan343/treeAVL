#include "treeavl.h"

#include <gtest/gtest.h>
namespace {

TEST(TreeAVL, Basic102030) {
  TreeAVL tp;
  stringstream ss;

  tp.insert(10);
  tp.insert(20);
  tp.insert(30);
  EXPECT_EQ(tp.to_string(), "[[20],[10,30]]");
}

TEST(TreeAVL, Basic) {
  TreeAVL tp;
  stringstream ss;

  tp.insert(20);
  tp.insert(10);
  tp.insert(30);
  EXPECT_EQ(tp.to_string(), "[[20],[10,30]]");
}

TEST(TreeAVL, SingleRotate) {
  TreeAVL tp;
  stringstream ss;

  tp.insert(20);
  tp.insert(10);
  tp.insert(30);
  tp.insert(40);
  tp.insert(50);
  // single rotation
  EXPECT_EQ(tp.to_string(), "[[20],[10,40],[30,50]]");
}

TEST(TreeAVL, DoubleRotate) {
  TreeAVL tp;
  stringstream ss;

  tp.insert(20);
  tp.insert(10);
  tp.insert(30);
  tp.insert(40);
  tp.insert(50);
  tp.insert(15);
  tp.insert(18);
  // double rotation
  tp.insert(25);
  tp.insert(27);
  tp.insert(26);
  EXPECT_EQ(tp.to_string(), "[[20],[15,27],[10,18,25,40],[26,30,50]]");
}

} // namespace
