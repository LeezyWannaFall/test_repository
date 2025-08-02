#include "s21_list.h"

#include <gtest/gtest.h>

TEST(ListTest, DefaultConstructor) {
  s21::list<int> list;
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, PushBackAndSize) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);
  EXPECT_EQ(list.size(), 2);
  EXPECT_FALSE(list.empty());
}

TEST(ListTest, PushFrontAndSize) {
  s21::list<int> list;
  list.push_front(1);
  list.push_front(2);
  EXPECT_EQ(list.size(), 2);
  EXPECT_FALSE(list.empty());
}

TEST(ListTest, PopBack) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.pop_back();
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.back(), 1);
}

TEST(ListTest, PopFront) {
  s21::list<int> list;
  list.push_front(1);
  list.push_front(2);
  list.pop_front();
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.front(), 1);
}

TEST(ListTest, Clear) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.clear();
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, FrontAndBack) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 2);
}

TEST(ListTest, Insert) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(3);
  auto it = list.begin();
  ++it;  // Move to the second element
  list.insert(it, 2);
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, Erase) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  auto it = list.begin();
  ++it;  // Move to the second element
  list.erase(it);
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, Iterator) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  int sum = 0;
  for (auto it = list.begin(); it != list.end(); ++it) {
    sum += *it;
  }

  EXPECT_EQ(sum, 6);  // 1 + 2 + 3
}

TEST(ListTest, CopyConstructor) {
  s21::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);

  s21::list<int> list2(list1);
  EXPECT_EQ(list2.size(), 2);
  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 2);
}

TEST(ListTest, MoveConstructor) {
  s21::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);

  s21::list<int> list2(std::move(list1));
  EXPECT_EQ(list2.size(), 2);
  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 2);
  EXPECT_TRUE(list1.empty());  // list1 should be empty after move
}

TEST(ListTest, Swap) {
  s21::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);

  s21::list<int> list2;
  list2.push_back(3);

  list1.swap(list2);

  EXPECT_EQ(list1.size(), 1);
  EXPECT_EQ(list1.front(), 3);

  EXPECT_EQ(list2.size(), 2);
  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 2);
}

TEST(ListTest, Merge) {
  s21::list<int> list1;
  list1.push_back(1);
  list1.push_back(3);

  s21::list<int> list2;
  list2.push_back(2);
  list2.push_back(4);

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 4);
  EXPECT_EQ(list1.front(), 1);
  EXPECT_EQ(list1.back(), 4);
}

TEST(ListTest, Splice) {
  s21::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);

  s21::list<int> list2;
  list2.push_back(3);
  list2.push_back(4);

  auto it = list1.begin();
  ++it;  // Move to the second element
  list1.splice(s21::list<int>::const_iterator(it), list2);

  EXPECT_EQ(list1.size(), 4);
  EXPECT_EQ(list1.front(), 1);
  EXPECT_EQ(list1.back(), 4);
}

TEST(ListTest, Reverse) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list.reverse();

  EXPECT_EQ(list.front(), 3);
  EXPECT_EQ(list.back(), 1);
}

TEST(ListTest, Unique) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(1);
  list.push_back(2);

  list.unique();

  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 2);
}

TEST(ListTest, Sort) {
  s21::list<int> list;
  list.push_back(3);
  list.push_back(1);
  list.push_back(2);

  list.sort();

  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, MaxSize) {
  s21::list<int> list;
  EXPECT_GT(list.max_size(), 0);  // Check that max_size is greater than 0
}

TEST(ListTest, Empty) {
  s21::list<int> list;
  EXPECT_TRUE(list.empty());

  list.push_back(1);
  EXPECT_FALSE(list.empty());

  list.clear();
  EXPECT_TRUE(list.empty());
}

TEST(ListTest, Size) {
  s21::list<int> list;
  EXPECT_EQ(list.size(), 0);

  list.push_back(1);
  EXPECT_EQ(list.size(), 1);

  list.push_back(2);
  EXPECT_EQ(list.size(), 2);

  list.pop_back();
  EXPECT_EQ(list.size(), 1);

  list.clear();
  EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, FrontAndBackAccess) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);

  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 2);

  list.pop_front();
  EXPECT_EQ(list.front(), 2);

  list.pop_back();
  EXPECT_TRUE(list.empty());
}

TEST(ListTest, IteratorOperations) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  auto it = list.begin();
  EXPECT_EQ(*it, 1);

  ++it;
  EXPECT_EQ(*it, 2);

  --it;
  EXPECT_EQ(*it, 1);

  it++;
  EXPECT_EQ(*it, 2);

  it--;
  EXPECT_EQ(*it, 1);
}

TEST(ListTest, ConstIterator) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);

  s21::list<int>::const_iterator it = list.begin();
  EXPECT_EQ(*it, 1);

  ++it;
  EXPECT_EQ(*it, 2);

  --it;
  EXPECT_EQ(*it, 1);

  it++;
  EXPECT_EQ(*it, 2);

  it--;
  EXPECT_EQ(*it, 1);
}

TEST(ListTest, IteratorEquality) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);

  auto it1 = list.begin();
  auto it2 = list.begin();

  EXPECT_TRUE(it1 == it2);  // Same iterator should be equal
  ++it2;
  EXPECT_FALSE(it1 == it2);  // Different iterators should not be equal
}

TEST(ListTest, ConstIteratorEquality) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);

  auto it1 = list.begin();
  auto it2 = list.begin();

  EXPECT_TRUE(it1 == it2);  // Same iterator should be equal
  ++it2;
  EXPECT_FALSE(it1 == it2);  // Different iterators should not be equal
}

TEST(ListTest, IteratorInequality) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);

  auto it1 = list.begin();
  auto it2 = list.begin();

  EXPECT_FALSE(it1 != it2);  // Same iterator should not be unequal
  ++it2;
  EXPECT_TRUE(it1 != it2);  // Different iterators should be unequal
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}