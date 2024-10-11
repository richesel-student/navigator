#include "s21_graphalgorithms.h"

#include <climits>
#include <stdexcept>
#include <vector>

#include "../Containers/s21_queue.hpp"
#include "../Containers/s21_stack.hpp"
#include "s21_ACO.h"

namespace s21 {

std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph,
                                                   int start_vertex) {
  int size = graph.get_size();
  if (start_vertex > size || start_vertex < 1) {
    throw std::invalid_argument("This graph has not this vertex");
  }
  std::vector<int> visited(size + 1, 0);
  std::vector<int> route;
  stack<int> vertex_stack;
  vertex_stack.push(start_vertex);

  while (!vertex_stack.empty()) {
    int current_vertex = vertex_stack.top();
    vertex_stack.pop();
    if (!visited[current_vertex]) {
      visited[current_vertex] = 1;
      route.push_back(current_vertex);
      for (int neighbor : graph.get_neighboring_vertices(current_vertex)) {
        if (!visited[neighbor]) {
          vertex_stack.push(neighbor);
        }
      }
    }
  }
  return route;
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                     int start_vertex) {
  int size = graph.get_size();
  if (start_vertex > size || start_vertex < 1) {
    throw std::invalid_argument("This graph has not this vertex");
  }
  std::vector<bool> visited(size + 1, false);
  std::vector<int> route;
  queue<int> vertex_queue;
  vertex_queue.push(start_vertex);
  visited[start_vertex] = true;

  while (!vertex_queue.empty()) {
    int current_vertex = vertex_queue.front();
    route.push_back(current_vertex);
    vertex_queue.pop();
    for (int neighbor : graph.get_neighboring_vertices(current_vertex)) {
      if (!visited[neighbor]) {
        vertex_queue.push(neighbor);
        visited[neighbor] = true;
      }
    }
  }
  return route;
}

int GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                    int vertex2) {
  int size = graph.get_size();
  if (vertex1 > size || vertex1 < 1 || vertex2 > size || vertex2 < 1) {
    throw std::invalid_argument("This graph has not this vertex");
  }
  --vertex1;
  --vertex2;
  Matrix<int> adj_matrix = graph.get_adj_matrix();
  std::vector<int> mark(size, INT_MAX);
  std::vector<bool> is_visited(size, false);
  mark[vertex1] = 0;

  for (int i = 0; i < size; ++i) {
    // find the vertex with min distance value
    int min_mark = INT_MAX;
    int min_index = -1;
    for (int j = 0; j < size; ++j) {
      if (!is_visited[j] && mark[j] < min_mark) {
        min_mark = mark[j];
        min_index = j;
      }
    }
    // go to min_index vertex
    is_visited[min_index] = true;
    // change distance value for neighbour
    for (int j = 0; j < size; j++) {
      if (!is_visited[j] && adj_matrix(min_index, j) != 0) {
        mark[j] = std::min(mark[j], mark[min_index] + adj_matrix(min_index, j));
      }
    }
  }
  return mark[vertex2];
}

Matrix<int> GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph) {
  Matrix<int> result = graph.get_adj_matrix();
  for (int i = 0; i < graph.get_size(); ++i) {
    for (int j = 0; j < graph.get_size(); ++j) {
      if (i != j && !result(i, j)) {
        result(i, j) = INT_MAX;
      }
    }
  }
  for (int v = 0; v < graph.get_size(); ++v) {
    for (int i = 0; i < graph.get_size(); ++i) {
      for (int j = 0; j < graph.get_size(); ++j) {
        if (result(i, v) != INT_MAX && result(v, j) != INT_MAX) {
          result(i, j) = std::min(result(i, j), result(v, j) + result(i, v));
        }
      }
    }
  }
  return result;
}

Matrix<int> GraphAlgorithms::GetLeastSpanningTree(Graph &graph) {
  Matrix<int> adj_matrix = graph.get_adj_matrix();
  std::vector<int> mark(graph.get_size(), INT_MAX);
  std::vector<bool> is_visited(graph.get_size(), false);
  std::vector<int> parent(graph.get_size(), -1);
  mark[0] = 0;

  for (int i = 0; i < graph.get_size() - 1; ++i) {
    int index = -1;
    int min_dist = INT_MAX;
    for (int j = 0; j < graph.get_size(); ++j) {
      if (!is_visited[j] && mark[j] < min_dist) {
        index = j;
        min_dist = mark[j];
      }
    }
    is_visited[index] = true;
    for (int j = 0; j < graph.get_size(); j++) {
      if (!is_visited[j] && adj_matrix(index, j) != 0 &&
          adj_matrix(index, j) < mark[j]) {
        mark[j] = adj_matrix(index, j);
        parent[j] = index;
      }
    }
  }
  Matrix<int> result(graph.get_size(), graph.get_size());
  for (int i = 1; i < result.get_row(); ++i) {
    result(i, parent[i]) = result(parent[i], i) = mark[i];
  }
  return result;
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph) {
  AntAlgorithm antAlgo(graph);
  return antAlgo.SolveTSP();
}

}  // namespace s21
