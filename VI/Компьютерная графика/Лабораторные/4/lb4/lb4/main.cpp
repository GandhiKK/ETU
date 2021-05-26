#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;


    w.setWindowTitle("Kireev Mukovsky 8383 lb4");
    QFile styleF;
    styleF.setFileName(":/styles/styles.css");
    styleF.open(QFile::ReadOnly);
    QString qssStr = styleF.readAll();
    qApp->setStyleSheet(qssStr);


    w.show();


    return a.exec();
}
