#ifndef CPP_3D_VIEWER_V2_SRC_MODEL_PARCER_H_
#define CPP_3D_VIEWER_V2_SRC_MODEL_PARCER_H_

#include <fstream>
#include <string>
#include <vector>

namespace s21 {
class Parcer {
 public:
  Parcer() = default;
  Parcer(std::string&& str);
  Parcer(const Parcer& other) = delete;
  Parcer(Parcer&& other){};
  ~Parcer() { Close(); };

  double GetMaxCoordinate() const {};
  std::vector<double> GetVertexes() const {};
  std::vector<double> GetFacets() const {};

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
};
};  // namespace s21

#endif  // CPP_3D_VIEWER_V2_SRC_MODEL_PARCER_H_