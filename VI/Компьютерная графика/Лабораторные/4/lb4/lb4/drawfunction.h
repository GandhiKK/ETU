#ifndef DRAWFUNCTION_H
#define DRAWFUNCTION_H

#include <QGLWidget>
#include <QVector2D>
#include <QVector3D>

namespace drawFunction {

    void drawPoint(QVector2D p, QVector3D c_rgb, float alpha=1,  int size=4);
    void drawLine(QVector2D p1, QVector2D p2, QVector3D c_rgb, float alpha=1,  int size=4);
}

#endif // DRAWFUNCTION_H
