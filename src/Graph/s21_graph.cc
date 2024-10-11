#include "s21_graph.h"

#include <fstream>
#include <iostream>

namespace s21 {

void Graph::LoadGraphFromFile(std::string filename) {
  std::fstream file_obj{filename};
  if (file_obj.is_open()) {
    file_obj >> size_;
    if (size_ > 0) {
      Matrix<int> temp_graph(size_, size_);
      for (int i = 0; i < size_; ++i) {
        for (int j = 0; j < size_; ++j) {
          std::string temp;
          file_obj >> temp;
          temp_graph(i, j) = stoi(temp);
        }
      }
      adjacency_matrix_ = std::move(temp_graph);
      CheckDirected();
      file_obj.close();
    } else {
      file_obj.close();
      throw "File format is not correct";
    }
    file_obj.close();
  } else {
    throw "Unable to open file!";
  }
}

void Graph::CheckDirected() {
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      if (adjacency_matrix_(i, j) != adjacency_matrix_(j, i)) {
        is_directed_ = true;
      }
    }
  }
}

void Graph::ExportGraphToDot(std::string filename) {
  std::ofstream file_obj{filename};
  if (file_obj.is_open()) {
    file_obj << "graph {" << std::endl;
    for (int i = 0; i < size_; ++i) {
      for (int j = i + 1; j < size_; ++j) {
        if (adjacency_matrix_(i, j) != 0) {
          if (is_directed_) {
            file_obj << "  " << i + 1 << " -> " << j + 1 << ";" << std::endl;
          } else {
            file_obj << "  " << i + 1 << " -- " << j + 1 << ";" << std::endl;
          }
        }
      }
    }
    file_obj << "}" << std::endl;
    file_obj.close();
  } else {
    throw "Unable to write in file";
  }
}

std::vector<int> Graph::get_neighboring_vertices(int vertex) {
  std::vector<int> neighboring_vertices;
  for (int i = 0; i < size_; ++i) {
    if (adjacency_matrix_(vertex - 1, i)) {
      neighboring_vertices.push_back(i + 1);
    }
  }
  return neighboring_vertices;
}

}  // namespace s21