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
  for (const auto &value : items) {
    push_back(value);
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

template <typename T>
void list<T>::swap(list& other) {
  list<T> copy(*this);
  *this = other;
  other = copy;
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos, const_reference value) {
    Item *new_item = new Item{value, pos.node_->prev, pos.node_};
    if (pos.node_->prev) {
        pos.node_->prev->next = new_item;
    } else {
        head_ = new_item;
    }
    pos.node_->prev = new_item;
    size_++;
    return iterator(new_item);
}
 
template <typename T>
void list<T>::erase(iterator pos) {
    //..code..
}

template <typename T>
typename list<T>::const_reference list<T>::front() {
    //..code..
}

template <typename T>
typename list<T>::const_reference list<T>::back() {
    //..code..
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
    //..code..
}

template <typename T>
typename list<T>::iterator list<T>::end() {
    //..code..
}

template <typename T>
bool list<T>::empty() {
    //..code..
}

template <typename T>
typename list<T>::size_type list<T>::size() {
    //..code..
}

template <typename T>
typename list<T>::size_type list<T>::max_size() {
    //..code..
}

template <typename T>
void list<T>::pop_back() {
    //..code..
}

template <typename T>
void list<T>::pop_front() {
    //..code..
}

template <typename T>
void list<T>::merge(list &other) {
    //..code..
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
    //..code..
}

template <typename T>
void list<T>::reverse() {
    //..code..
}

template <typename T>
void list<T>::unique() {
    //..code..
}

template <typename T>
void list<T>::sort() {
    //..code..
}

}  // namespace s21
