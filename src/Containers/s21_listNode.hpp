#ifndef A2_SIMPLE_NAVIGATOR_CONTAINERS_S21_LISTNODE_HPP
#define A2_SIMPLE_NAVIGATOR_CONTAINERS_S21_LISTNODE_HPP

namespace s21 {

template <class T>
struct node {
  T data_;
  node *pprev;
  node *pnext;
  node(const T &data = T(), node *prev = nullptr, node *next = nullptr)
      : data_(data), pprev(prev), pnext(next) {}
};

template <class T>
struct ListIterator {
  node<T> *it_;
  explicit ListIterator(node<T> *it) noexcept : it_(it) {}
  ~ListIterator() {}
  T &operator*() const noexcept { return it_->data_; }
  node<T> *operator->() { return it_; }
  bool operator==(const ListIterator<T> &other) const noexcept {
    return it_ == other.it_;
  }
  bool operator!=(const ListIterator<T> &other) const noexcept {
    return it_ != other.it_;
  }
  ListIterator<T> &operator++() {
    it_ = it_->pnext;
    return *this;
  }
  ListIterator<T> &operator--() {
    it_ = it_->pprev;
    return *this;
  }
};

template <class T>
struct ListConstIterator {
  const node<T> *it_;
  explicit ListConstIterator(const node<T> *it) noexcept : it_(it) {}
  ~ListConstIterator() {}
  const T &operator*() const noexcept { return it_->data_; }
  bool operator==(const ListConstIterator<T> &other) const noexcept {
    return it_ == other.it_;
  }
  bool operator!=(const ListConstIterator<T> &other) const noexcept {
    return it_ != other.it_;
  }
  ListConstIterator<T> &operator++() {
    it_ = it_->pnext;
    return *this;
  }
  ListConstIterator<T> &operator--() {
    it_ = it_->pprev;
    return *this;
  }
};
}  // namespace s21

#endif  // A2_SIMPLE_NAVIGATOR_CONTAINERS_S21_LISTNODE_HPP
