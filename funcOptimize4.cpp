#include <iostream>
#include "OptMethod.h"
#include <locale.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    int optMethod, function, stopCrit;
    double x, y, z, w;
    OptMethod* om;
    StopCrit* sc;
    Function* func;
    Area* area;
    vector<double> start;

    vector<double> nums;
    double num;

    std::cout << "Выберите метод:\n1 - Случайный поиск\n2 - Метод Ньютона \n";
    std::cin >> optMethod;
    std::cout << "Выберите функцию:\n1 - x^2 + y^2\n2 - Функция Розенброка\n3 - (x - 1)^2 + (y - 2)^2 + (z - 3)^2 + (w - 4)^2 \n";
    std::cin >> function;

    std::cout << "Введите первую координату старта\n";
    std::cin >> x;
    std::cout << "Введите вторую координату старта\n";
    std::cin >> y;

    if (function == 1) {
        func = new Func2d();
        area = new Area2d(0, 10, 0, 10);
        start = { x, y };
    }
    else if (function == 2) {
        func = new Func2d1();
        area = new Area2d(0, 10, 0, 10);
        start = { x, y };
    }
    else {
        func = new Func4d();
        area = new Area4d(0, 10, 0, 10, 0, 10, 0, 10);

        std::cout << "Введите третью координату старта\n";
        std::cin >> z;
        std::cout << "Введите четвертую координату старта\n";
        std::cin >> w;
        start = { x, y, z, w };
    }

    if (optMethod == 1) {
        om = new RandomSearch();

        std::cout << "Выберите критерий остановки:\n1 - Число итераций\n2 - Число итераций с момента последнего улучшения\n";
        std::cin >> stopCrit;
        std::cout << "Введите число итераций\n";
        cin >> num;
        if (stopCrit == 1) {
            sc = new StopCritN(num);
        }
        else {
            sc = new StopCritLastImprove(num);
        }
    }
    else {
        om = new Newton();

        std::cout << "Выберите критерий остановки:\n1 - Число итераций\n2 - Норма градиента\n3 - Норма разности последних точек\n4 - Норма отношения (f(x_n)-f(x_n-1))/f(x_n)\n";
        std::cin >> stopCrit;
        if (stopCrit == 1) {
            std::cout << "Введите число итераций\n";
            cin >> num;
            sc = new StopCritN(num);
        }
        else if (stopCrit == 2) {
            std::cout << "Введите эпсилон\n";
            cin >> num;
            sc = new StopCritGrad(num);
        }
        else if (stopCrit == 3) {
            std::cout << "Введите эпсилон\n";
            cin >> num;
            sc = new StopCritDelta(num);
        }
        else {
            std::cout << "Введите эпсилон\n";
            cin >> num;
            sc = new StopCritGrow(num);
        }
    }

    om->optimize(func, sc, area, start);

    return 0;
}