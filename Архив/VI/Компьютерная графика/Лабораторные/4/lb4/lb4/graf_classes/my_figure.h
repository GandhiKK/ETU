#ifndef MY_FIGURE_H
#define MY_FIGURE_H

#include <QVector2D>
#include <QVector3D>
#include <QGLWidget>

class My_Figure
{
public:
    virtual My_Figure *copy()=0;
    virtual void draw(int line_width=2)=0;
    virtual void turn(float angle=0.0f, QVector2D center= QVector2D(0,0))=0;  // именно поворачивает текущий объект
    virtual void scale(float angle=0.0f, QVector2D center= QVector2D(0,0))=0;
    virtual void scaleX(float n=0.0f, QVector2D center= QVector2D(0,0))=0;
    virtual void scaleY(float n=0.0f, QVector2D center= QVector2D(0,0))=0;
    virtual void moveTo(QVector2D point= QVector2D(0,0))=0;
    virtual void moveFromTo(QVector2D pointFrom= QVector2D(0,0),QVector2D pointTo= QVector2D(0,0))=0;
    virtual float  perimeter()=0;


    virtual QVector2D getPoint1() const =0;
    virtual void setPoint1(const QVector2D &value) =0;
    virtual QVector2D getPoint2() const =0;
    virtual void setPoint2(const QVector2D &value) =0;
    virtual QVector3D getColorRGB() const =0;
    virtual void setColorRGB(const QVector3D &value)=0;
    virtual float getAlpha() const=0;
    virtual void setAlpha(float value)=0;
    virtual void moveY(int value)=0;
    virtual void moveX(int value)=0;
    virtual void reflectX(QVector2D around)=0;
    //virtual QVector2D getGrowPoint()=0;  // возвращает точку, из которой будет "рaсти" дерево
};

#endif // MY_FIGURE_H
