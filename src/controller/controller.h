//
// Created by joaquind on 03.07.23.
//

#ifndef SRC_CONTROLLER_H
#define SRC_CONTROLLER_H

#include <string>

#include "../Model/basic_model/model.h"

namespace s21 {

class Controller {
 public:
  Controller() : model_{} {};
  void InitModel(std::string file);
  double MaxCoordinate();
  double* Vertexes();
  double* Facets();
  int CountOfFacetsLines();
  int CountOfVertexes();

 private:
  Model model_;
};

}  // namespace s21

#endif  // SRC_CONTROLLER_H
