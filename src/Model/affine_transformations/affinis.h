//
// Created by Joaquina Daeron on 6/21/23.
//

#ifndef SRC_AFFINIS_H
#define SRC_AFFINIS_H

#include <utility>
#include <vector>

namespace s21 {

class MoveX {
 public:
  void Calculate(std::vector<double>& data, long double change);
};

class MoveY {
 public:
  void Calculate(std::vector<double>& data, long double change);
};

class MoveZ {
 public:
  void Calculate(std::vector<double>& data, long double change);
};

class RotateX {
 public:
  void Calculate(std::vector<double>& data, long double change);
};

class RotateY {
 public:
  void Calculate(std::vector<double>& data, long double change);
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
