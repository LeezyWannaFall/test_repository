#include <gtest/gtest.h>
#include "s21_array.h"

TEST(S21ArrayTest, DefaultConstructor) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.size(), 5);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], int());
  }
}

TEST(S21ArrayTest, InitializerListConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.size(), 5);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], i + 1);
  }
}

TEST(S21ArrayTest, CopyConstructor) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2(arr1);
  EXPECT_EQ(arr2.size(), arr1.size());
  for (size_t i = 0; i < arr2.size(); ++i) {
    EXPECT_EQ(arr2[i], arr1[i]);
  }
}

TEST(S21ArrayTest, MoveConstructor) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2(std::move(arr1));
  EXPECT_EQ(arr2.size(), 5);
  for (size_t i = 0; i < arr2.size(); ++i) {
    EXPECT_EQ(arr2[i], i + 1);
  }
}

TEST(S21ArrayTest, MoveAssignmentOperator) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2;
  arr2 = std::move(arr1);
  EXPECT_EQ(arr2.size(), 5);
  for (size_t i = 0; i < arr2.size(); ++i) {
    EXPECT_EQ(arr2[i], i + 1);
  }
}

TEST(S21ArrayTest, FillMethod) {
  s21::array<int, 5> arr;
  arr.fill(10);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 10);
  }
}

TEST(S21ArrayTest, AtMethod) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.at(0), 1);
  EXPECT_EQ(arr.at(4), 5);
}

TEST(S21ArrayTest, FrontMethod) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.front(), 1);
}

TEST(S21ArrayTest, BackMethod) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.back(), 5);
}

TEST(S21ArrayTest, DataMethod) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int* data_ptr = arr.data();
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(data_ptr[i], arr[i]);
  }
}

TEST(S21ArrayTest, EmptyMethod) {
  s21::array<int, 5> arr;
  EXPECT_FALSE(arr.empty());
  s21::array<int, 0> empty_arr;
  EXPECT_TRUE(empty_arr.empty());
}

TEST(S21ArrayTest, SizeMethod) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.size(), 5);
}

TEST(S21ArrayTest, MaxSizeMethod) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.max_size(), 5);
}

TEST(S21ArrayTest, SwapMethod) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = {6, 7, 8, 9, 10};
  arr1.swap(arr2);
  
  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], i + 6);
    EXPECT_EQ(arr2[i], i + 1);
  }
}

TEST(S21ArrayTest, OperatorElement) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[4], 5);
}

TEST(S21ArrayTest, Begin) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  auto it = arr.begin();
  EXPECT_EQ(*it, 1);
}

TEST(S21ArrayTest, End) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  auto it = arr.end();
  --it; // Move to the last element
  EXPECT_EQ(*it, 5);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
