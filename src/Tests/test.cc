#include <list>
#include <vector>

#include "../Containers/s21_list.hpp"
#include "../Graph/s21_graph.h"
#include "../GraphAlgorithms/s21_graphalgorithms.h"
#include "../Matrix/matrix.h"
#include "gtest/gtest.h"

using namespace s21;

TEST(Graph, check_without_load) {
  Graph graph;
  GraphAlgorithms algo;
  auto res = algo.BreadthFirstSearch(graph, 1);
  EXPECT_EQ(res[0], 1);
  EXPECT_EQ(res.size(), 1);
}

TEST(Graph, check_without_load2) {
  Graph graph;
  GraphAlgorithms algo;
  auto res = algo.DepthFirstSearch(graph, 1);
  EXPECT_EQ(res[0], 1);
  EXPECT_EQ(res.size(), 1);
}

TEST(Graph, check_without_load3) {
  Graph graph;
  GraphAlgorithms algo;
  auto res = algo.GetShortestPathBetweenVertices(graph, 1, 1);
  EXPECT_EQ(res, 0);
}

TEST(Graph, check_without_load4) {
  Graph graph;
  GraphAlgorithms algo;
  auto res = algo.GetShortestPathsBetweenAllVertices(graph);
  EXPECT_EQ(res(0, 0), 0);
  EXPECT_EQ(res.get_col(), 1);
}

TEST(Graph, check_without_load5) {
  Graph graph;
  GraphAlgorithms algo;
  auto res = algo.GetLeastSpanningTree(graph);
  EXPECT_EQ(res(0, 0), 0);
  EXPECT_EQ(res.get_col(), 1);
}

TEST(Graph, check_without_load6) {
  Graph graph;
  GraphAlgorithms algo;
  EXPECT_ANY_THROW(algo.SolveTravelingSalesmanProblem(graph));
}

TEST(Graph, normal_load) {
  Graph graph;
  graph.LoadGraphFromFile("DataFiles/fromTask.txt");
  EXPECT_EQ(graph.get_size(), 11);
}

TEST(Graph, load_exception) {
  Graph graph;
  EXPECT_ANY_THROW(graph.LoadGraphFromFile("DataFiles/NonExistentFile.txt"));
}

TEST(Graph, load_exception2) {
  Graph graph;
  EXPECT_ANY_THROW(graph.LoadGraphFromFile("DataFiles/myFile"));
}
TEST(Graph, normal_export) {
  Graph graph;
  graph.LoadGraphFromFile("DataFiles/fromTask.txt");
  graph.ExportGraphToDot("DataFiles/ToDot.txt");
  EXPECT_EQ(graph.get_size(), 11);
}

TEST(Graph, normal_export2) {
  Graph graph;
  graph.LoadGraphFromFile("DataFiles/Floyd.txt");
  graph.ExportGraphToDot("DataFiles/FloydToDot.txt");
  EXPECT_EQ(graph.get_size(), 4);
}

TEST(Graph, export_throw) {
  Graph graph;
  graph.LoadGraphFromFile("DataFiles/fromTask.txt");
  EXPECT_ANY_THROW(graph.ExportGraphToDot("NotExistentFolder/file.txt"));
}

TEST(GraphAlgo, DFS_normal) {
  Graph graph;
  graph.LoadGraphFromFile("DataFiles/fromTask.txt");
  GraphAlgorithms algo;
  std::vector result = algo.DepthFirstSearch(graph, 1);
  EXPECT_EQ(result.size(), 11);
}

TEST(GraphAlgo, BFS_normal) {
  Graph graph;
  graph.LoadGraphFromFile("DataFiles/fromTask.txt");
  GraphAlgorithms algo;
  std::vector result = algo.BreadthFirstSearch(graph, 1);
  EXPECT_EQ(result.size(), 11);
}

TEST(GraphAlgo, DFS_DFS) {
  Graph graph;
  graph.LoadGraphFromFile("DataFiles/DFSandBFS.txt");
  GraphAlgorithms algo;
  std::vector result = algo.DepthFirstSearch(graph, 1);
  EXPECT_EQ(result.size(), 7);
  EXPECT_EQ(result[0], 1);
  EXPECT_EQ(result[1], 3);
  EXPECT_EQ(result[2], 6);
  EXPECT_EQ(result[3], 7);
  EXPECT_EQ(result[4], 5);
  EXPECT_EQ(result[5], 4);
  EXPECT_EQ(result[6], 2);
}

TEST(GraphAlgo, BFS_BFS) {
  Graph graph;
  graph.LoadGraphFromFile("DataFiles/DFSandBFS.txt");
  GraphAlgorithms algo;
  std::vector result = algo.BreadthFirstSearch(graph, 1);
  EXPECT_EQ(result.size(), 7);
  EXPECT_EQ(result[0], 1);
  EXPECT_EQ(result[1], 2);
  EXPECT_EQ(result[2], 3);
  EXPECT_EQ(result[3], 4);
  EXPECT_EQ(result[4], 5);
  EXPECT_EQ(result[5], 6);
  EXPECT_EQ(result[6], 7);
}

TEST(GraphAlgo, BFS_throw) {
  Graph graph;
  graph.LoadGraphFromFile("DataFiles/fromTask.txt");
  GraphAlgorithms algo;
  EXPECT_ANY_THROW(algo.BreadthFirstSearch(graph, 15));
}

TEST(GraphAlgo, BFS_throw_negative) {
  Graph graph;
  graph.LoadGraphFromFile("DataFiles/fromTask.txt");
  GraphAlgorithms algo;
  EXPECT_ANY_THROW(algo.BreadthFirstSearch(graph, -8));
}

TEST(GraphAlgo, DFS_throw) {
  Graph graph;
  graph.LoadGraphFromFile("DataFiles/fromTask.txt");
  GraphAlgorithms algo;
  EXPECT_ANY_THROW(algo.DepthFirstSearch(graph, 15));
}

TEST(GraphAlgo, DFS_throw_negative) {
  Graph graph;
  graph.LoadGraphFromFile("DataFiles/fromTask.txt");
  GraphAlgorithms algo;
  EXPECT_ANY_THROW(algo.DepthFirstSearch(graph, -8));
}

TEST(GraphAlgo, Dijkstra_throw_negative) {
  Graph graph;
  graph.LoadGraphFromFile("DataFiles/fromTask.txt");
  GraphAlgorithms algo;
  EXPECT_ANY_THROW(algo.GetShortestPathBetweenVertices(graph, 1, -9));
}

TEST(GraphAlgo, Dijkstra_throw) {
  Graph graph;
  graph.LoadGraphFromFile("DataFiles/fromTask.txt");
  GraphAlgorithms algo;
  EXPECT_ANY_THROW(algo.GetShortestPathBetweenVertices(graph, 1, 19));
}

TEST(GraphAlgo, Dijkstra_throw2) {
  Graph graph;
  graph.LoadGraphFromFile("DataFiles/Disconected.txt");
  GraphAlgorithms algo;
  EXPECT_ANY_THROW(algo.GetShortestPathBetweenVertices(graph, 1, 19));
}

TEST(GraphAlgo, Dijkstra_normal) {
  Graph graph;
  graph.LoadGraphFromFile("DataFiles/fromTask.txt");
  GraphAlgorithms algo;
  EXPECT_EQ(algo.GetShortestPathBetweenVertices(graph, 1, 9), 4);
}

TEST(GraphAlgo, Dijkstra_normal2) {
  Graph graph;
  graph.LoadGraphFromFile("DataFiles/fromTask.txt");
  GraphAlgorithms algo;
  EXPECT_EQ(algo.GetShortestPathBetweenVertices(graph, 11, 7), 84);
}

TEST(GraphAlgo, Floyd_Warshall) {
  Graph graph;
  graph.LoadGraphFromFile("DataFiles/Floyd.txt");
  GraphAlgorithms algo;
  auto res = algo.GetShortestPathsBetweenAllVertices(graph);
  EXPECT_EQ(res(0, 0), 0);
  EXPECT_EQ(res(0, 1), 5);
  EXPECT_EQ(res(0, 2), 3);
  EXPECT_EQ(res(0, 3), 8);
  EXPECT_EQ(res(1, 0), -5);
  EXPECT_EQ(res(1, 1), 0);
  EXPECT_EQ(res(1, 2), -2);
  EXPECT_EQ(res(1, 3), 3);
  EXPECT_EQ(res(2, 0), -3);
  EXPECT_EQ(res(2, 1), 2);
  EXPECT_EQ(res(2, 2), 0);
  EXPECT_EQ(res(2, 3), 5);
  EXPECT_EQ(res(3, 0), -8);
  EXPECT_EQ(res(3, 1), -3);
  EXPECT_EQ(res(3, 2), -5);
  EXPECT_EQ(res(3, 3), 0);
}

TEST(GraphAlgo, Spaning_tree) {
  Graph graph;
  graph.LoadGraphFromFile("DataFiles/fromTask.txt");
  GraphAlgorithms algo;
  auto res = algo.GetLeastSpanningTree(graph);
  int weight_spannin_tree = 0;
  for (int i = 0; i < 11; ++i) {
    for (int j = 0; j < 11; ++j) {
      weight_spannin_tree += res(i, j);
    }
  }
  weight_spannin_tree /= 2;
  EXPECT_EQ(weight_spannin_tree, 150);
}

TEST(GraphAlgo, ACO) {
  Graph graph;
  graph.LoadGraphFromFile("DataFiles/fromTask.txt");
  GraphAlgorithms algo;
  auto res = algo.SolveTravelingSalesmanProblem(graph);
  EXPECT_EQ(res.distance, 253);
}

TEST(GraphAlgo, ACO_throw) {
  Graph graph;
  graph.LoadGraphFromFile("DataFiles/Floyd.txt");
  GraphAlgorithms algo;
  EXPECT_ANY_THROW(algo.SolveTravelingSalesmanProblem(graph));
}

TEST(ListTest, container_test) {
  list<int> l_int{1, 2, 3, 4, 5, 6, 7};
  std::list<int> std_l_int{1, 2, 3, 4, 5, 6, 7};
  l_int.clear();
  std_l_int.clear();
  EXPECT_TRUE(l_int.size() == std_l_int.size());
  l_int.clear();
  std_l_int.clear();
  EXPECT_TRUE(l_int.size() == std_l_int.size());
  l_int.push_front(15);
  std_l_int.push_front(15);
  EXPECT_TRUE(l_int.size() == std_l_int.size());
  EXPECT_TRUE(l_int.front() == std_l_int.front());
  l_int.push_front(20);
  std_l_int.push_front(20);
  EXPECT_TRUE(l_int.size() == std_l_int.size());
  EXPECT_TRUE(l_int.front() == std_l_int.front());
}

TEST(test_set, throw_construcor) { EXPECT_ANY_THROW(Matrix<int> a(1, 0)); }

TEST(test_set, throw_getter) {
  Matrix<int> a(1, 1);
  EXPECT_ANY_THROW(a(2, 2));
}

TEST(test_set, operator_eq) {
  Matrix<int> a(2, 2);
  Matrix<int> b(2, 2);
  a = a;
  EXPECT_TRUE(a == a);
  b(0, 0) = 1;
  EXPECT_EQ(a == b, false);
}

TEST(test_set, operator_eq2) {
  Matrix<int> a(2, 2);
  Matrix<int> b(2, 2);
  b(0, 0) = 1;
  a = b;
  EXPECT_EQ(a(0, 0), 1);
}

TEST(test_set, operator_eq_with_move) {
  Matrix<int> a(2, 2);
  a = std::move(a);
  EXPECT_TRUE(a == a);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
