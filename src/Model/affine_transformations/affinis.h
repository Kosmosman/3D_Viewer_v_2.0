//
// Created by Joaquina Daeron on 6/21/23.
//

#ifndef SRC_AFFINIS_H
#define SRC_AFFINIS_H

#include <vector>
#include <utility>

namespace s21 {

    using vec_iter = std::vector<double>::iterator;

    class Move {
    public:
        void Calculate(vec_iter start, vec_iter end, const std::pair<int, int>& values);
        ~Move(){};
    };

    class Rotate {
    public:
        void Calculate(vec_iter start, vec_iter end, const std::pair<int, int>& values);
        ~Rotate(){};
    };

    class Scaling {
    public:
        void Calculate(vec_iter start, vec_iter end, const std::pair<int, int>& values);
        ~Scaling(){};
    };

    template <class Operation>
    class Affinis : public Operation {
    public:
        Affinis(std::size_t size);
        void MakeCalculate(std::vector<double>& data, const std::pair<int, int>& values);

    private:
        std::vector<std::thread> threads_pool_;
        std::size_t min_thread_elem_;
    };

} // s21

#endif //SRC_AFFINIS_H
