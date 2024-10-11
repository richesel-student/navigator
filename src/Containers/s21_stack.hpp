#ifndef A2_SIMPLE_NAVIGATOR_CONTAINERS_S21_STACK_HPP
#define A2_SIMPLE_NAVIGATOR_CONTAINERS_S21_STACK_HPP

#include <algorithm>
#include <initializer_list>

#include "s21_list.hpp"

namespace s21 {

template <class T, class Container = s21::list<T>>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  // member functions
  stack() noexcept : data_() {}
  explicit stack(std::initializer_list<value_type> const &items)
      : data_{items} {}
  stack(const stack &other) : data_(other.data_) {}
  stack(stack &&other) noexcept : data_(std::move(other.data_)) {}
  ~stack() {}
  stack &operator=(const stack &other) {
    data_ = other.data_;
    return *this;
  }
  stack &operator=(stack &&other) noexcept {
    data_ = std::move(other.data_);
    return *this;
  }

  // element access
  reference top() { return data_.back(); }
  const_reference top() const { return data_.back(); }

  // capacity
  bool empty() const noexcept { return data_.empty(); }
  size_type size() const noexcept { return data_.size(); }

  // modifiers
  void push(const_reference value) { data_.push_back(value); }
  void pop() { data_.pop_back(); }
  void swap(stack &other) noexcept { data_.swap(other.data_); }

  template <class... Args>
  void emplace_front(Args &&...args) {
    data_.emplace_back(args...);
  }

 private:
  Container data_;
};
}  // namespace s21

#endif  // A2_SIMPLE_NAVIGATOR_CONTAINERS_S21_STACK_HPP
