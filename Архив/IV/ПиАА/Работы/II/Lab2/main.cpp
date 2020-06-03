#include "mainwindow.h"
#include <QApplication>
#include <time.h>
#include <QMainWindow>

int main(int argc, char **argv)
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setFixedSize(1266, 749);
    w.setWindowTitle("Лабораторная работа №2");

    return a.exec();
}
