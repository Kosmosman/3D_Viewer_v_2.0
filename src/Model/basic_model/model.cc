//
// Created by Joaquina Daeron on 6/21/23.
//

#include "model.h"
#include "../parcer/parcer.h"

namespace s21 {

    Model::Model(std::string file) : filename_{file} {
        SetData();
    };

    void Model::SetData() {
        Parcer p(filename_);
        max_coordinate_ = p.GetMaxCoordinate();
        vertexes_ = p.GetVertexes();
        facets_ = p.GetFacets();
        is_valid_ = p.IsValid();
    };

    Model& Model::operator()(std::string file) {
        filename_ = file;
        SetData();
        return *this;
    }

} // s21