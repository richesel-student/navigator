#ifndef A2_SIMPLE_NAVIGATOR_CONTAINERS_S21_LIST_HPP
#define A2_SIMPLE_NAVIGATOR_CONTAINERS_S21_LIST_HPP

#include <algorithm>
#include <initializer_list>

#include "s21_listNode.hpp"

namespace s21 {

template <class T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using size_type = std::size_t;

  // member functions
  list() : begin_(new node<value_type>(value_type())), size_(0) {
    end_ = begin_;
  }
  explicit list(size_type count) : list() {
    while (count--) {
      push_back(value_type());
    }
  }
  explicit list(std::initializer_list<value_type> const &items) : list() {
    for (auto elem : items) {
      push_back(elem);
    }
  }
  list(const list &other) : list() {
    for (auto &elem : other) {
      push_back(elem);
    }
  }
  list(list &&other) : list() { swap(other); }
  ~list() {
    clear();
    delete end_;
  }
  list<value_type> &operator=(const list &other) {
    clear();
    for (auto &elem : other) {
      push_back(elem);
    }
    size_ = other.size_;
    return *this;
  }
  list<value_type> &operator=(list &&other) {
    swap(other);
    other.clear();
    return *this;
  }

  // element access
  reference front() { return begin_->data_; }
  const_reference front() const { return begin_->data_; }
  reference back() { return end_->pprev->data_; }
  const_reference back() const { return end_->pprev->data_; }
  // iterators
  iterator begin() { return iterator(begin_); }
  const_iterator begin() const { return const_iterator(begin_); }
  iterator end() { return iterator(end_); }
  const_iterator end() const { return const_iterator(end_); }
  // capacity
  bool empty() const noexcept { return size_ == 0; }
  size_type size() const noexcept { return size_; }

  // modifiers
  void clear() noexcept {
    while (size_ > 0) {
      erase(begin());
    }
  }
  iterator insert(iterator pos, const_reference value) {
    node<value_type> *add_node = new node<value_type>(value);
    if (size_ == 0) {
      begin_ = add_node;
      begin_->pnext = end_;
      end_->pprev = begin_;
    } else {
      insert_node(pos, add_node);
    }
    ++size_;
    return iterator(add_node);
  }
  void erase(iterator pos) {
    if (pos != end()) {
      if (pos == begin()) {
        begin_ = begin_->pnext;
        begin_->pprev = nullptr;
        delete pos.it_;
      } else {
        pos->pprev->pnext = pos->pnext;
        pos->pnext->pprev = pos->pprev;
        delete pos.it_;
      }
      --size_;
    }
  }
  void push_back(const_reference value) { insert(end(), value); }
  void pop_back() { erase(--end()); }
  void push_front(const_reference value) { insert(begin(), value); }
  void pop_front() { erase(begin()); }
  void swap(list &other) noexcept {
    std::swap(begin_, other.begin_);
    std::swap(end_, other.end_);
    std::swap(size_, other.size_);
  }
  void splice(iterator pos, list &other) {
    if (pos == begin()) {
      other.end_->pprev->pnext = begin_;
      begin_->pprev = other.end_->pprev;
      begin_ = other.begin_;
    } else {
      pos->pprev->pnext = other.begin_;
      other.begin_->pprev = pos->pprev;
      pos->pprev = other.end_->pprev;
      other.end_->pprev->pnext = pos.it_;
    }
    other.begin_ = other.end_;
    other.end_->pprev = nullptr;
    size_ += other.size_;
    other.size_ = 0;
  }
  void unique() {
    if (size_ != 0) {
      iterator first(begin());
      iterator second(++begin());
      while (second != end()) {
        if (*first == *second) {
          ++second;
          erase(iterator(second->pprev));
        } else {
          ++first;
          ++second;
        }
      }
    }
  }
  void merge(list &other) {
    if (&other != this && other.size_ != 0) {
      if (size_ == 0) {
        swap(other);
      } else {
        iterator temp(begin());
        iterator other_temp(other.begin());
        while (temp != end() && other_temp != other.end()) {
          if (*temp < *other_temp) {
            ++temp;
          } else {
            ++other_temp;
            insert_node(temp, other_temp->pprev);
            ++size_;
            --other.size_;
            other.begin_ = other_temp.it_;
          }
        }
        if (other.size_ > 0) {
          splice(end(), other);
        }
      }
    }
  }
  void reverse() noexcept {
    if (size_ > 0) {
      iterator it_begin = begin();
      while (it_begin != end()) {
        ++it_begin;
        std::swap(it_begin->pprev->pprev, it_begin->pprev->pnext);
      }
      begin_->pnext = end_;
      std::swap(begin_, end_->pprev);
      begin_->pprev = nullptr;
    }
  }

  void sort() {
    if (size_ > 1) {
      iterator first(begin());
      iterator second(++begin());
      while (second != end()) {
        if (*first < *second) {
          ++first;
          ++second;
        } else {
          iterator move_node(second.it_);
          ++second;
          second->pprev = first.it_;
          first->pnext = second.it_;
          iterator pos(first.it_);
          while (*move_node < *pos && pos != begin()) {
            --pos;
          }
          if (*pos < *move_node) ++pos;
          insert_node(pos, move_node.it_);
        }
      }
    }
  }

  template <class... Args>
  iterator emplace(iterator pos, Args &&...args) {
    for (auto elem : {std::forward<Args>(args)...}) {
      insert(pos, elem);
    }
    return pos;
  }

  template <class... Args>
  void emplace_back(Args &&...args) {
    emplace(end(), args...);
  }

  template <class... Args>
  void emplace_front(Args &&...args) {
    emplace(begin(), args...);
  }

 private:
  void insert_node(iterator pos, node<value_type> *add_node) {
    if (pos == iterator(begin_)) {
      add_node->pnext = begin_;
      begin_ = begin_->pprev = add_node;
    } else {
      add_node->pprev = pos->pprev;
      add_node->pnext = pos.it_;
      pos->pprev = pos->pprev->pnext = add_node;
    }
  }
  node<T> *begin_;
  node<T> *end_;
  size_t size_;
};
}  // namespace s21

#endif  // A2_SIMPLE_NAVIGATOR_CONTAINERS_S21_LIST_HPP
