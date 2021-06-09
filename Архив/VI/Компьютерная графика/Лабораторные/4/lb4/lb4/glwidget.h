#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "graf_classes/my_triangle.h"
#include "graf_classes/my_line.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
private:
    QString ComboBox_type="Треугольники";
    //
    int X=0, Y=0;
    int Width=150, Height=100;
    int winSizeW, winSizeH;
    //
    int Func=GL_ALWAYS;
    int Ref=1.0;
    //
    int SFactor= GL_SRC_ALPHA, DFactor = GL_ONE_MINUS_SRC_ALPHA;
    //
    int N=1;
    int mainAngle= 0;
    int leftAngle= 45, rightAngle = 60;
    int heightSeq = 10;
    bool isFilled = false;
    float alpha = 1.0;
public:
    explicit GLWidget(QWidget *parent=0);
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);  

private slots:
    // для изменения модификатора:
    void changePicture(QString type);

    //для теста отсечения
    void changeX(int x);
    void changeY(int y);
    void changeWidth(int width);
    void changeHeight(int height);
    // для теста прозрачности
    void changeFunc(int f);
    void changeRef(int r);
    // для смешения цветов
    void changeSfactor(QString s);
    void changeDfactor(QString d);
    //

    void changeN(int n);

    void setLeftAngle(int value);
    void setRightAngle(int value);
    void setHeightSeq(int value);
    void setIsFilled(bool value);
    void setAlpha(int value);
    void setMainAngle(int value);

};

#endif // GLWIDGET_H
