#include "my_quad.h"

My_Quad::My_Quad(QVector2D p1, QVector2D p2, QVector2D p3, QVector2D p4, QVector3D c_rgb, int alpha)
{
    this->point1 =p1;
    this->point2 =p2;
    this->point3 =p3;
    this->point4 =p4;
}

void My_Quad::draw(int line_width)
{
    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex3f(this->point1.x(), this->point1.y(),0);
    glVertex3f( this->point2.x(), this->point2.y(), 0);
    glVertex3f(this->point3.x(), this->point3.y(),0);
    glVertex3f(this->point4.x(), this->point4.y(),0);
    glEnd();
}
