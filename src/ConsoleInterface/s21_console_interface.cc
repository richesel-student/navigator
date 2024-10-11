#include "s21_console_interface.h"

#include <iostream>
#include <vector>

namespace s21 {

void ConsoleInterface::Loop() {
  while (user_choice_ != "q" && user_choice_ != "Q") {
    ShowMainMenu();
    UserMakeChoice();
  }
}

void ConsoleInterface::ShowMainMenu() {
  std::cout << std::endl
            << std::endl
            << "Project A2_SimpleNavigator_v1.0" << std::endl;
  std::cout
      << "To select an action, you need to enter its number from the keyboard"
      << std::endl;
  std::cout << "Plese enter only number from 1 to 7" << std::endl << std::endl;
  std::cout << "1. loading the original graph from a file" << std::endl;
  std::cout << "2. graph traversal in breadth with output of the result to the "
               "console"
            << std::endl;
  std::cout
      << "3. graph traversal in depth with output of the result to the console"
      << std::endl;
  std::cout << "4. searching for the shortest path between any two vertices "
               "and displaying the result to the console"
            << std::endl;
  std::cout
      << "5. searching for the shortest paths between all pairs of vertices in "
         "the graph with the output of the resulting matrix to the console"
      << std::endl;
  std::cout << "6. searching for the minimal spanning tree in the graph with "
               "the output of the resulting adjacency matrix to the console"
            << std::endl;
  std::cout << "7. solving the salesman problem with the output of the "
               "resulting route and its length to the console"
            << std::endl
            << std::endl;
  std::cout << "Press q or Q for quit" << std::endl
            << std::endl
            << std::endl
            << std::endl;
}

void ConsoleInterface::UserMakeChoice() {
  std::cin >> user_choice_;
  try {
    if (user_choice_ == "1") {
      RunLoadingFile();
    } else if (user_choice_ == "2") {
      RunBFS();
    } else if (user_choice_ == "3") {
      RunDFS();
    } else if (user_choice_ == "4") {
      RunShortestPath();
    } else if (user_choice_ == "5") {
      RunShortestPathAll();
    } else if (user_choice_ == "6") {
      RunLeastTree();
    } else if (user_choice_ == "7") {
      RunACO();
    } else {
      std::cout << "Plese enter only number from 1 to 7, or q or Q for quit"
                << std::endl;
    }
  } catch (...) {
    std::cout
        << "You can't do that with with graph, please try with another graph"
        << std::endl;
  }
}

void ConsoleInterface::RunLoadingFile() {
  std::cout << "Plese enter file path (Expamle: DataFiles/fromTask.txt)"
            << std::endl;
  std::string filepath;
  std::cin >> filepath;
  try {
    graph_.LoadGraphFromFile(filepath);
    is_loaded_ = true;
    std::cout << "Graph was successfully uploaded!" << std::endl;
  } catch (...) {
    std::cout << "Your file path or file is not correct" << std::endl;
  }
}

void ConsoleInterface::RunBFS() {
  if (!is_loaded_) {
    std::cout << "Please load the graph first" << std::endl;
  } else {
    GraphAlgorithms graph_algo;
    std::vector<int> res = graph_algo.BreadthFirstSearch(graph_, 1);
    std::cout << "The result of BFS is:" << std::endl;
    for (int vertex : res) {
      std::cout << vertex << " ";
    }
    std::cout << std::endl;
  }
}

void ConsoleInterface::RunDFS() {
  if (!is_loaded_) {
    std::cout << "Please load the graph first" << std::endl;
  } else {
    GraphAlgorithms graph_algo;
    std::vector<int> res = graph_algo.DepthFirstSearch(graph_, 1);
    std::cout << "The result of DFS is:" << std::endl;
    for (int vertex : res) {
      std::cout << vertex << " ";
    }
    std::cout << std::endl;
  }
}

void ConsoleInterface::RunShortestPath() {
  if (!is_loaded_) {
    std::cout << "Please load the graph first" << std::endl;
  } else {
    std::cout << "Please enter two vertixes" << std::endl;
    int start, end;
    std::cin >> start >> end;
    GraphAlgorithms graph_algo;
    int result = graph_algo.GetShortestPathBetweenVertices(graph_, start, end);
    std::cout << "The shortest path is " << result << std::endl;
  }
}

void ConsoleInterface::RunShortestPathAll() {
  if (!is_loaded_) {
    std::cout << "Please load the graph first" << std::endl;
  } else {
    s21::GraphAlgorithms graph_algo;
    Matrix<int> result = graph_algo.GetShortestPathsBetweenAllVertices(graph_);
    for (int i = 0; i < result.get_row(); ++i) {
      for (int j = 0; j < result.get_col(); ++j) {
        std::cout << result(i, j) << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
}

void ConsoleInterface::RunLeastTree() {
  if (!is_loaded_) {
    std::cout << "Please load the graph first" << std::endl;
  } else {
    s21::GraphAlgorithms graph_algo;
    Matrix<int> result = graph_algo.GetLeastSpanningTree(graph_);
    for (int i = 0; i < result.get_row(); ++i) {
      for (int j = 0; j < result.get_col(); ++j) {
        std::cout << result(i, j) << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
}

void s21::ConsoleInterface::RunACO() {
  if (!is_loaded_) {
    std::cout << "Please load the graph first" << std::endl;
  } else {
    s21::GraphAlgorithms graph_algo;
    auto result = graph_algo.SolveTravelingSalesmanProblem(graph_);
    for (size_t i = 0; i < result.vertices.size(); ++i) {
      std::cout << result.vertices[i] << " - ";
    }
    std::cout << std::endl;
    std::cout << "The min distance is " << result.distance << std::endl;
  }
}

}  // namespace s21