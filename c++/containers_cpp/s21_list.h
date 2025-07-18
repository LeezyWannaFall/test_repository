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

 public:
  using size_type = std::size_t;

 private:
  size_type size_;

 public:
  // Class types
  using value_type = T;
  using reference = T &;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using const_reference = const T &;

  // Constructors
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  operator=(list && l);

  // Destructor
  ~list();

  // Accesors
  const_reference front();
  const_reference back();

  // Iterators
  iterator begin();
  iterator end();

  // Capacity
  bool empty();
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

  class ListIterator {
   private:
    // ...code...
   public:
    // ...code...
  }

  class ListConstIterator {
   private:
    // ...code...

   public:
    // ...code...
  }
};

}  // namespace s21
#endif  // S21_LIST_H_