//
// Created by Joaquina Daeron on 6/21/23.
//

#include "affinis.h"

namespace s21 {

    void Move::Calculate(std::vector& data, const std::pair<int, int>& values) {
        for (auto i = data.begin(); i < data.end(); std::advance(i, 3))
            i += values.first - values.second;
    }

    void Rotate::Calculate(std::vector& data, const std::pair<int, int>& values) {

    }

    void Scaling::Calculate(std::vector& data, const std::pair<int, int>& values) {

    }
} // s21