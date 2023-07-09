#include "model.h"

#include "../parcer/parcer.h"

namespace s21 {

Model::Model(std::string file) : filename_{file} { SetData(); }

Model& Model::operator()(std::string file) {
  filename_ = file;
  SetData();
  return *this;
}

void Model::SetData() {
  Parcer p(filename_);
  max_coordinate_ = p.GetMaxCoordinate();
  count_of_facets_ = p.GetCountOfFacets();
  vertexes_ = start_vertexes_ = p.GetVertexes();
  facets_ = p.GetFacets();
  is_valid_ = p.IsValid();
  polygon_size_ = p.GetPolygonSize();
}

}  // namespace s21