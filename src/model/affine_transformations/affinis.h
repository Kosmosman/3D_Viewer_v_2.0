#ifndef CPP4_3D_VIEWER_V2_SRC_MODEL_AFFINE_TRANSFORMATION_AFFINIS_H
#define CPP4_3D_VIEWER_V2_SRC_MODEL_AFFINE_TRANSFORMATION_AFFINIS_H

#include <cmath>
#include <utility>
#include <vector>

namespace s21 {

class Move {
 public:
  virtual void Calculate(std::vector<double>& data, long double change) = 0;
  virtual ~Move() {}
};

class MoveX : public Move {
 public:
  void Calculate(std::vector<double>& data, long double change) override;
};

class MoveY : public Move {
 public:
  void Calculate(std::vector<double>& data, long double change) override;
};

class MoveZ : public Move {
 public:
  void Calculate(std::vector<double>& data, long double change) override;
};

class Rotate {
 public:
  virtual void Calculate(std::vector<double>& data, long double change) = 0;
  virtual ~Rotate() {}
  long double Converter(long double angle) { return angle * acos(-1) / 180.0; }
};

class RotateX : public Rotate {
 public:
  void Calculate(std::vector<double>& data, long double change) override;
};

class RotateY : public Rotate {
 public:
  void Calculate(std::vector<double>& data, long double change) override;
};

class RotateZ : public Rotate {
 public:
  void Calculate(std::vector<double>& data, long double change) override;
};

class Scaling {
 public:
  void Calculate(std::vector<double>& data, long double change);
};

template <class Operation>
class AffinisOperation : public Operation {
 public:
  void MakeCalculate(std::vector<double>& data, long double change) {
    this->Calculate(data, change);
  }
};

}  // namespace s21

#endif  // CPP4_3D_VIEWER_V2_SRC_MODEL_AFFINE_TRANSFORMATION_AFFINIS_H
