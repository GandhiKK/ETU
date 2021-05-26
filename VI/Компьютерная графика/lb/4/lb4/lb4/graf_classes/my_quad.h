#ifndef MY_QUAD_H
#define MY_QUAD_H

#include "my_figure.h"

class My_Quad:public My_Figure
{

    QVector2D point1, point2, point3, point4;
    QVector3D colorRGB;
public:
    My_Quad(QVector2D p1, QVector2D p2, QVector2D p3, QVector2D p4, QVector3D c_rgb =QVector3D(0,0,0), int alpha=1);
    void draw(int line_width);
};

#endif // MY_QUAD_H
