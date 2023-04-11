#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_RandomSearch_clicked();

    void on_Newton_clicked();

    void on_OptimizeButton_clicked();

private:
    Ui::MainWindow *ui;

signals:
    void signal();
};
#endif // MAINWINDOW_H
