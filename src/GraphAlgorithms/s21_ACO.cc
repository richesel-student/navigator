#include "s21_ACO.h"

#include <algorithm>
#include <climits>
#include <cmath>
#include <random>

namespace s21 {
AntAlgorithm::AntAlgorithm(Graph &graph, double alpha, double beta, double rho,
                           double q, int max_iterators)
    : graph_(graph) {
  size_ = graph.get_size();
  alpha_ = alpha;
  beta_ = beta;
  rho_ = rho;
  q_ = q;
  max_iterators_ = max_iterators;
  optimal_tour_.distance = INT_MAX;
}

TsmResult AntAlgorithm::SolveTSP() {
  InitDistanceMatrix();
  InitPheromoneMatrix();
  for (int i = 0; i < max_iterators_; ++i) {
    AntCreation();
    ColonyRun();
    PheromonUpdate();
  }
  if (optimal_tour_.distance == INT_MAX) {
    throw std::domain_error(
        "It is impossible to solve the problem with a given graph");
  }
  return optimal_tour_;
}

void AntAlgorithm::InitDistanceMatrix() { distance_ = graph_.get_adj_matrix(); }

void AntAlgorithm::InitPheromoneMatrix() {
  pheromone_ = Matrix<double>(size_, size_);
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      if (distance_(i, j)) {
        pheromone_(i, j) = q_;
      }
    }
  }
}

void AntAlgorithm::AntCreation() {
  ant_colony_.clear();
  for (int i = 0; i < size_; ++i) {
    ant_colony_.push_back(Ant());
  }
}

void AntAlgorithm::ColonyRun() {
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      int vertex = ChooseNextVertex(ant_colony_[i]);
      if (vertex != -1) {
        ant_colony_[i].path_length_ +=
            distance_(ant_colony_[i].current_vertex_, vertex);
        ant_colony_[i].visited_vertex_.push_back(vertex);
        ant_colony_[i].current_vertex_ = vertex;
      }
    }
    if (distance_(ant_colony_[i].current_vertex_, 0)) {
      ant_colony_[i].path_length_ +=
          distance_(ant_colony_[i].current_vertex_, 0);
      ant_colony_[i].visited_vertex_.push_back(0);
    }
  }
}

int AntAlgorithm::ChooseNextVertex(Ant &ant) {
  double sum_probabilities = 0;
  double *probabilities = new double[size_];
  for (int i = 0; i < size_; ++i) {
    if (std::find(ant.visited_vertex_.begin(), ant.visited_vertex_.end(), i) ==
        ant.visited_vertex_.end()) {
      probabilities[i] = pow(pheromone_(ant.current_vertex_, i), alpha_) *
                         pow(10.0 / distance_(ant.current_vertex_, i), beta_);
      sum_probabilities += probabilities[i];
    } else {
      probabilities[i] = 0;
    }
  }
  double random_double = ((double)rand() / (RAND_MAX));
  double cumulative = 0;
  for (int i = 0; i < size_; ++i) {
    cumulative += probabilities[i] / sum_probabilities;
    if (random_double <= cumulative) {
      delete[] probabilities;
      return i;
    }
  }
  delete[] probabilities;
  return -1;
}

void AntAlgorithm::PheromonUpdate() {
  // decrease
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      pheromone_(i, j) = pheromone_(i, j) * (1 - rho_);
    }
  }

  // increase
  for (int i = 0; i < size_; ++i) {
    if ((int)ant_colony_[i].visited_vertex_.size() == size_ + 1) {
      for (int j = 0; j < size_; ++j) {
        int vertex1 = ant_colony_[i].visited_vertex_[j];
        int vertex2 = ant_colony_[i].visited_vertex_[j + 1];
        pheromone_(vertex1, vertex2) += q_ / ant_colony_[i].path_length_;
        pheromone_(vertex2, vertex1) += q_ / ant_colony_[i].path_length_;
      }
      if (optimal_tour_.distance > ant_colony_[i].path_length_) {
        optimal_tour_.distance = ant_colony_[i].path_length_;
        optimal_tour_.vertices = ant_colony_[i].visited_vertex_;
      }
    }
  }
}

}  // namespace s21