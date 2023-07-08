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
  Model() = default;
  explicit Model(std::string filename);
  double GetMaxCoordinate() const noexcept { return max_coordinate_; };
  std::vector<double>& GetVertexes() noexcept { return vertexes_; };
  std::vector<unsigned int>& GetFacets() noexcept { return facets_; };
  std::size_t GetCountOfVertex() const noexcept { return count_of_facets_; };
  std::size_t GetPolygonSize() const noexcept { return polygon_size_; };
  bool IsValid() const noexcept { return is_valid_; };
  void BackToStartCoord() { vertexes_ = start_vertexes_; };
  Model& operator()(std::string file);

 private:
  std::string filename_{};
  double max_coordinate_{};
  std::size_t count_of_facets_{};
  std::vector<double> vertexes_{};
  std::vector<double> start_vertexes_{};
  std::vector<unsigned int> facets_{};
  std::size_t polygon_size_{};
  bool is_valid_{};

  void SetData();
};

}  // namespace s21

#endif  // SRC_MODEL_H
