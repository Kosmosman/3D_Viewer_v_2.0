//
// Created by Joaquina Daeron on 6/21/23.
//

#ifndef SRC_AFFINIS_H
#define SRC_AFFINIS_H

#include <utility>
#include <vector>

namespace s21 {

class Move {
 public:
  virtual void Calculate(std::vector<double>& data, long double change) = 0;
  virtual ~Move(){};
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

class RotateX {
 public:
  void Calculate(std::vector<double>& data, long double change);
};

class Rotate {
  virtual void Calculate(std::vector<double>& data, long double change) = 0;
  virtual ~Rotate(){};
};

class RotateX : public Rotate {
 public:
  void Calculate(std::vector<double>& data, long double change) override;
};

class RotateZ {
 public:
  void Calculate(std::vector<double>& data, long double change);
};

class Scaling {
 public:
  void Calculate(std::vector<double>& data, long double change);
};

template <class Operation>
class Affinis : public Operation {
 public:
  void MakeCalculate(std::vector<double>& data, long double change);
};

}  // namespace s21

#endif  // SRC_AFFINIS_H
