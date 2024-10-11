#ifndef A2_SIMPLE_NAVIGATOR_CONSOLEINTERFACE_CONSOLEINTERFACE_H
#define A2_SIMPLE_NAVIGATOR_CONSOLEINTERFACE_CONSOLEINTERFACE_H

#include "../Graph/s21_graph.h"
#include "../GraphAlgorithms/s21_graphalgorithms.h"

namespace s21 {

class ConsoleInterface {
 public:
  ConsoleInterface() : user_choice_("") {
    is_loaded_ = false;
    Loop();
  }

 private:
  void Loop();
  void ShowMainMenu();
  void UserMakeChoice();
  void RunLoadingFile();
  void RunBFS();
  void RunDFS();
  void RunShortestPath();
  void RunShortestPathAll();
  void RunLeastTree();
  void RunACO();
  std::string user_choice_;
  bool is_loaded_;
  Graph graph_;
};

}  // namespace s21
#endif  //  A2_SIMPLE_NAVIGATOR_CONSOLEINTERFACE_CONSOLEINTERFACE_H