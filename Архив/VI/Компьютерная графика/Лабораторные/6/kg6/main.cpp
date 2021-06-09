#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    w.setWindowTitle("Computer graphic lb6 Kireev Mukovsky");
    QFile styleF;
    styleF.setFileName(":/styles/styles.css");
    styleF.open(QFile::ReadOnly);
    QString qssStr = styleF.readAll();
    qApp->setStyleSheet(qssStr);

    w.show();

    return a.exec();
}
