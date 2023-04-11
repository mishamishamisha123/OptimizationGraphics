//
// Created by misha on 17.11.2021.
//

#ifndef BIGPROJECTFUNCOPTIMIZE_OPTMETHOD_H
#define BIGPROJECTFUNCOPTIMIZE_OPTMETHOD_H
#include "Function.h"
#include "Area.h"
#include "StopCrit.h"
using namespace std;

class OptMethod {
public:
    virtual double optimize(Function *f, StopCrit *sc, Area *a, std::vector<double> start) = 0;
    std::vector<std::vector<double>> points;
};

class RandomSearch : public OptMethod {
    double p{}, delta{}, alpha{};
public:
    explicit RandomSearch(double p1 = 0.7, double delta1 = 0.01, double alpha = 0.5);
    double optimize(Function *f, StopCrit *sc, Area *a, std::vector<double> start) override;
};

class Newton : public OptMethod {
    double p{}, delta{}, alpha{};
public:
    Newton();
    double optimize(Function *f, StopCrit *sc, Area *a, std::vector<double> start) override;
    std::vector<double> nextPoint(std::vector<double> a, Function *f);
    std::vector<std::vector<double>> inverse_matrix(std::vector<std::vector<double>> matrix);
};

#endif //BIGPROJECTFUNCOPTIMIZE_OPTMETHOD_H
