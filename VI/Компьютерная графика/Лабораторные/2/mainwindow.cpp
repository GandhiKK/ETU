#include "mainwindow.h"
#include "ui_mainwindow.h"

int k = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->ref->setEnabled(false);
    ui->comboBoxFunc->setEnabled(false);
    ui->ScissorHeight->setEnabled(false);
    ui->ScissorWidth->setEnabled(false);
    ui->ScissorX->setEnabled(false);
    ui->ScissorY->setEnabled(false);
    ui->sfactor->setEnabled(false);
    ui->dfactor->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPic1()
{
    QPixmap pixmap(":/img/img/img1.jpg");
//    int w = ui->label_4->width();
//    int h = ui->label_4->height();
    ui->label_4->setPixmap(pixmap);
}

void MainWindow::addPic2()
{
    QPixmap pixmap(":/img/img/img4.jpg");
//    int w = ui->label_4->width();
//    int h = ui->label_4->height();
    ui->label_4->setPixmap(pixmap);
}

void MainWindow::on_pushButton_clicked()
{
    k++;
    if (k % 3 == 1)
        addPic1();
    else if (k % 3 == 2)
        addPic2();
    else
        ui->label_4->clear();
}

void MainWindow::on_checkBox_clicked(bool check)
{
    ui->comboBoxFunc->setEnabled(check);
    ui->ref->setEnabled(check);
}

void MainWindow::on_checkBox_2_clicked(bool check)
{
    ui->ScissorHeight->setEnabled(check);
    ui->ScissorWidth->setEnabled(check);
    ui->ScissorX->setEnabled(check);
    ui->ScissorY->setEnabled(check);
}

void MainWindow::on_checkBox_3_clicked(bool check)
{
    ui->sfactor->setEnabled(check);
    ui->dfactor->setEnabled(check);
}
