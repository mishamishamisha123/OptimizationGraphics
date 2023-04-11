//
// Created by misha on 17.11.2021.
//

#include "Area.h"

#include <utility>

unsigned long Area::getDim() {
    return area.size() / 2;
}

std::vector<double> Area::getArea() {
    return area;
}

void Area::setAria(std::vector<double> a) {
    this->area = std::move(a);
}

Area2d::Area2d(double x1, double x2, double x3, double x4) {
   this->setAria(std::vector<double>{x1, x2, x3, x4});
}

Area3d::Area3d(double x1, double x2, double x3, double x4, double x5, double x6) {
    this->setAria(std::vector<double>{x1, x2, x3, x4, x5, x6});
}

Area4d::Area4d(double x1, double x2, double x3, double x4, double x5, double x6, double x7, double x8) {
    this->setAria(std::vector<double>{x1, x2, x3, x4, x5, x6, x7, x8});
}
