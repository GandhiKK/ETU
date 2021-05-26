#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Widget* glwidget;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent*);

private slots:

    void on_comboBox_currentIndexChanged(int index);

    void on_xSlider_valueChanged(int value);

    void on_ySlider_valueChanged(int value);

    void on_zSlider_valueChanged(int value);

    void on_oxSlider_valueChanged(int value);

    void on_ozSlider_valueChanged(int value);

    void on_oySlider_valueChanged(int value);

    void on_fxSlider_valueChanged(int value);

    void on_fySlider_valueChanged(int value);

    void on_fzSlider_valueChanged(int value);

    void on_sxSlider_valueChanged(int value);

    void on_sySlider_valueChanged(int value);

    void on_szSlider_valueChanged(int value);

    void on_horizontalSlider_valueChanged(int value);

    void on_checkBox_2_clicked(bool checked);

    void on_checkBox_4_clicked(bool checked);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
