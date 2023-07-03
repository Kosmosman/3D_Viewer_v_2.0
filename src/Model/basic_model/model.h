//
// Created by Joaquina Daeron on 6/21/23.
//

#ifndef SRC_MODEL_H
#define SRC_MODEL_H

#include <string>
#include <vector>

namespace s21 {

class Model {
 public:
  Model(){};
  explicit Model(std::string filename);
  double GetMaxCoordinate() const noexcept { return max_coordinate_; };
  std::vector<double> GetVertexes() const noexcept { return vertexes_; };
  std::vector<double> GetFacets() const noexcept { return facets_; };
  bool IsValid() const noexcept { return is_valid_; };
  Model& operator()(std::string file);

 private:
  std::string filename_{};
  double max_coordinate_{};
  std::vector<double> vertexes_{};
  std::vector<double> facets_{};
  bool is_valid_{};

  void SetData();
};

}  // namespace s21

#endif  // SRC_MODEL_H
