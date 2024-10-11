#ifndef A2_SIMPLE_NAVIGATOR_GRAPHALGORITHMS_GRAPHALGORITHMS_H
#define A2_SIMPLE_NAVIGATOR_GRAPHALGORITHMS_GRAPHALGORITHMS_H

#include <fstream>
#include <iostream>
#include <vector>

#include "../Graph/s21_graph.h"
#include "../Matrix/matrix.h"

namespace s21 {

struct TsmResult {
  std::vector<int> vertices;
  double distance;
};

class GraphAlgorithms {
 public:
  std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);
  std::vector<int> BreadthFirstSearch(Graph &graph, int start_vertex);
  int GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  Matrix<int> GetShortestPathsBetweenAllVertices(Graph &graph);
  Matrix<int> GetLeastSpanningTree(Graph &graph);
  TsmResult SolveTravelingSalesmanProblem(Graph &graph);
};

}  // namespace s21
#endif  //  A2_SIMPLE_NAVIGATOR_GRAPHALGORITHMS_GRAPHALGORITHMS_H