//
// Created by Joaquina Daeron on 6/21/23.
//

#include "model.h"

#include "../parcer/parcer.h"

namespace s21 {

Model::Model(std::string file) : filename_{file} {
  Parcer p(file);
  double max_coordinate_ = p.GetMaxCoordinate();
  std::vector<double> vertexes_ = p.GetVertexes();
  std::vector<double> facets_ = p.GetFacets();
  bool is_valid_ = p.IsValid();
};

}  // namespace s21