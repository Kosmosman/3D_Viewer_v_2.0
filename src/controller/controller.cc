//
// Created by joaquind on 03.07.23.
//

#include "controller.h"

namespace s21 {
void Controller::InitModel(std::string file) { model_(file); };
double Controller::MaxCoordinate() { return model_.GetMaxCoordinate(); };
double* Controller::Vertexes() { return model_.GetVertexes().data(); };
double* Controller::Facets() { return model_.GetFacets().data(); };
int Controller::CountOfFacetsLines() { return model_.GetFacets().size(); };
int Controller::CountOfVertexes() { return model_.GetVertexes().size() / 3; };
}  // namespace s21