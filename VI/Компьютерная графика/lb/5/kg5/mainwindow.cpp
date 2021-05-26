#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QGLFormat fmt;
    fmt.setSampleBuffers(true);
    fmt.setSamples(16);
    QGLFormat::setDefaultFormat(fmt);

    glwidget = new Widget(this);
    int width = size().width();
    int height = size().height() ;
    glwidget->resize(width, height);
    glwidget->setGeometry(0, 0, width, height);
    glwidget->resizeGL(width, height);

    QList<point> pts;

//    pts.append(point(-0.86, -0.2));
//    pts.append(point(-0.66, 0.4));
//    pts.append(point(-0.33, -0.4));
//    pts.append(point(-0.1, 0.3));
//    pts.append(point(0.36, -0.4));
//    pts.append(point(0.7, 0.28));

    pts.append(point(-0.86, 0.6));
    pts.append(point(-0.66, 1.2));
    pts.append(point(0.86, -1.0));


    glwidget->nodes = pts;
    glwidget->recountGraphPoints();




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *e) {
    int width = e->size().width();
    int height = e->size().height() ;
    glwidget->setGeometry(0, 0, width, height);
    glwidget->resizeGL(width, height);
}
