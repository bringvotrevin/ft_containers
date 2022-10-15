
#include <iostream>
#include <vector>
#include <string>

#include "gtest/gtest.h"

// namespace ft = std;
#include "../vector.hpp"

TEST(VectorConstructor, default_constructor) {
  std::vector<int> vi_1;
  ft::vector<int> vi_2;
  EXPECT_EQ(vi_1.size(), vi_2.size());
  std::vector<std::string> vstr_1;
  ft::vector<std::string> vstr_2;
}
TEST(VectorConstructor, fill_constructor) {
  std::vector<int> vi_1(10);
  std::vector<std::string> vstr_1(10);
}
TEST(VectorConstructor, range_constructor) {
  std::vector<int> vi_1;
  std::vector<int> vi_2(vi_1.begin(), vi_1.end());
}
TEST(VectorConstructor, copy_constructor) {
  std::vector<int> vi_1;
  std::vector<int> vi_2(vi_1);
}
TEST(VectorIterator, iterator) {
  std::vector<int> vi_1(10);
  vi_1.begin();
  vi_1.end();
}
TEST(VectorIterator, reverse_iterator) {
  std::vector<int> vi_1(10);
  vi_1.rbegin();
  vi_1.rend();
}
TEST(VectorIterator, convertible_to_const_iterator) {
  std::vector<int>::iterator it;
  std::vector<int>::const_iterator cit(it);
}
TEST(VectorCapacity, capacity) {
  std::vector<int> vi_1(10);
  vi_1.size();
  vi_1.max_size();
  vi_1.resize(20);
  vi_1.empty();
  vi_1.reserve(40);
}
TEST(VectorElementAceess, element_access) {
  std::vector<int> vi_1(10);
  vi_1[0];
  vi_1.at(0);
  vi_1.front();
  vi_1.back();
}
TEST(VectorModifiers, assign) {
  std::vector<int> vi_1(10);
  std::vector<int> vi_2;
  vi_2.assign(vi_1.begin(), vi_1.end()); // range(1)
  vi_2.assign(20, 5);  // fill(2)
}
TEST(VectorModifiers, push_back) {
  std::vector<int> vi_1;
  vi_1.push_back(10);
}
TEST(VectorModifiers, pop_back) {
  std::vector<int> vi_1(10);
  vi_1.pop_back();
}
TEST(VectorModifiers, insert) {
  std::vector<int> vi_1;
  std::vector<int> vi_2;
  vi_1.insert(vi_1.begin(), 5);  // single element(1)
  vi_1.insert(vi_1.begin(), 10, 42);  // fill(2)
  vi_2.insert(vi_2.begin(), vi_1.begin(), vi_1.end());  // range(3)
}
TEST(VectorModifiers, erase) {
  std::vector<int> vi_1(50);
  vi_1.erase(vi_1.begin());
  vi_1.erase(vi_1.begin(), vi_1.end());
}
TEST(VectorModifiers, swap) {
  std::vector<int> vi_1(5, 42);
  std::vector<int> vi_2(5, 21);
  vi_1.swap(vi_2);
}
TEST(VectorModifiers, clear) {
  std::vector<int> vi_1(5, 42);
  vi_1.clear();
}
TEST(VectorAllocator, get_allocator) {
  std::vector<int> vi_1(5, 42);
  vi_1.get_allocator();
}
TEST(VectorNonMember, swap) {
  std::vector<int> vi_1(5, 42);
  std::vector<int> vi_2(5, 21);
  std::swap(vi_1, vi_2);
}
TEST(VectorNonMember, relational_operators) {
  std::vector<int> vi_1(5, 42);
  std::vector<int> vi_2(5, 42);
  ft::vector<int> __vi_1(5, 42);
  ft::vector<int> __vi_2(5, 42);
  EXPECT_EQ(vi_1 == vi_2, __vi_1 == __vi_2);
  EXPECT_EQ(vi_1 != vi_2, __vi_1 != __vi_2);
  EXPECT_EQ(vi_1 < vi_2, __vi_1 < __vi_2);
  EXPECT_EQ(vi_1 > vi_2, __vi_1 > __vi_2);
  EXPECT_EQ(vi_1 <= vi_2, __vi_1 <= __vi_2);
  EXPECT_EQ(vi_1 >= vi_2, __vi_1 >= __vi_2);
}
int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
