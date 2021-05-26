#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widget.h"
#include <QResizeEvent>
#include <qmath.h>

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
    int width = size().width() - 130;
    int height = size().height() - 10;
    glwidget->setGeometry(350, 5, width, height);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *e) {
    int width = e->size().width() - 160;
    int height = e->size().height() - 10;
    glwidget->setGeometry(320, 5, width, height);
    glwidget->resizeGL(width, height);
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (index == 0) {
        glwidget->perspective = true;
        glwidget->setPerspectiveProjection();
    }
    if (index == 1) {
        glwidget->perspective = false;
        glwidget->setOrthoProjection();
    }
}
//положение наблюдателя
void MainWindow::on_xSlider_valueChanged(int value)
{
    glwidget->changeCameraPositionX(value * 10.0 / 100.0 - 5.0);
}

void MainWindow::on_ySlider_valueChanged(int value)
{
    glwidget->changeCameraPositionY(value * 10.0 / 100.0 - 5.0);
}

void MainWindow::on_zSlider_valueChanged(int value)
{
    glwidget->changeCameraPositionZ(value * 10.0 / 100.0 - 5.0);
}
//поворот
void MainWindow::on_oxSlider_valueChanged(int value)
{
    glwidget->angleX = value / 100.0 * 360;
    glwidget->update();
}

void MainWindow::on_ozSlider_valueChanged(int value)
{
    glwidget->angleZ = value / 100.0 * 360;
    glwidget->update();
}

void MainWindow::on_oySlider_valueChanged(int value)
{
    glwidget->angleY = value / 100.0 * 360;
    glwidget->update();
}
//смещение
void MainWindow::on_fxSlider_valueChanged(int value)
{
    glwidget->changeFigurePositionX(value * 10.0 / 100.0 - 5.0);
}


void MainWindow::on_fySlider_valueChanged(int value)
{
    glwidget->changeFigurePositionY(value * 10.0 / 100.0 - 5.0);
}


void MainWindow::on_fzSlider_valueChanged(int value)
{
    glwidget->changeFigurePositionZ(value * 10.0 / 100.0 - 5.0);
}
//масштабирование
void MainWindow::on_sxSlider_valueChanged(int value)
{
    glwidget->changeFigureScaleX(value / 50.0);
}

void MainWindow::on_sySlider_valueChanged(int value)
{
    glwidget->changeFigureScaleY(value / 50.0);
}

void MainWindow::on_szSlider_valueChanged(int value)
{
    glwidget->changeFigureScaleZ(value / 50.0);
}
//освещенность
void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    glwidget->changeBrightness(value / 100.0);
}
//контуры фигуры
void MainWindow::on_checkBox_2_clicked(bool checked)
{
    glwidget->setShowWireframe(checked);
}

//полигоны
void MainWindow::on_checkBox_4_clicked(bool checked)
{
    glwidget->setShowPolygons(checked);
}


void MainWindow::on_pushButton_clicked()
{
    glwidget->changeLightPosition1();
}

void MainWindow::on_pushButton_2_clicked()
{
    glwidget->changeLightPosition2();
}

void MainWindow::on_pushButton_3_clicked()
{
    glwidget->changeLightPosition3();
}

void MainWindow::on_pushButton_4_clicked()
{
    glwidget->changeMaterial1();
}

void MainWindow::on_pushButton_5_clicked()
{
    glwidget->changeMaterial2();
}

void MainWindow::on_pushButton_6_clicked()
{
    glwidget->changeMaterial3();
}

void MainWindow::on_pushButton_7_clicked()
{
    glwidget->changeModel();
}
