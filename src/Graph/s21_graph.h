#ifndef A2_SIMPLE_NAVIGATOR_GRAPH_GRAPH_H
#define A2_SIMPLE_NAVIGATOR_GRAPH_GRAPH_H

#include <vector>

#include "../Matrix/matrix.h"

namespace s21 {
class Graph {
 public:
  Graph() {}
  ~Graph() {}
  void LoadGraphFromFile(std::string filename);
  void ExportGraphToDot(std::string filename);
  int get_size() { return size_; }
  Matrix<int> get_adj_matrix() { return adjacency_matrix_; }
  std::vector<int> get_neighboring_vertices(int vertex);

 private:
  void CheckDirected();
  int size_ = 1;
  bool is_directed_ = false;
  Matrix<int> adjacency_matrix_;
};

}  // namespace s21
#endif  // A2_SIMPLE_NAVIGATOR_GRAPH_GRAPH_H