#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setFixedSize(1200,150);

   // w.setWindowIcon(QIcon(":/images/images/2.png"));
    w.setWindowTitle("Лабораторная работа №1");

    return a.exec();
}
