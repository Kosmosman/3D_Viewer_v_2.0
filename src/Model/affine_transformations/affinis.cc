//
// Created by Joaquina Daeron on 6/21/23.
//

#include "affinis.h"

#include <algorithm>
#include <iostream>
#include <thread>

namespace s21 {

    void Move::Calculate(vec_iter start, vec_iter end, const std::pair<int, int>& values) {
        for (auto i = start; i < end; std::advance(i, 3))
            *i += values.first - values.second;
    }

    void Rotate::Calculate(vec_iter start, vec_iter end, const std::pair<int, int>& values) {

    }

    void Scaling::Calculate(vec_iter start, vec_iter end, const std::pair<int, int>& values) {

    }


    template <class Operator>
    Affinis<Operator>::Affinis(std::size_t size) : min_thread_elem_{30}  {
        std::size_t max_count_of_threads = (size + min_thread_elem_ - 1) / min_thread_elem_;
        std::size_t hardware_threads = std::thread::hardware_concurrency();
        std::size_t count_of_threads = std::min(hardware_threads != 0 ? hardware_threads : 3, max_count_of_threads);
        if (count_of_threads) min_thread_elem_ = size / count_of_threads;
    }

    template <class Operator>
    void Affinis<Operator>::MakeCalculate(std::vector<double>& data, const std::pair<int, int> &values) {


        std::vector<std::thread> threads;
        threads.reserve(1);
    }

} // s21

int main() {
    std::cout << std::thread::hardware_concurrency() << std::endl;
    return 0;
}

