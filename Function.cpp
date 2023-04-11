//
// Created by misha on 17.11.2021.
//

#include "Function.h"
#include <cmath>
#include <vector>

int Function::getDim() const {
    return dim;
}

Function::Function(int dim_) : dim(dim_) {}

double Function::derivative(std::vector<double> points, double eps)
{
    double sum = 0;
    for (int i = 0; i < points.size(); ++i) {
        std::vector<double> tmp1 = points, tmp2 = points;
        tmp1[i] += eps;
        tmp2[i] -= eps;
        sum += (eval(tmp1) - eval(tmp2)) / (2 * eps);
    }
    return sum;
}

double Function::derivative(std::vector<double> points, int i, double eps)
{
    std::vector<double> tmp1 = points, tmp2 = points;
    tmp1[i] += eps;
    tmp2[i] -= eps;
    return (eval(tmp1) - eval(tmp2)) / (2 * eps);
}


double Function::derivative2(std::vector<double> points, int i, int j, double eps) {
    std::vector<double> a = points;
    std::vector<double> b = points;
    std::vector<double> c = points;
    std::vector<double> d = points;
    a[i] += eps;
    a[j] += eps;
    b[i] += eps;
    c[j] += eps;

    return (eval(a) - eval(b) - eval(c) + eval(d)) / (pow(eps, 2));
}

Func2d::Func2d() : Function(2) {}

double Func2d::eval(std::vector<double> point) {
    return point[0] * point[0] + point[1] * point[1];
}

Func2d1::Func2d1() : Function(2) {}
double Func2d1::eval(std::vector<double> point) {
    return (1 - point[0]) * (1 - point[0]) + 100 * (point[1] - point[0] * point[0]) * (point[1] - point[0] * point[0]);
}

Func4d::Func4d() : Function(4) {}
double Func4d::eval(std::vector<double> point) {
    return pow(point[0] - 1, 2) + pow(point[1] - 2, 2) + pow(point[2] - 3, 2) + pow(point[3] - 4, 2);
}

