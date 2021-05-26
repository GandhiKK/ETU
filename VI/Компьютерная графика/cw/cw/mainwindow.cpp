#include "drawer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <table.h>


bool MainWindow::count = false;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    drawer = new Drawer();

    ui->setupUi(this);
    ui->verticalLayout->addWidget(drawer, 1);
    ui->unbindLight->setDisabled(true);

    float splitDensity = 3.0f;
  //  table.bigPanel->split(splitDensity);
  //  table.bigPanelSides->split(splitDensity);
   // table.smallPanel->split(splitDensity);
   // table.smallPanelSides->split(splitDensity);

    for (Figure* f : table.legs)
        f->split(splitDensity);
    for (Figure* f : table.smallLegs)
        f->split(splitDensity);
    for (Figure* f : table.ironLegs)
        f->split(splitDensity);

    for (Figure* f : table.legs)
        drawer->addFigure(f);
    for (Figure* f : table.smallLegs)
        drawer->addFigure(f);
    for (Figure* f : table.ironLegs)
        drawer->addFigure(f);

 //   drawer->addFigure(table.smallPanel);
 //    drawer->addFigure(table.smallPanelSides);
  //  drawer->addFigure(table.bigPanel);
    drawer->addFigure(table.sitting);
   // QObject::connect(ui->attachLightCheckbox, SIGNAL(clicked()), this, SLOT(lightClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_bindLight_clicked()
{

    LightConfig::base.attachViewWrapper(&drawer->viewWrapper());
    ui->bindLight->setDisabled(true);
     ui->unbindLight->setDisabled(false);

}

void MainWindow::on_unbindLight_clicked()
{
    LightConfig::base.detachViewWrapper();
    ui->bindLight->setDisabled(false);
     ui->unbindLight->setDisabled(true);
}


void MainWindow::on_firstSettings_clicked()
{
    LightConfig::base.changeConfig(GL_LIGHT0,
                                QVector4D(40,40,40, 1),
                                QColor(62, 62, 62),
                                QColor(184, 246, 255),
                                QColor(255, 255, 255));

    ui->firstSettings->setDisabled(true);
     ui->secondSettings->setDisabled(false);
     ui->thirdSettings->setDisabled(false);
}

void MainWindow::on_secondSettings_clicked()
{

    LightConfig::base.changeConfig(GL_LIGHT1,
                                   QVector3D(1, 1, 1),
                                   QColor(12, 12, 62),
                                   QColor(90, 123, 128),
                                   QColor(75, 128, 118));

    ui->firstSettings->setDisabled(false);
     ui->secondSettings->setDisabled(true);
     ui->thirdSettings->setDisabled(false);
}


void MainWindow::on_thirdSettings_clicked()
{
    LightConfig::base.changeConfig(GL_LIGHT1,
                                   QVector3D(12, 12, 1),
                                   QColor(62, 12, 62),
                                   QColor(90, 23, 18),
                                   QColor(5, 128, 118));

    ui->firstSettings->setDisabled(false);
     ui->secondSettings->setDisabled(false);
     ui->thirdSettings->setDisabled(true);
}
