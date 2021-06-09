#ifndef MY_TRIANGLE_H
#define MY_TRIANGLE_H

#include "my_figure.h"


class My_Triangle:public My_Figure
{
    QVector2D point1, point2, point3;
    QVector3D colorRGB;
    float alpha;
    bool filled;
public:
    My_Triangle(QVector2D p1= QVector2D(0,0),
                QVector2D p2= QVector2D(0,0),
                QVector2D p3= QVector2D(0,0),
                QVector3D c_rgb =QVector3D(0,0,0), float alpha=1, bool filled=false);
    // переопределённые функции
    void draw(int line_width);
    void turn(float angle=0.0f, QVector2D center= QVector2D(0,0));
    void scale(float n=0.0f, QVector2D center= QVector2D(0,0));
    void scaleX(float n=0.0f, QVector2D center= QVector2D(0,0));
    void scaleY(float n=0.0f, QVector2D center= QVector2D(0,0));
    void moveTo(QVector2D point= QVector2D(0,0));   //собственно двигает центр нижней грани в эту точку
    void moveFromTo(QVector2D pointFrom= QVector2D(0,0),QVector2D pointTo= QVector2D(0,0));
    float  perimeter();
    void moveY(int value);
    void moveX(int value);
    void reflectX(QVector2D around);
    My_Figure * copy();

    //
    QVector2D getPoint1() const;
    void setPoint1(const QVector2D &value);
    QVector2D getPoint2() const;
    void setPoint2(const QVector2D &value);
    QVector2D getPoint3() const;
    void setPoint3(const QVector2D &value);
    QVector3D getColorRGB() const;
    void setColorRGB(const QVector3D &value);
    float getAlpha() const;
    void setAlpha(float value);
};


#endif // MY_TRIANGLE_H
