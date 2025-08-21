#ifndef S21_LIST_H_
#define S21_LIST_H_

#include <cstddef>  // для std::size_t
#include <initializer_list>
#include <limits>
#include <stdexcept>

namespace s21 {

template <typename T>
class list {
 public:
  // Iterator classes
  class ListIterator;
  class ListConstIterator;

  // Class types
  using value_type = T;
  using reference = T &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using const_reference = const T &;
  using size_type = std::size_t;

  // Constructors
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  list &operator=(list &&l);

  // Destructor
  ~list();

  // Accesors
  const_reference front();
  const_reference back();

  // Iterators
  iterator begin();
  iterator end();

  const_iterator begin() const noexcept { return const_iterator(head_); }
  const_iterator end() const noexcept { return const_iterator(nullptr); }

  // Capacity
  bool empty() const;
  size_type size();
  size_type max_size();

  // Methods
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  void insert_many_front(Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args)

 private:
  struct Item {
    T data;
    Item *prev;
    Item *next;
  };

  Item *head_;
  Item *tail_;
  size_type size_;
};

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
  l.size_ = 0;
}

template <typename T>
list<T>::~list() {
  clear();
}

template <typename T>
typename list<T>::list &list<T>::operator=(list &&l) {
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
    tail_ = new_item;  // List was empty
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
void list<T>::swap(list &other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
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
  if (pos.node_ == head_) {
    head_ = pos.node_->next;
  }
  if (pos.node_ == tail_) {
    tail_ = pos.node_->prev;
  }
  if (pos.node_->prev) {
    pos.node_->prev->next = pos.node_->next;
  }
  if (pos.node_->next) {
    pos.node_->next->prev = pos.node_->prev;
  }
  delete pos.node_;
  size_--;
}

template <typename T>
typename list<T>::const_reference list<T>::front() {
  if (!head_) throw std::out_of_range("List is empty");
  return head_->data;
}

template <typename T>
typename list<T>::const_reference list<T>::back() {
  if (!tail_) throw std::out_of_range("List is empty");
  return tail_->data;
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  return iterator(head_);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator(nullptr);
}

template <typename T>
bool list<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename list<T>::size_type list<T>::size() {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() {
  return std::numeric_limits<size_type>::max();
}

template <typename T>
void list<T>::pop_back() {
  if (!tail_) throw std::out_of_range("List is empty");
  Item *to_delete = tail_;
  tail_ = tail_->prev;
  if (tail_) {
    tail_->next = nullptr;
  } else {
    head_ = nullptr;  // List is now empty
  }
  delete to_delete;
  size_--;
}

template <typename T>
void list<T>::pop_front() {
  if (!head_) throw std::out_of_range("List is empty");
  Item *to_delete = head_;
  head_ = head_->next;
  if (head_) {
    head_->prev = nullptr;
  } else {
    tail_ = nullptr;  // List is now empty
  }
  delete to_delete;
  size_--;
}

template <typename T>
void list<T>::merge(list &other) {
  if (this == &other) throw std::out_of_range("No need to merge with itself");
  if (other.empty()) throw std::out_of_range("Nothing to merge");
  if (this->empty()) {
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
  } else {
    tail_->next = other.head_;
    other.head_->prev = tail_;
    tail_ = other.tail_;
    size_ += other.size_;
  }

  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
  if (other.empty()) {
    throw std::out_of_range("Other list is empty");
  }
  if (this == &other) {
    throw std::out_of_range("Cannot splice with itself");
  }

  Item *pos_node = const_cast<Item *>(pos.node_);
  if (pos_node) {
    if (pos_node->prev) {
      pos_node->prev->next = other.head_;
    } else {
      head_ = other.head_;
    }
    other.head_->prev = pos_node->prev;
    pos_node->prev = other.tail_;
  } else {
    tail_->next = other.head_;
    other.head_->prev = tail_;
  }

  tail_ = other.tail_;
  size_ += other.size_;

  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename T>
void list<T>::reverse() {
  if (size_ <= 1) {
    throw std::out_of_range("List is empty or has only one element");
  }
  Item *current = head_;
  Item *temp = nullptr;
  tail_ = head_;  // New tail will be the old head

  while (current != nullptr) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev;  // Move to the next item
  }

  if (temp) {
    head_ = temp->prev;  // New head will be the last processed item
  } else {
    head_ = tail_;  // If temp is null, it means we reached the end
  }
}

template <typename T>
void list<T>::unique() {
  if (size_ <= 1) {
    throw std::out_of_range("List is empty or has only one element");
  }

  Item *current = head_;
  while (current && current->next) {
    if (current->data == current->next->data) {
      Item *to_delete = current->next;
      current->next = to_delete->next;
      if (to_delete->next) {
        to_delete->next->prev = current;
      } else {
        tail_ = current;  // Update tail if we removed the last item
      }
      delete to_delete;
      size_--;
    } else {
      current = current->next;
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (size_ <= 1) {
    throw std::out_of_range("List is empty or has only one element");
  }

  bool swapped;
  do {
    swapped = false;
    Item *current = head_;
    while (current && current->next) {
      if (current->data > current->next->data) {
        std::swap(current->data, current->next->data);
        swapped = true;
      }
      current = current->next;
    }
  } while (swapped);
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args&&... args) {
  (push_front(std::forward<Args>(args)), ...);
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args&&... args) {
  (push_back(std::forward<Args>(args)), ...);
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos, Args&&... args) {
  if (pos.node_ == nullptr) {
    throw std::out_of_range("Cannot insert at end of list");
  }
  
  iterator it = iterator(pos.node_);
  (it = insert(it, std::forward<Args>(args)), ...);
  return it;
}

template <typename T>
class list<T>::ListIterator {
  friend class list<T>;

 private:
  Item *node_;

 public:
  // Constructor
  explicit ListIterator(Item *value) : node_(value) {}

  // Methods
  T &operator*() const { return node_->data; }
  ListIterator &operator++() {
    node_ = node_->next;
    return *this;
  }
  ListIterator operator++(int) {
    auto tmp = *this;
    ++*this;
    return tmp;
  }
  ListIterator &operator--() {
    node_ = node_->prev;
    return *this;
  }
  ListIterator operator--(int) {
    auto tmp = *this;
    --*this;
    return tmp;
  }

  bool operator==(const ListIterator &other) const {
    return node_ == other.node_;
  }
  bool operator!=(const ListIterator &other) const {
    return node_ != other.node_;
  }
};

template <typename T>
class list<T>::ListConstIterator {
  friend class list<T>;

 private:
  const Item *node_;

 public:
  // Constructor
  explicit ListConstIterator(const Item *value) : node_(value) {}
  ListConstIterator(const ListIterator &it) noexcept : node_(it.node_) {}
  // Methods
  const T &operator*() const { return node_->data; }
  ListConstIterator &operator++() {
    node_ = node_->next;
    return *this;
  }
  ListConstIterator operator++(int) {
    auto tmp = *this;
    ++*this;
    return tmp;
  }
  ListConstIterator &operator--() {
    node_ = node_->prev;
    return *this;
  }
  ListConstIterator operator--(int) {
    auto tmp = *this;
    --*this;
    return tmp;
  }

  bool operator==(const ListConstIterator &other) const {
    return node_ == other.node_;
  }
  bool operator!=(const ListConstIterator &other) const {
    return node_ != other.node_;
  }
};

}  // namespace s21

#endif  // S21_LIST_H_