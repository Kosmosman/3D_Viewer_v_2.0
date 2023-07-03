//
// Created by Joaquina Daeron on 6/21/23.
//

#include "model.h"
#include "../parcer/parcer.h"

namespace s21 {

    Model::Model(std::string file) : filename_{file} {
        Parcer p(file);
        max_coordinate_ = p.GetMaxCoordinate();
        vertexes_ = p.GetVertexes();
        facets_ = p.GetFacets();
        is_valid_ = p.IsValid();
    };

} // s21