#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "OptMethod.h"
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <QtWidgets>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGradient>
#include <QPixmap>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QWidget>
#include <Qt>
#include <QMouseEvent>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->RandomSearch->setChecked(true);
    ui->comboBox_N->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_RandomSearch_clicked()
{
    ui->comboBox_RS->setVisible(true);
    ui->comboBox_N->setVisible(false);
}


void MainWindow::on_Newton_clicked()
{
    ui->comboBox_RS->setVisible(false);
    ui->comboBox_N->setVisible(true);
}

void MainWindow::on_OptimizeButton_clicked()
{
    OptMethod* om;
    StopCrit* sc;
    Function* func;
    Area* area;
    std::vector<double> start, areaV;

    QString startText = ui->StartField->text();
    QString areaText = ui->AreaField->text();
    QString stopCritText = ui->lineEdit->text();

    std::string startString = startText.toStdString(), areaString = areaText.toStdString(), stopCritString = stopCritText.toStdString(), token;
    std::istringstream iss(startString), iss1(areaString);
    char delimiter = ' ';

    while (std::getline(iss, token, delimiter)) {
        start.push_back(std::stod(token));
    }
    if (start.size() != 2){
        start.clear();
        start.push_back(3);
        start.push_back(3);
    }
    while (std::getline(iss1, token, delimiter)) {
        areaV.push_back(std::stod(token));
    }
    if (areaV.size() != 4){
        areaV.clear();
        areaV.push_back(0);
        areaV.push_back(10);
        areaV.push_back(0);
        areaV.push_back(10);
    }

    QString funcStr = ui->FunctionSelect->currentText();
    if (funcStr.toStdString() == "x^2+y^2"){
        func = new Func2d();
    }
    else{
        func = new Func2d1();
    }

    area = new Area2d(areaV[0], areaV[1], areaV[2], areaV[3]);

    if (ui->RandomSearch->isChecked()){
        om = new RandomSearch();
        QString stopStr = ui->comboBox_RS->currentText();
        if (stopStr.toStdString() == "Число итераций"){
            sc = new StopCritN(std::stod(stopCritString));
        }
        else{
            sc = new StopCritLastImprove(std::stod(stopCritString));
        }
    }
    else {
        om = new Newton();
        QString stopStr = ui->comboBox_N->currentText();
        if (stopStr.toStdString() == "Число итераций"){
            sc = new StopCritN(std::stod(stopCritString));
        }
        else if (stopStr.toStdString() == "Норма градиента"){
            sc = new StopCritGrad(std::stod(stopCritString));
        }
        else if (stopStr.toStdString() == "Норма разности последних точек"){
            sc = new StopCritDelta(std::stod(stopCritString));
        }
        else{
            sc = new StopCritGrow(std::stod(stopCritString));
        }
    }


    om->optimize(func, sc, area, start);

    QGraphicsScene* scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

    int width = ui->graphicsView->width(), height = ui->graphicsView->height();

    vector<double> temp{};
    vector<vector<double>> map{};

    double step_w = (area->getArea()[1] - area->getArea()[0]) / width;
    double step_h = (area->getArea()[3] - area->getArea()[2]) / height;
    double pos_h = area->getArea()[2];
    double pos_w = area->getArea()[0];

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            temp.push_back(func->eval(vector<double>{pos_w, pos_h}));
            pos_w += step_w;
        }
        map.push_back(temp);
        temp.clear();
        pos_w = area->getArea()[0];
        pos_h += step_h;
    }

    QStatusBar* statusBar = QMainWindow::statusBar();

    // Отображаем сообщение в статус баре на 5 секунд
    statusBar->showMessage(QString::number(om->points.size()), 5000);

    double max = map[0][0];
    double min = map[0][0];

    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j) {
            if(map[i][j] > max) max = map[i][j];
            if(map[i][j] < min) min = map[i][j];
        }
    };

    QImage* image = new QImage(width, height, QImage::Format_RGB32);

    int color = 0;

    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
                color = (int) (256 * (map[i][j] - min) / (max - min));
                QRgb value = qRgb(color, 0, color);
                image->setPixel(j, i, value);
        }
    };

    QPainter painter(image);
    painter.setPen(QPen(Qt::white, 1));
    painter.setFont(QFont("Arial", 10));
    double x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    x1 = width / (area->getArea()[1] - area->getArea()[0]) * (om->points[0][0] - area->getArea()[0]);
    y1 = height / (area->getArea()[3] - area->getArea()[2]) * (om->points[0][1] - area->getArea()[2]);
    painter.drawText(x1, y1, QString::number(1) + QString(". ") + QString::number(func->eval(om->points[0]), 'e', 3));

    if (om->points.size() > 1)
        for (int i = 0; i < om->points.size() - 1; ++i){
            x1 = width / (area->getArea()[1] - area->getArea()[0]) * (om->points[i][0] - area->getArea()[0]);
            x2 = width / (area->getArea()[1] - area->getArea()[0]) * (om->points[i + 1][0] - area->getArea()[0]);
            y1 = height / (area->getArea()[3] - area->getArea()[2]) * (om->points[i][1] - area->getArea()[2]);
            y2 = height / (area->getArea()[3] - area->getArea()[2]) * (om->points[i + 1][1] - area->getArea()[2]);
            painter.drawLine(QPointF(x1,y1), QPointF(x2,y2));
            painter.drawText(x2, y2, QString::number(i + 2) + QString(". ") + QString::number(func->eval(om->points[i + 1]), 'e', 2));
        }

    painter.setFont(QFont("Arial", 15));
    painter.drawText(20, 25, QString("Точек найдено: ") + QString::number(om->points.size(), 'f', 0));
    painter.drawText(20, 40, QString("x = ") + QString::number(om->points[om->points.size() - 1][0], 'e', 2) + QString(", y = ") + QString::number(om->points[om->points.size() - 1][1], 'e', 2));
    painter.drawText(20, 55, QString("f = ") + QString::number(func->eval(om->points[om->points.size() - 1]), 'e', 2));


    QPixmap pixmap = QPixmap::fromImage(*image);

    // создаем QGraphicsPixmapItem и добавляем его на сцену
    QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap);
    scene->addItem(pixmapItem);

    // задаем размеры сцены
    scene->setSceneRect(pixmap.rect());

}

