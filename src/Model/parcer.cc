#include "parcer.h"

#include <sys/stat.h>

#include <iostream>

namespace s21 {
// Базовый конструктор, принимает в качестве аргумента название текстового
// файла. Если файл не валидный, то переменная состояния is_valid_ меняет
// значение на false
Parcer::Parcer(std::string&& str) {
  file_.open(str);
  if (file_.is_open()) {
    auto size = GetFileSize(str);
    vertexes_.reserve(size / 2);
    facets_.reserve(size / 2);
    Parce();
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
  while (file_ >> str) {
    std::stringstream ss(str);
    ss >> str;
    try {
      if (str == "v")
        ReadVertexes(ss);
      else if (str == "f")
        ReadFacets(ss);
    } catch (...) {
      is_valid_ = false;
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
  int count = 0;
  std::string str;
  for (count = 0; ss >> str; ++count) {
    if (count > 2) is_valid_ = false;
    vertexes_.push_back(std::stod(str));
  }
  if (count < 3) is_valid_ = false;
};

// Считываем расположение грани. Строку подразбиваем на подстроки с номерами
// вершин.
void Parcer::ReadFacets(std::stringstream& ss) {
  int count = 0;
  std::string substr, num;
  for (count = 0; ss >> substr; ++count) {
    for (auto it = substr.begin(); it != substr.end() && *it != '/'; ++it) {
      num += *it;
    }
    facets_.push_back(std::stoi(num));
    num = "";
  }
  if (count < 2) is_valid_ = false;
};

};  // namespace s21