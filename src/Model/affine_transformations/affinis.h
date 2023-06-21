//
// Created by Joaquina Daeron on 6/21/23.
//

#ifndef SRC_AFFINIS_H
#define SRC_AFFINIS_H

#include <vector>
#include <utility>

namespace s21 {

    class Move {
        void Calculate(std::vector& data, const std::pair<int, int>& values) override {};
        ~Move(){};
    };

    class Rotate {
        void Calculate(std::vector& data, const std::pair<int, int>& values) override;
        ~Rotate(){};
    };

    class Scaling {
        void Calculate(std::vector& data, const std::pair<int, int>& values) override;
        ~Scaling(){};
    };

    template <class Operation>
    class Affinis : public Operation {
        void MakeCalculate(std::vector& data, const std::pair<int, int>& values) {
            Calculate(start, end);
        }
    };

} // s21

#endif //SRC_AFFINIS_H
