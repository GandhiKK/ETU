#ifndef FRACTAL_H
#define FRACTAL_H

#include <QVector2D>
#include <QVector>
#include "graf_classes/my_figure.h"


void makeFractal(My_Figure *start, int line_width, int length, int mainAngle, int leftAngle,int rightAngle, int N, int curr_n=0);
QVector <My_Figure*>  makeFractal(QVector <My_Figure*> store,QVector2D centr,  int line_width, int length, int mainAngle, int leftAngle,int rightAngle, int N, int curr_n);

QVector2D getLineCenter(QVector2D p1, QVector2D p2);
QVector2D findScale(QVector2D p1, QVector2D p2,float n);

//доп
void makeLabirint(My_Figure *start, int line_width, int length, int mainAngle, int leftAngle,int rightAngle, int N, int curr_n=0);
QVector <My_Figure*>  makeLabirint(QVector <My_Figure*> store,QVector2D centr,  int line_width, int length, int mainAngle, int leftAngle,int rightAngle, int N, int curr_n);

#endif // FRACTAL_H
