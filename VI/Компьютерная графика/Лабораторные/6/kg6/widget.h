#ifndef WIDGET_H
#define WIDGET_H

#include <QGLWidget>
#include <QVector3D>
#include <QMouseEvent>

typedef std::pair<float, float> point;

class Widget: public QGLWidget {

public:
    int vertices = 4;
    float angleX, angleZ, angleY;
    float starSize = 2, starHeight = 1, endSize = 0.5;
    float axisSize = 3.5, arrowSize = 0.1;
    bool polygons, showWireframe, perspective;

    QList<QVector3D> topPoints;
    QList<QVector3D> bottomPoints;
    QList<QVector3D> sidePoints;
    QList<QVector3D> sideNormals;
    QList<QVector3D> wireframe;
    QList<QVector3D> wireframe2;
    QList<QVector3D> wireframe3;
    QList<QVector3D> wireframe4;
    QList<QVector3D> wireframe5;
    QList<QVector3D> wireframe6;
    QList<QVector3D> wireframe7;
    QList<QVector3D> wireframe8;
 QList<QVector3D> wireframe9;
    QVector3D *cameraPosition;
    QVector3D *figurePosition;
    float d = -1.0;
    QVector3D *figureScale;

    Widget(QWidget*);
    void initializeGL();
    void resizeGL(int, int);
    void paintGL();

    void drawWireframe(QList<QVector3D> wireframe);
    void drawPolygons();
    void recountPoints();
    void setPerspectiveProjection();
    void setOrthoProjection();
    void drawAxises();
    void setLight();
    void changeBrightness(float b);
    void setShowWireframe(bool s);
    void setShowPolygons(bool s);

    void changeCameraPositionX(float x);
    void changeCameraPositionY(float y);
    void changeCameraPositionZ(float z);

    void changeFigurePositionX(float x);
    void changeFigurePositionY(float y);
    void changeFigurePositionZ(float z);

    void changeFigureScaleX(float x);
    void changeFigureScaleY(float y);
    void changeFigureScaleZ(float z);


    QVector3D vectorProduct(float ax, float ay, float az, float bx, float by, float bz);



};

#endif // WIDGET_H
