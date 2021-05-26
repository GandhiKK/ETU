#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->widget->setd(position);
    ui->widget->updateGL();
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    ui->widget->setb(checked);
    ui->widget->updateGL();
}

void MainWindow::on_pushButton_clicked()
{
    ui->widget->clear();
    ui->widget->updateGL();
}
