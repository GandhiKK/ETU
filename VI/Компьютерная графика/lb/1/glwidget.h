#ifndef GLWIDGET_H
#define GLWIDGET_H


#include <QGLWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    QString type = "GL_POINTS";

private slots:
    void changeType(QString type);
};
#endif // GLWIDGET_H
