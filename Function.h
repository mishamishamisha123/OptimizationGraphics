//
// Created by misha on 17.11.2021.
//

#ifndef BIGPROJECTFUNCOPTIMIZE_FUNCTION_H
#define BIGPROJECTFUNCOPTIMIZE_FUNCTION_H
#include <vector>

/*class Function {
    int dim = 4;
public:
    virtual double eval(double x, double y, double z, double w) = 0;
    double derivative(double x, double y, double z, double w, double eps = 1e-5);
    double derivative2(double x, double y, double z, double w, int i, int j, double eps = 1e-5);
    int getDim() const;
    Function();
};

class Func2d : public Function {
public:
    double eval(double x, double y, double z, double w) override;
    Func2d();
};

class Func2d1 : public Function {
public:
    Func2d1();
    double eval(double x, double y, double z, double w) override;
};*/

class Function {
    int dim = 4;
public:
    virtual double eval(std::vector<double> point) = 0;
    double derivative(std::vector<double> points, double eps = 1e-5);
    double derivative(std::vector<double> points, int i, double eps = 1e-5);
    double derivative2(std::vector<double> points, int i, int j, double eps = 1e-5);
    int getDim() const;
    Function(int dim_ = 2);
};

class Func2d : public Function {
public:
    double eval(std::vector<double> point) override;
    Func2d();
};

class Func2d1 : public Function {
public:
    Func2d1();
    double eval(std::vector<double> point) override;
};

class Func4d : public Function {
public:
    Func4d();
    double eval(std::vector<double> point) override;
};

#endif //BIGPROJECTFUNCOPTIMIZE_FUNCTION_H
