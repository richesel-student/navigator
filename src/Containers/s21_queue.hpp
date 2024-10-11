#ifndef A2_SIMPLE_NAVIGATOR_CONTAINERS_S21_QUEUE_HPP
#define A2_SIMPLE_NAVIGATOR_CONTAINERS_S21_QUEUE_HPP

#include <algorithm>
#include <initializer_list>

#include "s21_list.hpp"

namespace s21 {

template <class T, class Container = s21::list<T>>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  // member functions
  queue() noexcept : data_() {}
  explicit queue(std::initializer_list<value_type> const &items)
      : data_{items} {}
  queue(const queue &other) : data_(other.data_) {}
  queue(queue &&other) noexcept : data_(std::move(other.data_)) {}
  ~queue() {}
  queue &operator=(const queue &other) {
    data_ = other.data_;
    return *this;
  }
  queue &operator=(queue &&other) noexcept {
    data_ = std::move(other.data_);
    return *this;
  }

  // element access
  reference front() { return data_.front(); }
  const_reference front() const { return data_.front(); }
  reference back() { return data_.back(); }
  const_reference back() const { return data_.back(); }

  // capacity
  bool empty() const noexcept { return data_.empty(); }
  size_type size() const noexcept { return data_.size(); }

  // modifiers
  void push(const_reference value) { data_.push_back(value); }
  void pop() { data_.pop_front(); }
  void swap(queue &other) noexcept { data_.swap(other.data_); }

  template <class... Args>
  void emplace_back(Args &&...args) {
    data_.emplace_back(args...);
  }

 private:
  Container data_;
};
}  // namespace s21

#endif  // A2_SIMPLE_NAVIGATOR_CONTAINERS_S21_QUEUE_HPP
