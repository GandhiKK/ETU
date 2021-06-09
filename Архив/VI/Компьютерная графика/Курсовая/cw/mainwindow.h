#pragma once

#include "drawer.h"

#include <QMainWindow>
#include <table.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void lightClicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_bindLight_clicked();

    void on_unbindLight_clicked();

    void on_firstSettings_clicked();

    void on_secondSettings_clicked();

    void on_thirdSettings_clicked();

private:
    Drawer *drawer;
    Ui::MainWindow *ui;
    Table table = Table(7.0f, 7.0f ,12.0f);
    static bool count;
};
