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
array<T, N>::array() {}

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
}

template<typename T, std::size_t N>
array<T, N>& array<T, N>::operator=(array &&a) {
  if (this != &a) {
    for (size_type i = 0; i < N; ++i) {
      data_[i] = std::move(a.data_[i]);
    }
  }
  return *this;
}

template <typename T, std::size_t N>
array<T, N>::~array() {} 

template<typename T, std::size_t N>
T& array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("Value must be in array size");
  }
  return data_[pos];
} 

template <typename T, std::size_t N>
const T& array<T, N>::front() {
  return data_[0];
}

template <typename T, std::size_t N>
const T& array<T, N>::back() {
  return data_[N - 1];
}

template <typename T, std::size_t N>
T& array<T, N>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T, std::size_t N>
T* array<T, N>::data() {
  return data_;
}

template <typename T, std::size_t N>
bool array<T, N>::empty() {
  return N == 0;
}

template <typename T, std::size_t N>
size_t array<T, N>::size() {
  return N;
}

template <typename T, std::size_t N>
size_t array<T, N>::max_size() {
  return N; // THIS SHIT IS SAME AS SIZE() LMAO
}

template <typename T, std::size_t N>
void array<T, N>::swap(array& other) {
  for (size_type i = 0; i < N; i++) {
    value_type tmp = data_[i];
    data_[i] = other.data_[i];
    other.data_[i] = tmp;
  }
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < N; i++) {
    data_[i] = value;
  }
}

} // namespace s21
#endif // S21_ARRAY_H_
