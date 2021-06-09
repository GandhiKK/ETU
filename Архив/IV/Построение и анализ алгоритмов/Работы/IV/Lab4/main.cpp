#include "mainwindow.h"

#include <QApplication>
#include <QTime>
#include <QStyle>
#include <QFile>
#include <QtWidgets>



int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}



