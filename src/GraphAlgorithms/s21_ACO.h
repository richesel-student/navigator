#ifndef A2_SIMPLE_NAVIGATOR_GRAPHALGORITHMS_ACO_H
#define A2_SIMPLE_NAVIGATOR_GRAPHALGORITHMS_ACO_H

#include "../Graph/s21_graph.h"
#include "../Matrix/matrix.h"
#include "s21_graphalgorithms.h"

namespace s21 {

struct Ant {
  int current_vertex_;
  std::vector<int> visited_vertex_;
  int path_length_;
  Ant() : current_vertex_(0), path_length_(0) { visited_vertex_.push_back(0); }
};

class AntAlgorithm {
 public:
  explicit AntAlgorithm(Graph &graph, double alpha = 0.7, double beta = 1.5,
                        double rho = 0.2, double q = 100,
                        int max_iterators = 5000);
  TsmResult SolveTSP();

 private:
  void InitDistanceMatrix();
  void InitPheromoneMatrix();
  void AntCreation();
  void ColonyRun();
  int ChooseNextVertex(Ant &ant);
  void PheromonUpdate();
  Graph graph_;
  int size_;
  std::vector<Ant> ant_colony_;
  Matrix<int> distance_;
  Matrix<double> pheromone_;
  double alpha_;
  double beta_;
  double rho_;
  double q_;
  int max_iterators_;
  TsmResult optimal_tour_;
};

}  // namespace s21
#endif  //  A2_SIMPLE_NAVIGATOR_GRAPHALGORITHMS_ACO_H