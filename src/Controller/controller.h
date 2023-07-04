//
// Created by joaquind on 03.07.23.
//

#ifndef SRC_CONTROLLER_H
#define SRC_CONTROLLER_H

#include "../Model/basic_model/model.h"

#include <string>

namespace s21 {

    class Controller {
    public:
        Controller() = default;
        void InitModel(std::string file) { model_(file); };
        double MaxCoordinate() { return model_.GetMaxCoordinate(); };
        double* Vertexes() { return model_.GetVertexes().data; };
        double* Facets() { return model_.GetFacets().data; };
        int CountOfFacets() {return model_.GetCountOfVertex(); };
        int CountOfVertexes() { return model_.GetVertexes().size() / 3; };
    private:
        Model model_;
    };

} // s21

#endif //SRC_CONTROLLER_H
