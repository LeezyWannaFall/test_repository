#include "s21_list.h"

namespace s21 {

template <typename T>
list<T>::list() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
list<T>::list(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
  for (size_type i = 0; i < n; ++i) push_back(T());
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items)
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (const auto &item : items) push_back(item);
}

template <typename T>
void list::T>::push_back(const_reference value) {
  Item *new_item = new Item{value, tail_, nullptr};
  if (tail_) {
    tail_->next = new_item;
  } else {
    head_ = new_item;  // List was empty
  }
  tail_ = new_item;
  ++size_;
}

}  // namespace s21
