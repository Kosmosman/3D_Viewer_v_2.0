#include "parcer.h"

#include <sys/stat.h>

#include <cmath>
#include <iostream>

namespace s21 {
// Базовый конструктор, принимает в качестве аргумента название текстового
// файла. Если файл не валидный, то переменная состояния is_valid_ меняет
// значение на false
Parcer::Parcer(std::string str) {
  file_.open(str);
  if (file_.is_open()) {
    auto size = GetFileSize(str);
    vertexes_.reserve(size / 3);
    facets_.reserve(size / 2);
    Parce();
    Close();
  } else {
    is_valid_ = false;
  }
};

// Метод Parce в которм происходит основной парсин файла. Построчное чтение,
// строка передается в поток, где разделяется по пробелам. В зависимости от
// перовго аргумента, оно воспринимается как вершина или грань, после чего
// вызываются соответствующие методы их валидации и обработок. Операторы
// обработки исключений стоят для случаев некорретных данных в .obj файле.
void Parcer::Parce() {
  std::string str;
  while (getline(file_, str) && is_valid_) {
    std::stringstream ss(str);
    ss >> str;
    try {
      if (str == "v") {
        ReadVertexes(ss);
      } else if (str == "f") {
        ReadFacets(ss);
        ++count_of_facets_;
      }
    } catch (...) {
      is_valid_ = false;
      ResetValues();
      std::cout << "Incorrect data" << std::endl;
    }
  }
};

// Получение размера файла для предварительного резервирования векторов под
// массивы vertexes_ и facets_. Это сделано для предотвращения перевыделения
// памяти при добавлении элементов в вектора и выделения излишней памяти.
long Parcer::GetFileSize(std::string str) {
  struct stat stat_buf;
  int rc = stat(str.c_str(), &stat_buf);
  return rc == 0 ? stat_buf.st_size : -1;
}

// Считываем координаты вершины. По ТЗ их будет 3, без учета компонента w. Если
// чисел в строке больше или меньше трёх - файл некорректный
void Parcer::ReadVertexes(std::stringstream& ss) {
  int count{};
  double num{};
  for (count = 0; ss >> num; ++count) {
    if (count > 2) is_valid_ = false;
    vertexes_.push_back(num);
    max_coordinate_ = fabs(num) > fabs(max_coordinate_) ? num : max_coordinate_;
  }
  if (count < 3) {
      is_valid_ = false;
      ResetValues();
    }
};

// Считываем расположение грани. Строку подразбиваем на подстроки с номерами
// вершин. Мы создаем массив с закольцованными полигонами, поэтому на один
// полигон выделяется х2 вершин.
void Parcer::ReadFacets(std::stringstream& ss) {
  int count{};
  unsigned int num_dbl{};
  std::string substr, num, first;
  for (count = 0; ss >> substr; ++count) {
    for (auto it = substr.begin(); it != substr.end() && *it != '/'; ++it) {
      num += *it;
    }
    num_dbl = std::stoi(num) - 1;
    facets_.push_back(num_dbl);
    if (count)
      facets_.push_back(num_dbl);
    else
      first = num;
    num = "";
  }
  if (count < 2) {
      is_valid_ = false;
      ResetValues();
  } else {
      facets_.push_back(std::stoi(first) - 1);
      polygon_size_ += count * 2;
  }
};

void Parcer::ResetValues() {
    max_coordinate_ = 0;
    vertexes_.clear();
    facets_.clear();
    is_valid_ = false;
    count_of_facets_ = 0;
    polygon_size_ = 0;
}

};  // namespace s21