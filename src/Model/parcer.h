#ifndef CPP_3D_VIEWER_V2_SRC_MODEL_PARCER_H_
#define CPP_3D_VIEWER_V2_SRC_MODEL_PARCER_H_

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {
class Parcer {
 public:
  Parcer() : file_{}, max_coordinate_{}, vertexes_{}, facets_{} {};
  Parcer(std::string str);
  Parcer(const Parcer& other) = delete;
  Parcer(Parcer&& other) = delete;
  ~Parcer() { Close(); };

  double GetMaxCoordinate() const noexcept { return max_coordinate_; };
  std::vector<double> GetVertexes() const noexcept { return vertexes_; };
  std::vector<double> GetFacets() const noexcept { return facets_; };

 private:
  std::ifstream file_;
  double max_coordinate_;
  std::vector<double> vertexes_;
  std::vector<double> facets_;
  bool is_valid_{true};

  void Close() {
    if (file_.is_open()) file_.close();
  };
  void Parce();
  long GetFileSize(std::string str);
  void ReadVertexes(std::stringstream& ss);
  void ReadFacets(std::stringstream& ss);
};
};  // namespace s21

#endif  // CPP_3D_VIEWER_V2_SRC_MODEL_PARCER_H_