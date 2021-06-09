#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{

}

void GLWidget::initializeGL()
{
    glClearColor(1,1,1,1);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(type == "GL_POINTS")
        {
        glPointSize(6);
        glBegin(GL_TRIANGLES);
            glColor3f(1, 0, 0);
            glVertex3f (0.1f, 0.0f, 0.5f);
            glColor3f(0, 1, 0);
            glVertex3f (0.0f, 1.0f, 0.4f);
            glColor3f(0, 0, 1);
            glVertex3f (0.0f, 0.0f, 0.2f);
        glEnd ();
//            glPointSize(6);
//            glBegin(GL_POINTS);
//            // 1
//            glColor3f(1, 0, 0);
//            glVertex3f(80, 50, 0);
//            // 2
//            glColor3f(1, 0, 0);
//            glVertex3f(65, 175, 0);
//            // 3
//            glColor3f(0, 0, 1);
//            glVertex3f(160, 250, 0);
//            // 4
//            glColor3f(0, 0, 1);
//            glVertex3f(240, 270, 0);
//            // 5
//            glColor3f(0, 1, 1);
//            glVertex3f(355, 230, 0);
//            // 6
//            glColor3f(0, 1, 1);
//            glVertex3f(370, 50, 0);
//            // 7
//            glColor3f(1, 1, 0);
//            glVertex3f(260, 25, 0);
//            // 8
//            glColor3f(1, 1, 0);
//            glVertex3f(240, 150, 0);
//            // 9
//            glColor3f(0, 1, 0);
//            glVertex3f(180, 95, 0);
//            // 10
//            glColor3f(0, 1, 0);
//            glVertex3f(130, 15, 0);
//            glEnd();
            return;
        }
        if(type == "GL_LINES")
        {
            glLineWidth(4);
            glBegin(GL_LINES);
            // 1
            glColor3f(1, 0, 0);
            glVertex3f(80, 50, 0);
            // 2
            glColor3f(1, 0, 0);
            glVertex3f(65, 175, 0);
            // 3
            glColor3f(0, 0, 1);
            glVertex3f(160, 250, 0);
            // 4
            glColor3f(0, 0, 1);
            glVertex3f(240, 270, 0);
            // 5
            glColor3f(0, 1, 1);
            glVertex3f(355, 230, 0);
            // 6
            glColor3f(0, 1, 1);
            glVertex3f(370, 50, 0);
            // 7
            glColor3f(1, 1, 0);
            glVertex3f(260, 25, 0);
            // 8
            glColor3f(1, 1, 0);
            glVertex3f(240, 150, 0);
            // 9
            glColor3f(0, 1, 0);
            glVertex3f(180, 95, 0);
            // 10
            glColor3f(0, 1, 0);
            glVertex3f(130, 15, 0);
            glEnd();
            return;
        }
        if(type == "GL_LINE_STRIP")
        {
            glLineWidth(4);
            glBegin(GL_LINE_STRIP);
            // 1
            glColor3f(1, 0, 0);
            glVertex3f(80, 50, 0);
            // 2
            glColor3f(1, 0, 0);
            glVertex3f(65, 175, 0);
            // 3
            glColor3f(0, 0, 1);
            glVertex3f(160, 250, 0);
            // 4
            glColor3f(0, 0, 1);
            glVertex3f(240, 270, 0);
            // 5
            glColor3f(0, 1, 1);
            glVertex3f(355, 230, 0);
            // 6
            glColor3f(0, 1, 1);
            glVertex3f(370, 50, 0);
            // 7
            glColor3f(1, 1, 0);
            glVertex3f(260, 25, 0);
            // 8
            glColor3f(1, 1, 0);
            glVertex3f(240, 150, 0);
            // 9
            glColor3f(0, 1, 0);
            glVertex3f(180, 95, 0);
            // 10
            glColor3f(0, 1, 0);
            glVertex3f(130, 15, 0);
            glEnd();
            return;
        }
        if(type == "GL_LINE_LOOP")
        {
            glLineWidth(4);
            glBegin(GL_LINE_LOOP);
            // 1
            glColor3f(1, 0, 0);
            glVertex3f(80, 50, 0);
            // 2
            glColor3f(1, 0, 0);
            glVertex3f(65, 175, 0);
            // 3
            glColor3f(0, 0, 1);
            glVertex3f(160, 250, 0);
            // 4
            glColor3f(0, 0, 1);
            glVertex3f(240, 270, 0);
            // 5
            glColor3f(0, 1, 1);
            glVertex3f(355, 230, 0);
            // 6
            glColor3f(0, 1, 1);
            glVertex3f(370, 50, 0);
            // 7
            glColor3f(1, 1, 0);
            glVertex3f(260, 25, 0);
            // 8
            glColor3f(1, 1, 0);
            glVertex3f(240, 150, 0);
            // 9
            glColor3f(0, 1, 0);
            glVertex3f(180, 95, 0);
            // 10
            glColor3f(0, 1, 0);
            glVertex3f(130, 15, 0);
            glEnd();
            return;
        }
        if(type == "GL_TRIANGLES")
        {
            glBegin(GL_TRIANGLES);
            // 1
            glColor3f(1, 0, 0);
            glVertex3f(80, 50, 0);
            // 2
            glColor3f(1, 0, 0);
            glVertex3f(65, 175, 0);
            // 3
            glColor3f(0, 0, 1);
            glVertex3f(160, 250, 0);
            // 4
            glColor3f(0, 0, 1);
            glVertex3f(240, 270, 0);
            // 5
            glColor3f(0, 1, 1);
            glVertex3f(355, 230, 0);
            // 6
            glColor3f(0, 1, 1);
            glVertex3f(370, 50, 0);
            // 7
            glColor3f(1, 1, 0);
            glVertex3f(260, 25, 0);
            // 8
            glColor3f(1, 1, 0);
            glVertex3f(240, 150, 0);
            // 9
            glColor3f(0, 1, 0);
            glVertex3f(180, 95, 0);
            // 10
            glColor3f(0, 1, 0);
            glVertex3f(130, 15, 0);
            glEnd();
            return;
        }
        if(type == "GL_TRIANGLE_STRIP")
        {
            glBegin(GL_TRIANGLE_STRIP);
            // 1
            glColor3f(1, 0, 0);
            glVertex3f(80, 50, 0);
            // 2
            glColor3f(1, 0, 0);
            glVertex3f(65, 175, 0);
            // 3
            glColor3f(0, 0, 1);
            glVertex3f(160, 250, 0);
            // 4
            glColor3f(0, 0, 1);
            glVertex3f(240, 270, 0);
            // 5
            glColor3f(0, 1, 1);
            glVertex3f(355, 230, 0);
            // 6
            glColor3f(0, 1, 1);
            glVertex3f(370, 50, 0);
            // 7
            glColor3f(1, 1, 0);
            glVertex3f(260, 25, 0);
            // 8
            glColor3f(1, 1, 0);
            glVertex3f(240, 150, 0);
            // 9
            glColor3f(0, 1, 0);
            glVertex3f(180, 95, 0);
            // 10
            glColor3f(0, 1, 0);
            glVertex3f(130, 15, 0);
            glEnd();
            return;
        }
        if(type == "GL_TRIANGLE_FAN")
        {
            glBegin(GL_TRIANGLE_FAN);
            // 1
            glColor3f(1, 0, 0);
            glVertex3f(80, 50, 0);
            // 2
            glColor3f(1, 0, 0);
            glVertex3f(65, 175, 0);
            // 3
            glColor3f(0, 0, 1);
            glVertex3f(160, 250, 0);
            // 4
            glColor3f(0, 0, 1);
            glVertex3f(240, 270, 0);
            // 5
            glColor3f(0, 1, 1);
            glVertex3f(355, 230, 0);
            // 6
            glColor3f(0, 1, 1);
            glVertex3f(370, 50, 0);
            // 7
            glColor3f(1, 1, 0);
            glVertex3f(260, 25, 0);
            // 8
            glColor3f(1, 1, 0);
            glVertex3f(240, 150, 0);
            // 9
            glColor3f(0, 1, 0);
            glVertex3f(180, 95, 0);
            // 10
            glColor3f(0, 1, 0);
            glVertex3f(130, 15, 0);
            glEnd();
            return;
        }
        if(type == "GL_QUADS")
        {
            glBegin(GL_QUADS);
            // 1
            glColor3f(1, 0, 0);
            glVertex3f(80, 50, 0);
            // 2
            glColor3f(1, 0, 0);
            glVertex3f(65, 175, 0);
            // 3
            glColor3f(0, 0, 1);
            glVertex3f(160, 250, 0);
            // 4
            glColor3f(0, 0, 1);
            glVertex3f(240, 270, 0);
            // 5
            glColor3f(0, 1, 1);
            glVertex3f(355, 230, 0);
            // 6
            glColor3f(0, 1, 1);
            glVertex3f(370, 50, 0);
            // 7
            glColor3f(1, 1, 0);
            glVertex3f(260, 25, 0);
            // 8
            glColor3f(1, 1, 0);
            glVertex3f(240, 150, 0);
            // 9
            glColor3f(0, 1, 0);
            glVertex3f(180, 95, 0);
            // 10
            glColor3f(0, 1, 0);
            glVertex3f(130, 15, 0);
            glEnd();
            return;
        }
        if(type == "GL_QUAD_STRIP")
        {
            glBegin(GL_QUAD_STRIP);
            // 1
            glColor3f(1, 0, 0);
            glVertex3f(80, 50, 0);
            // 2
            glColor3f(1, 0, 0);
            glVertex3f(65, 175, 0);
            // 3
            glColor3f(0, 0, 1);
            glVertex3f(160, 250, 0);
            // 4
            glColor3f(0, 0, 1);
            glVertex3f(240, 270, 0);
            // 5
            glColor3f(0, 1, 1);
            glVertex3f(355, 230, 0);
            // 6
            glColor3f(0, 1, 1);
            glVertex3f(370, 50, 0);
            // 7
            glColor3f(1, 1, 0);
            glVertex3f(260, 25, 0);
            // 8
            glColor3f(1, 1, 0);
            glVertex3f(240, 150, 0);
            // 9
            glColor3f(0, 1, 0);
            glVertex3f(180, 95, 0);
            // 10
            glColor3f(0, 1, 0);
            glVertex3f(130, 15, 0);
            glEnd();
            return;
        }
        if(type == "GL_POLYGON")
        {
            glBegin(GL_POLYGON);
            // 1
            glColor3f(1, 0, 0);
            glVertex3f(80, 50, 0);
            // 2
            glColor3f(1, 0, 0);
            glVertex3f(65, 175, 0);
            // 3
            glColor3f(0, 0, 1);
            glVertex3f(160, 250, 0);
            // 4
            glColor3f(0, 0, 1);
            glVertex3f(240, 270, 0);
            // 5
            glColor3f(0, 1, 1);
            glVertex3f(355, 230, 0);
            // 6
            glColor3f(0, 1, 1);
            glVertex3f(370, 50, 0);
            // 7
            glColor3f(1, 1, 0);
            glVertex3f(260, 25, 0);
            // 8
            glColor3f(1, 1, 0);
            glVertex3f(240, 150, 0);
            // 9
            glColor3f(0, 1, 0);
            glVertex3f(180, 95, 0);
            // 10
            glColor3f(0, 1, 0);
            glVertex3f(130, 15, 0);
            glEnd();
            return;
        }
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(0,400,0,300,0,400);

////    glMatrixMode(GL_MODELVIEW);
////    glLoadIdentity();
}

void GLWidget::changeType(QString type)
{
    this->type = type;
    glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();
}
