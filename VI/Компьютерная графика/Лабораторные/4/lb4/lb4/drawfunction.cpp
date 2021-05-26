#include "drawfunction.h"

namespace drawFunction {

    void drawPoint(QVector2D p, QVector3D c_rgb, float alpha,  int size)
    {
        glPointSize(size);
        glBegin(GL_POINTS);
        glColor4f(c_rgb.x(), c_rgb.y(), c_rgb.z(), alpha);
        glVertex3f( p.x(), p.y(),0);
        glEnd();
        return;
    }
    void drawLine(QVector2D p1, QVector2D p2, QVector3D c_rgb, float alpha,  int size)
    {
        glLineWidth(size);
        glBegin(GL_LINES);
        glColor4f(c_rgb.x(), c_rgb.y(), c_rgb.z(), alpha);
        glVertex3f( p1.x(), p1.y(),0);
        glVertex3f( p2.x(), p2.y(),0);
        glEnd();
        return;
    }

}
