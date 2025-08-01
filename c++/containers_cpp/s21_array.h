#ifndef S21_ARRAY_H_
#define S21_ARRAY_H_

// Includes
#include <stdexcept>
#include <cstddef> // For size_t

namespace s21 {

template <typename T, std::size_t N>    
class array {
 public:
  // Class types
  using value_type = T;
  using reference = T &;
  using iterator = T *;
  using const_iterator = const T *; 
  using const_reference = const T &;
  using size_type = std::size_t;

  // Constructors
  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a);
  ~array();
  array& operator=(array &&a);

  // Acces
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  // Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // iterators
  iterator begin() { return data_; }
  iterator end()   { return data_ + N; }

  // Modifiers
  void swap(array& other);
  void fill(const_reference value);

 private:
  value_type data_[N];
};

template <typename T, std::size_t N>
array<T, N>::array() : size_(N) {}

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  if (items.size() > N) {
    throw std::out_of_range("Too many initializer values");
  }
  size_type i = 0;
  for (auto &value : items) {
    data_[i++] = value;
  }
}

template <typename T, std::size_t N>
array<T, N>::array(const array &a) {
  for (size_type i = 0; i < N; ++i) {
    data_[i] = a.data_[i];
  }
}

template <typename T, std::size_t N>
array<T, N>::array(array &&a) {
  for (size_type i = 0; i < N; i++) {
    data_[i] = std::move(a.data_[i]);
  }
  delete data_;
}

template<typename T, std::size_t N>
array<T, N>& array<T, N>::operator=() { // Fix cap
  // ...code...
}

template <typename T, std::size_t N>
array<T, N>::~array() {} 


} // namesoace s21
#endif // S21_ARRAY_H_
