#ifndef A2_SIMPLE_NAVIGATOR_MATRIX_MATRIX_H
#define A2_SIMPLE_NAVIGATOR_MATRIX_MATRIX_H

#include <cstring>
#include <stdexcept>

namespace s21 {

template <class T>
class Matrix {
 public:
  Matrix() : Matrix(1, 1) {}
  Matrix(int row, int col) : row_(row), col_(col) {
    if (row < 1 || col < 1) {
      throw "Incorrect input, should be more than zero";
    }
    matrix_ = new T[row_ * col_]();
  }
  ~Matrix() { delete[] matrix_; }
  Matrix(const Matrix &other) : row_(other.row_), col_(other.col_) {
    matrix_ = new T[row_ * col_]();
    std::memcpy(matrix_, other.matrix_, row_ * col_ * sizeof(T));
  }
  Matrix(Matrix &&other) noexcept {
    row_ = other.row_;
    col_ = other.col_;
    matrix_ = other.matrix_;
    other.row_ = other.col_ = 0;
    other.matrix_ = nullptr;
  }

  Matrix &operator=(const Matrix &other) {
    if (this == &other) {
      return *this;
    }
    delete[] matrix_;
    row_ = other.row_;
    col_ = other.col_;
    matrix_ = new T[row_ * col_]();
    std::memcpy(matrix_, other.matrix_, row_ * col_ * sizeof(T));
    return *this;
  }
  Matrix &operator=(Matrix &&other) noexcept {
    if (this == &other) {
      return *this;
    }
    std::swap(row_, other.row_);
    std::swap(col_, other.col_);
    std::swap(matrix_, other.matrix_);
    return *this;
  }
  void set(int row, int col, const T &value) {
    IsValid(row, col);
    matrix_[row * col_ + col] = value;
  }
  T &operator()(int row, int col) {
    IsValid(row, col);
    return matrix_[row * col_ + col];
  }
  T operator()(int row, int col) const {
    IsValid(row, col);
    return matrix_[row * col_ + col];
  }
  bool operator==(const Matrix &other) const {
    for (int i = 0; i < row_; ++i) {
      for (int j = 0; j < col_; ++j) {
        if (matrix_[i * row_ + j] != other.matrix_[i * row_ + j]) {
          return false;
        }
      }
    }
    return true;
  }
  int get_row() const noexcept { return row_; }
  int get_col() const noexcept { return col_; }

 private:
  void IsValid(int row, int col) const {
    if (row > row_ || row < 0 || col > col_ || col < 0) {
      throw std::out_of_range("Incorrect input, index out of range");
    }
  }
  int row_, col_;
  T *matrix_;
};
}  // namespace s21

#endif  // A2_SIMPLE_NAVIGATOR_MATRIX_MATRIX_H
