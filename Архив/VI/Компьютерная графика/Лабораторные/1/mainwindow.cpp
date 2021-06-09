#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

int k = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::addPic()
{
    QPixmap pixmap(":/img/img/img2.jpg");
    int w = ui->label->width();
    int h = ui->label->height();
    ui->label->setPixmap(pixmap.scaled(w, h));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    k++;
    if (k % 2 == 1)
        addPic();
    else
        ui->label->clear();
}
