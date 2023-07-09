#ifndef CPP_3D_VIEWER_V2_SRC_MODEL_PARCER_PARCER_H_
#define CPP_3D_VIEWER_V2_SRC_MODEL_PARCER_PARCER_H_

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {

class Parcer {
 public:
  explicit Parcer(std::string str);
  Parcer(const Parcer& other) = delete;
  Parcer& operator=(const Parcer& other) = delete;

  double GetMaxCoordinate() const noexcept { return max_coordinate_; };
  std::vector<double> GetVertexes() const noexcept { return vertexes_; };
  std::vector<unsigned int> GetFacets() const noexcept { return facets_; };
  std::size_t GetCountOfFacets() const noexcept { return count_of_facets_; }
  std::size_t GetPolygonSize() const noexcept { return polygon_size_; };
  bool IsValid() const noexcept { return is_valid_; };

 private:
  std::ifstream file_{};
  double max_coordinate_{};
  std::vector<double> vertexes_{};
  std::vector<unsigned int> facets_{};
  bool is_valid_{true};
  std::size_t count_of_facets_{};
  std::size_t polygon_size_{};

  void Close() {
    if (file_.is_open()) file_.close();
  };
  void Parce();
  long GetFileSize(std::string str);
  void ReadVertexes(std::stringstream& ss);
  void ReadFacets(std::stringstream& ss);
  void ResetValues();
};

};  // namespace s21

#endif  // CPP_3D_VIEWER_V2_SRC_MODEL_PARCER_PARCER_H_