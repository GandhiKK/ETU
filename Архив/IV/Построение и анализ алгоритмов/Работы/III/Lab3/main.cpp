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
    w.setWindowTitle("Лабораторная работа №3");

    return a.exec();
}
