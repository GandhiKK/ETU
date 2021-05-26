#ifndef WIDGET_H
#define WIDGET_H

#include <QGLWidget>
#include <QDebug>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QPointF>
#include <QVector>
#include <QLineF>
class MyWidget : public QGLWidget
{
public:
    MyWidget(QWidget *parent = 0);
    void setd(int d);
    void sets(int s);
    void setb(bool f);
    void clear();



protected:
   void initializeGL();
   void resizeGL(int nWidth, int nHeight);
   void paintGL();
   void mousePressEvent(QMouseEvent* event);
   void mouseMoveEvent(QMouseEvent* event);
   void mouseReleaseEvent(QMouseEvent* event);

private:
   QPointF start;
   QVector<QPointF> points;
   QVector<float> knots;
   QPointF* selected;

   int d;
   int sm;
   bool bones;

   void CrKnotVector();
   float B(float x,int n, int d);
   void NURBspline();
};

#endif // WIDGET_H
