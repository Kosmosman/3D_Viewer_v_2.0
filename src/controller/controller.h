#ifndef CPP4_3D_VIEWER_V2_SRC_CONTROLLER_CONTROLLER_H
#define CPP4_3D_VIEWER_V2_SRC_CONTROLLER_CONTROLLER_H

#include <string>

#include "../model/affine_transformations/affinis.h"
#include "../model/basic_model/model.h"

namespace s21 {

class Controller {
 public:
  Controller() = default;
  void InitModel(std::string file) { model_(file); };
  double MaxCoordinate() { return model_.GetMaxCoordinate(); };
  double* Vertexes() { return model_.GetVertexes().data(); };
  void Reset() { model_.BackToStartCoord(); };
  unsigned int* Facets() { return model_.GetFacets().data(); };
  int CountOfFacets() { return model_.GetCountOfVertex(); };
  int CountOfVertexes() { return model_.GetVertexes().size() / 3; };
  std::size_t PolygonSize() { return model_.GetPolygonSize(); };

  void MakeMoveX(int value) {
    AffinisOperation<MoveX> op;
    op.MakeCalculate(model_.GetVertexes(), value);
  };
  void MakeMoveY(int value) {
    AffinisOperation<MoveY> op;
    op.MakeCalculate(model_.GetVertexes(), value);
  };
  void MakeMoveZ(int value) {
    AffinisOperation<MoveZ> op;
    op.MakeCalculate(model_.GetVertexes(), value);
  };
  void MakeRotateX(int value) {
    AffinisOperation<RotateX> op;
    op.MakeCalculate(model_.GetVertexes(), value);
  };
  void MakeRotateY(int value) {
    AffinisOperation<RotateY> op;
    op.MakeCalculate(model_.GetVertexes(), value);
  };
  void MakeRotateZ(int value) {
    AffinisOperation<RotateZ> op;
    op.MakeCalculate(model_.GetVertexes(), value);
  };
  void MakeScaling(double value) {
    AffinisOperation<Scaling> op;
    op.MakeCalculate(model_.GetVertexes(), value);
  };

 private:
  Model model_;
};

}  // namespace s21

#endif  // CPP4_3D_VIEWER_V2_SRC_CONTROLLER_CONTROLLER_H
