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
  for (const auto &x : items) {
    push_back(x);
  }
}

template <typename T>
list<T>::list(const list &l) : head_(nullptr), tail_(nullptr), size_(0) {
  for (const auto &value : l) {
    push_back(value);
  }
}

template <typename T>
list<T>::list(list &&l) : head_(l.head_), tail_(l.tail_), size_(l.size_) {
  l.tail_ = nullptr;
  l.head_ = nullptr;
  size_ = 0;
}

template <typename T>
list<T>::~list() {
  clear();
}

template <typename T>
typename list<T>::list& list<T>::operator=(list &&l) {
  if (this == &l) {
    return *this;
  }
  clear();
  head_ = l.head_;
  tail_ = l.tail_;
  size_ = l.size_;

  for (auto &value : l) {
    push_back(value);
  }
  l.tail_ = nullptr;
  l.head_ = nullptr;
  size_ = 0;

  return *this;
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Item *new_item = new Item{value, tail_, nullptr};
  if (tail_) {
    tail_->next = new_item;
  } else {
    head_ = new_item;  // List was empty
  }
  tail_ = new_item;
  size_++;
}

template <typename T>
void list<T>::push_front(const_reference value) {
  Item *new_item = new Item{value, nullptr, head_};
  if (head_) {
    head_->prev = new_item;
  } else {
    tail_ = new_item; // List was empty
  }
  head_ = new_item;
  size_++;
}

template <typename T>
void list<T>::clear() {
  Item *current = head_;
  while (current) {
    Item *next = current->next;
    delete current;
    current = next;
  }

  head_ = nullptr;
  tail_ = nullptr;
  size_ = 0;
}

}  // namespace s21
