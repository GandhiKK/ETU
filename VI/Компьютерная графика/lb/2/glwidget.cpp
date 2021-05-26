#include "glwidget.h"



GLWidget::GLWidget(QWidget *parent):
    QGLWidget(parent)
{

}

void GLWidget::initializeGL()
{
    glClearColor(0.15, 0.15, 0.15, 0.15);
}

void drawPicture(QString type)
{
    if(type == "GL_POINTS")
    {
        glPointSize(6);
        glBegin(GL_POINTS);

        // 1
        glColor4f(1, 0, 0, 0.6);
        glVertex3f(80, 50, 0);
        // 2
        glColor4f(1, 0, 0, 0.5);
        glVertex3f(65, 175, 0);
        // 3
        glColor4f(0, 0, 1, 0.3);
        glVertex3f(160, 250, 0);
        // 4
        glColor4f(0, 0, 1, 0.4);
        glVertex3f(240, 270, 0);
        // 5
        glColor4f(0, 1, 1, 0.5);
        glVertex3f(355, 230, 0);
        // 6
        glColor4f(0, 1, 1, 0.2);
        glVertex3f(370, 50, 0);
        // 7
        glColor4f(1, 1, 0, 0.8);
        glVertex3f(260, 25, 0);
        // 8
        glColor4f(1, 1, 0, 0.2);
        glVertex3f(240, 150, 0);
        // 9
        glColor4f(0, 1, 0, 0.3);
        glVertex3f(180, 95, 0);
        // 10
        glColor4f(0, 1, 0, 0.9);
        glVertex3f(130, 15, 0);

        glEnd();
        return;
    }
    if(type == "GL_LINES")
    {
        glLineWidth(4);
        glBegin(GL_LINES);
        // 1
        glColor4f(1, 0, 0, 0.6);
        glVertex3f(80, 50, 0);
        // 2
        glColor4f(1, 0, 0, 0.5);
        glVertex3f(65, 175, 0);
        // 3
        glColor4f(0, 0, 1, 0.3);
        glVertex3f(160, 250, 0);
        // 4
        glColor4f(0, 0, 1, 0.4);
        glVertex3f(240, 270, 0);
        // 5
        glColor4f(0, 1, 1, 0.5);
        glVertex3f(355, 230, 0);
        // 6
        glColor4f(0, 1, 1, 0.2);
        glVertex3f(370, 50, 0);
        // 7
        glColor4f(1, 1, 0, 0.8);
        glVertex3f(260, 25, 0);
        // 8
        glColor4f(1, 1, 0, 0.2);
        glVertex3f(240, 150, 0);
        // 9
        glColor4f(0, 1, 0, 0.3);
        glVertex3f(180, 95, 0);
        // 10
        glColor4f(0, 1, 0, 0.9);
        glVertex3f(130, 15, 0);
        glEnd();
        return;
    }
    if(type == "GL_LINE_STRIP")
    {
        glLineWidth(4);
        glBegin(GL_LINE_STRIP);
        // 1
        glColor4f(1, 0, 0, 0.6);
        glVertex3f(80, 50, 0);
        // 2
        glColor4f(1, 0, 0, 0.5);
        glVertex3f(65, 175, 0);
        // 3
        glColor4f(0, 0, 1, 0.3);
        glVertex3f(160, 250, 0);
        // 4
        glColor4f(0, 0, 1, 0.4);
        glVertex3f(240, 270, 0);
        // 5
        glColor4f(0, 1, 1, 0.5);
        glVertex3f(355, 230, 0);
        // 6
        glColor4f(0, 1, 1, 0.2);
        glVertex3f(370, 50, 0);
        // 7
        glColor4f(1, 1, 0, 0.8);
        glVertex3f(260, 25, 0);
        // 8
        glColor4f(1, 1, 0, 0.2);
        glVertex3f(240, 150, 0);
        // 9
        glColor4f(0, 1, 0, 0.3);
        glVertex3f(180, 95, 0);
        // 10
        glColor4f(0, 1, 0, 0.9);
        glVertex3f(130, 15, 0);
        glEnd();
        return;
    }
    if(type == "GL_LINE_LOOP")
    {
        glLineWidth(4);
        glBegin(GL_LINE_LOOP);
        // 1
        glColor4f(1, 0, 0, 0.6);
        glVertex3f(80, 50, 0);
        // 2
        glColor4f(1, 0, 0, 0.5);
        glVertex3f(65, 175, 0);
        // 3
        glColor4f(0, 0, 1, 0.3);
        glVertex3f(160, 250, 0);
        // 4
        glColor4f(0, 0, 1, 0.4);
        glVertex3f(240, 270, 0);
        // 5
        glColor4f(0, 1, 1, 0.5);
        glVertex3f(355, 230, 0);
        // 6
        glColor4f(0, 1, 1, 0.2);
        glVertex3f(370, 50, 0);
        // 7
        glColor4f(1, 1, 0, 0.8);
        glVertex3f(260, 25, 0);
        // 8
        glColor4f(1, 1, 0, 0.2);
        glVertex3f(240, 150, 0);
        // 9
        glColor4f(0, 1, 0, 0.3);
        glVertex3f(180, 95, 0);
        // 10
        glColor4f(0, 1, 0, 0.9);
        glVertex3f(130, 15, 0);
        glEnd();
        return;
    }
    if(type == "GL_TRIANGLES")
    {
        glBegin(GL_TRIANGLES);
        // 1
        glColor4f(1, 0, 0, 0.6);
        glVertex3f(80, 50, 0);
        // 2
        glColor4f(1, 0, 0, 0.5);
        glVertex3f(65, 175, 0);
        // 3
        glColor4f(0, 0, 1, 0.3);
        glVertex3f(160, 250, 0);
        // 4
        glColor4f(0, 0, 1, 0.4);
        glVertex3f(240, 270, 0);
        // 5
        glColor4f(0, 1, 1, 0.5);
        glVertex3f(355, 230, 0);
        // 6
        glColor4f(0, 1, 1, 0.2);
        glVertex3f(370, 50, 0);
        // 7
        glColor4f(1, 1, 0, 0.8);
        glVertex3f(260, 25, 0);
        // 8
        glColor4f(1, 1, 0, 0.2);
        glVertex3f(240, 150, 0);
        // 9
        glColor4f(0, 1, 0, 0.3);
        glVertex3f(180, 95, 0);
        // 10
        glColor4f(0, 1, 0, 0.9);
        glVertex3f(130, 15, 0);
        glEnd();
        return;
    }
    if(type == "GL_TRIANGLE_STRIP")
    {
        glBegin(GL_TRIANGLE_STRIP);
        // 1
        glColor4f(1, 0, 0, 0.6);
        glVertex3f(80, 50, 0);
        // 2
        glColor4f(1, 0, 0, 0.5);
        glVertex3f(65, 175, 0);
        // 3
        glColor4f(0, 0, 1, 0.3);
        glVertex3f(160, 250, 0);
        // 4
        glColor4f(0, 0, 1, 0.4);
        glVertex3f(240, 270, 0);
        // 5
        glColor4f(0, 1, 1, 0.5);
        glVertex3f(355, 230, 0);
        // 6
        glColor4f(0, 1, 1, 0.2);
        glVertex3f(370, 50, 0);
        // 7
        glColor4f(1, 1, 0, 0.8);
        glVertex3f(260, 25, 0);
        // 8
        glColor4f(1, 1, 0, 0.2);
        glVertex3f(240, 150, 0);
        // 9
        glColor4f(0, 1, 0, 0.3);
        glVertex3f(180, 95, 0);
        // 10
        glColor4f(0, 1, 0, 0.9);
        glVertex3f(130, 15, 0);
        glEnd();
        return;
    }
    if(type == "GL_TRIANGLE_FAN")
    {
        glBegin(GL_TRIANGLE_FAN);
        // 1
        glColor4f(1, 0, 0, 0.6);
        glVertex3f(80, 50, 0);
        // 2
        glColor4f(1, 0, 0, 0.5);
        glVertex3f(65, 175, 0);
        // 3
        glColor4f(0, 0, 1, 0.3);
        glVertex3f(160, 250, 0);
        // 4
        glColor4f(0, 0, 1, 0.4);
        glVertex3f(240, 270, 0);
        // 5
        glColor4f(0, 1, 1, 0.5);
        glVertex3f(355, 230, 0);
        // 6
        glColor4f(0, 1, 1, 0.2);
        glVertex3f(370, 50, 0);
        // 7
        glColor4f(1, 1, 0, 0.8);
        glVertex3f(260, 25, 0);
        // 8
        glColor4f(1, 1, 0, 0.2);
        glVertex3f(240, 150, 0);
        // 9
        glColor4f(0, 1, 0, 0.3);
        glVertex3f(180, 95, 0);
        // 10
        glColor4f(0, 1, 0, 0.9);
        glVertex3f(130, 15, 0);
        glEnd();
        return;
    }
    if(type == "GL_QUADS")
    {
        glBegin(GL_QUADS);
        // 1
        glColor4f(1, 0, 0, 0.6);
        glVertex3f(80, 50, 0);
        // 2
        glColor4f(1, 0, 0, 0.5);
        glVertex3f(65, 175, 0);
        // 3
        glColor4f(0, 0, 1, 0.3);
        glVertex3f(160, 250, 0);
        // 4
        glColor4f(0, 0, 1, 0.4);
        glVertex3f(240, 270, 0);
        // 5
        glColor4f(0, 1, 1, 0.5);
        glVertex3f(355, 230, 0);
        // 6
        glColor4f(0, 1, 1, 0.2);
        glVertex3f(370, 50, 0);
        // 7
        glColor4f(1, 1, 0, 0.8);
        glVertex3f(260, 25, 0);
        // 8
        glColor4f(1, 1, 0, 0.2);
        glVertex3f(240, 150, 0);
        // 9
        glColor4f(0, 1, 0, 0.3);
        glVertex3f(180, 95, 0);
        // 10
        glColor4f(0, 1, 0, 0.9);
        glVertex3f(130, 15, 0);
        glEnd();
        return;
    }
    if(type == "GL_QUAD_STRIP")
    {
        glBegin(GL_QUAD_STRIP);
        // 1
        glColor4f(1, 0, 0, 0.6);
        glVertex3f(80, 50, 0);
        // 2
        glColor4f(1, 0, 0, 0.5);
        glVertex3f(65, 175, 0);
        // 3
        glColor4f(0, 0, 1, 0.3);
        glVertex3f(160, 250, 0);
        // 4
        glColor4f(0, 0, 1, 0.4);
        glVertex3f(240, 270, 0);
        // 5
        glColor4f(0, 1, 1, 0.5);
        glVertex3f(355, 230, 0);
        // 6
        glColor4f(0, 1, 1, 0.2);
        glVertex3f(370, 50, 0);
        // 7
        glColor4f(1, 1, 0, 0.8);
        glVertex3f(260, 25, 0);
        // 8
        glColor4f(1, 1, 0, 0.2);
        glVertex3f(240, 150, 0);
        // 9
        glColor4f(0, 1, 0, 0.3);
        glVertex3f(180, 95, 0);
        // 10
        glColor4f(0, 1, 0, 0.9);
        glVertex3f(130, 15, 0);
        glEnd();
        return;
    }
    if(type == "GL_POLYGON")
    {
        glBegin(GL_POLYGON);
        // 1
        glColor4f(1, 0, 0, 0.6);
        glVertex3f(80, 50, 0);
        // 2
        glColor4f(1, 0, 0, 0.5);
        glVertex3f(65, 175, 0);
        // 3
        glColor4f(0, 0, 1, 0.3);
        glVertex3f(160, 250, 0);
        // 4
        glColor4f(0, 0, 1, 0.4);
        glVertex3f(240, 270, 0);
        // 5
        glColor4f(0, 1, 1, 0.5);
        glVertex3f(355, 230, 0);
        // 6
        glColor4f(0, 1, 1, 0.2);
        glVertex3f(370, 50, 0);
        // 7
        glColor4f(1, 1, 0, 0.8);
        glVertex3f(260, 25, 0);
        // 8
        glColor4f(1, 1, 0, 0.2);
        glVertex3f(240, 150, 0);
        // 9
        glColor4f(0, 1, 0, 0.3);
        glVertex3f(180, 95, 0);
        // 10
        glColor4f(0, 1, 0, 0.9);
        glVertex3f(130, 15, 0);
        glEnd();
        return;
    }

}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(this->SFactor, this->DFactor);
    glAlphaFunc(GL_NEVER+this->Func, this->Ref/100.0f);
    glScissor(this->X * this->winSizeW/100,
              this->Y*this->winSizeH /100,
              this->winSizeW*this->Width/100,
              this->winSizeH*this->Height/100) ;
    drawPicture(this->ComboBox_type);
    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_SCISSOR_TEST);
}

void GLWidget::resizeGL(int w, int h)
{
    this->winSizeW = w;
    this->winSizeH =h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 400.0, 0.0, 300.0, 0, 400.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void GLWidget::changeShapePicture(QString type)
{
    this->ComboBox_type = type;
    glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();
}


void GLWidget::changeX(int x)
{
    this->X=x;
    glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();
}

void GLWidget::changeY(int y)
{
     this->Y=y;
    glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();
}

void GLWidget::changeWidth(int width)
{
     this->Width=width;
    glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();
}

void GLWidget::changeHeight(int height)
{
     this->Height=height;
    glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();
}

void GLWidget::changeFunc(int f)
{
    this->Func = f;
    glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();
}

void GLWidget::changeRef(int r)
{
    this->Ref = r;
    glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();
}
int getBlend(QString m)
{
    if(m == "GL_ZERO")return GL_ZERO;
    if(m == "GL_ONE")return GL_ONE;
    if(m == "GL_DST_COLOR")return GL_DST_COLOR;
    if(m == "GL_ONE_MINUS_DST_COLOR")return GL_ONE_MINUS_DST_COLOR;
    if(m == "GL_SRC_ALPHA")return GL_SRC_ALPHA;
    if(m == "GL_ONE_MINUS_SRC_ALPHA")return GL_ONE_MINUS_SRC_ALPHA;
    if(m == "GL_DST_ALPHA")return GL_DST_ALPHA;
    if(m == "GL_ONE_MINUS_DST_ALPHA")return GL_ONE_MINUS_DST_ALPHA;
    if(m == "GL_SRC_ALPHA_SATURATE")return GL_SRC_ALPHA_SATURATE;
    if(m == "GL_SRC_COLOR") return GL_SRC_COLOR;
    if(m == "GL_ONE_MINUS_SRC_COLOR") return GL_ONE_MINUS_SRC_COLOR;
}

void GLWidget::changeSfactor(QString s)
{
    this->SFactor=getBlend(s);//+GL_ZERO;
    glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();
}

void GLWidget::changeDfactor(QString d)
{
    this->DFactor=getBlend(d);//+GL_ZERO;
    glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();
}


