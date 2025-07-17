#ifndef S21_LIST_H_
#define S21_LIST_H_

#include <iostream>

namespace s21 {

template <typename T>
class list {
 private:
  struct Item {
    T data;
    Item *prev;
    Item *next;
  };

  Item *head_;
  Item *tail_;
  size_type size_;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  // Constructors
  list();
  // ...code...
  // Destructor
  ~list();
  // ...methods (code...)
};

}  // namespace s21
#endif  // S21_LIST_H_