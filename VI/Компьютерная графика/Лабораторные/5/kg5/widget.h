#ifndef WIDGET_H
#define WIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QTimer>
#include <QString>

#include <QGLShader>
#include <QGLShaderProgram>
//#include <QPoint>
#include <QMatrix4x4>
#include <QVector4D>
#include <QVector3D>

#include <qmath.h>
#include <cmath>


typedef std::pair<float, float> point;

class Widget: public QGLWidget {


    Q_OBJECT

public:
    QVector<float> knots;
    int d;
    QVector<QPointF> points;

    static const int COLS = 50;
    const float GRID_SIZE = 0.1;
    static const int POINT_SIZE = 8;

    int dragNodeIndex;
    bool isDrag;
    float time;

    QList<point> nodes;
    QList <point> graphPoints;

    QGLShaderProgram* program;

    Widget(QWidget* parent = 0);
    ~Widget();

    void initializeGL();
    void resizeGL(int, int);
    void paintGL();

    void recountGraphPoints();
    const QVector4D* surfaceColor;

protected:
    point bezier(double t);
    double bernstein(int i, int n, double t);
    double factorial(double n);
    void CrKnotVector();
    float B(float x, int n, int d);
    void Bspline();

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent * e);

private slots:
    void refresh();

};

#endif // WIDGET_H
