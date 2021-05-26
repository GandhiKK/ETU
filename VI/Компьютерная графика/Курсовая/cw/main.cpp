#include "mainwindow.h"

#include <QApplication>
#include <QOpenGLContext>
#include <QSurfaceFormat>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat *format = new QSurfaceFormat();
    format->setDepthBufferSize(48);
    format->setMajorVersion(3);
    format->setMinorVersion(3);
    format->setSamples(4);
    format->setProfile(QSurfaceFormat::CompatibilityProfile);
    QSurfaceFormat::setDefaultFormat(*format);

    MainWindow w;

    w.setWindowTitle("cw Kireev Mukovsky");
    QFile styleF;
    styleF.setFileName(":/styles/styles.css");
    styleF.open(QFile::ReadOnly);
    QString qssStr = styleF.readAll();
    qApp->setStyleSheet(qssStr);

    w.show();
    return a.exec();
}
