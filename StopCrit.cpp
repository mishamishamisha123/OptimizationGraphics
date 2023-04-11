//
// Created by misha on 17.11.2021.
//

#include <vector>
#include "StopCrit.h"
#include <cmath>

int StopCrit::getN() const {
    return n;
}

StopCrit::StopCrit(int n_, double eps_, char t) : eps(eps_), n(n_), type(t) {}

double StopCrit::getEps() const {
    return eps;
}

bool StopCritN::stop(int n, std::vector<double> x1, std::vector<double> x2, double fx1, double fx2, double grad, int last_improve) {
    return this->getN() < n;
}

StopCritN::StopCritN(int n) : StopCrit(n, 0, 'n') {}

StopCritGrad::StopCritGrad(double eps) : StopCrit(0, eps, 'g') {}

bool StopCritGrad::stop(int n, std::vector<double> x1, std::vector<double> x2, double fx1, double fx2, double grad, int last_improve) {
    return abs(grad) < getEps();
}

StopCritDelta::StopCritDelta(double eps) : StopCrit(0, eps, 'd') {}

bool StopCritDelta::stop(int n, std::vector<double> x1, std::vector<double> x2, double fx1, double fx2, double grad, int last_improve)
{
    double sum = 0;
    for (int i = 0; i < std::min(x1.size(), x2.size()); ++i) {
        sum += pow(x1[i] - x2[i], 2);
    }
    return sum < pow(getEps(), 2);
}

StopCritGrow::StopCritGrow(double eps) : StopCrit(0, eps, 'G') {}

bool StopCritGrow::stop(int n, std::vector<double> x1, std::vector<double> x2, double fx1, double fx2, double grad, int last_improve)
{
    return (fx2-fx1)/fx2 < pow(getEps(), 2);
}

StopCritLastImprove::StopCritLastImprove(int n) : StopCrit(n, 0, 'l') {}

bool StopCritLastImprove::stop(int n, std::vector<double> x1, std::vector<double> x2, double fx1, double fx2, double grad, int last_improve)
{
    return this->getN() < last_improve;
}

