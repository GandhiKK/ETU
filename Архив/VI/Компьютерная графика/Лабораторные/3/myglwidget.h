#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QDebug>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QPointF>
#include <QVector>
#include <QLineF>

class MyGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    MyGLWidget(QWidget *parent = 0);
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


   int Width=300, Height=150;
   int winSizeW, winSizeH;

   int d;
   int sm;
   bool bones;

   void CrKnotVector();
   float B(float x,int n, int d);
   void Bspline();

private slots:
//    void changeShapePicture(QString);
//    void changePattern(int);
//    void blendS(QString);
//    void blendD(QString);
//    void setAlphaTestFunc(QString);
//    void setAlphaTestRef(int);
//    void setXScissor(int);
//    void setYScissor(int);
//    void setHeightScissor(int);
//    void setWidthScissor(int);
};

#endif // MYGLWIDGET_H
