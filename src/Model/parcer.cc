#include "parcer.h"

#include <sstream>

namespace s21 {
Parcer::Parcer(std::string&& str) {
  Close();
  file_.open(str);
};

void Parcer::Parce() {
  std::string str;
  while (file_ >> str) {
    std::stringstream ss(str);
    ss >> str;
    if (str == "v") {
      for (int i = 0; ss >> str; ++i) {
        if (i > 2) is_valid_ = false;
      }
    }
  }
};
};  // namespace s21