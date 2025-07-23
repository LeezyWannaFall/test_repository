#ifndef S21_LIST_H_
#define S21_LIST_H_

#include <cstddef>         // для std::size_t
#include <initializer_list>

namespace s21 {

template <typename T>
class list {
 public:
  // Iterator classes
  class ListIterator;
  class ListConstIterator;

  // Class types
  using value_type = T;
  using reference = T&;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using const_reference = const T&;
  using size_type = std::size_t;

  // Constructors
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  list& operator=(list &&l);

  // Destructor
  ~list();

  // Accesors
  const_reference front();
  const_reference back();

  // Iterators
  iterator begin();
  iterator end();

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
class list<T>::ListIterator {
 private:
  Item *node_;
 public:
  // Constructor
  explicit ListIterator(Item *value) : node_(value) {}

  // Methods
  T& operator*() const { 
    return node_->data;
  }
  ListIterator& operator++()   {
    node_ = node_->next;
    return *this;
  }
  ListIterator operator++(int){
    auto tmp = *this;
    ++*this;
    return tmp;
  }
  ListIterator& operator--()   {
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
 private:
  const Item *node_;
 public:
  // Constructor
  explicit ListIterator(const Item *value) : node_(value) {}

  // Methods
  const T& operator*() const { 
    return node_->data;
  }
  ListConstIterator& operator++()   {
    node_ = node_->next;
    return *this;
  }
  ListConstIterator operator++(int){
    auto tmp = *this;
    ++*this;
    return tmp;
  }
  ListConstIterator& operator--()   {
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