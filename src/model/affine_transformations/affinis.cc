#include "affinis.h"

namespace s21 {

void MoveX::Calculate(std::vector<double>& data, long double change) {
  for (auto i = data.begin(); i < data.end(); i += 3) *i += change;
}

void MoveY::Calculate(std::vector<double>& data, long double change) {
  for (auto i = data.begin() + 1; i < data.end(); i += 3) *i += change;
}

void MoveZ::Calculate(std::vector<double>& data, long double change) {
  for (auto i = data.begin() + 2; i < data.end(); i += 3) *i += change;
}

void RotateX::Calculate(std::vector<double>& data, long double change) {
  change = Converter(change);
  long double y{}, z{};
  for (auto i = data.begin(); i < data.end(); i += 3) {
    y = *(i + 1);
    z = *(i + 2);
    *(i + 1) = y * cosl(change) + z * sinl(change);
    *(i + 2) = -y * sinl(change) + z * cosl(change);
  }
}

void RotateY::Calculate(std::vector<double>& data, long double change) {
  change = Converter(change);
  long double x{}, z{};
  for (auto i = data.begin(); i < data.end(); i += 3) {
    x = *i;
    z = *(i + 2);
    *i = x * cosl(change) + z * sinl(change);
    *(i + 2) = -x * sinl(change) + z * cosl(change);
  }
}

void RotateZ::Calculate(std::vector<double>& data, long double change) {
  change = Converter(change);
  long double x{}, y{};
  for (auto i = data.begin(); i < data.end(); i += 3) {
    x = *i;
    y = *(i + 1);
    *i = x * cosl(change) - y * sinl(change);
    *(i + 1) = x * sinl(change) + y * cosl(change);
  }
}

void Scaling::Calculate(std::vector<double>& data, long double change) {
  for (auto i = data.begin(); i < data.end(); ++i) {
    *i *= change;
  }
}

}  // namespace s21
