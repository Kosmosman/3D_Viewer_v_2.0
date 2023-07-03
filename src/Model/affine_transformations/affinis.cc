//
// Created by Joaquina Daeron on 6/21/23.
//

#include "affinis.h"

#include <cmath>
#include <iostream>

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
  change = s21_degres_to_radians(change);
  long double y{}, z{};
  for (auto i = start; i < end; i += 3) {
    y = data[i + 1];
    z = data[i + 2];
    data[i + 1] = y * cosl(change) + z * sinl(change);
    data[i + 2] = -y * sinl(change) + z * cosl(change);
  }
}

void RotateY::Calculate(std::vector<double>& data, long double change) {
  change = s21_degres_to_radians(change);
  long double y{}, z{};
  for (auto i = start; i < end; i += 3) {
    y = data[i];
    z = data[i + 2];
    data[i] = x * cosl(change) + z * sinl(change);
    data[i + 2] = -x * sinl(change) + z * cosl(change);
  }
}

void RotateZ::Calculate(std::vector<double>& data, long double change) {
  change = s21_degres_to_radians(change);
  long double y{}, z{};
  for (auto i = start; i < end; i += 3) {
    y = data[i];
    z = data[i + 1];
    data[i] = x * cosl(change) - y * sinl(change);
    data[i + 1] = x * sinl(change) + y * cosl(change);
  }
}

void Scaling::Calculate(std::vector<double>& data, long double change) {
  for (auto i = start; i < end; i += 3) {
    data[i] *= change;
  }
}

template <class Operator>
void Affinis<Operator>::MakeCalculate(std::vector<double>& data,
                                      long double change) {}

long double Converter(long double change) { return change * acos(-1) / 180.0; }

}  // s21

int main() {
  std::cout << std::thread::hardware_concurrency() << std::endl;
  return 0;
}

void Rotate::Calculate(vec_iter start, vec_iter end,
                       const std::pair<int, int>& values) {}

void Scaling::Calculate(vec_iter start, vec_iter end,
                        const std::pair<int, int>& values) {}

template <class Operator>
Affinis<Operator>::Affinis(std::size_t size) : min_thread_elem_{30} {
  std::size_t max_count_of_threads =
      (size + min_thread_elem_ - 1) / min_thread_elem_;
  std::size_t hardware_threads = std::thread::hardware_concurrency();
  std::size_t count_of_threads = std::min(
      hardware_threads != 0 ? hardware_threads : 3, max_count_of_threads);
  if (count_of_threads) min_thread_elem_ = size / count_of_threads;
}

template <class Operator>
void Affinis<Operator>::MakeCalculate(std::vector<double>& data,
                                      const std::pair<int, int>& values) {
  std::vector<std::thread> threads;
  threads.reserve(1);
}

}  // namespace s21

int main() {
  std::cout << std::thread::hardware_concurrency() << std::endl;
  return 0;
}
