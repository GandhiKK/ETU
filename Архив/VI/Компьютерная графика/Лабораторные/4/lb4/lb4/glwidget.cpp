#include "glwidget.h"
#include "fractal.h"



void GLWidget::setLeftAngle(int value)
{
    leftAngle = value;
     this->repaint();
}

void GLWidget::setRightAngle(int value)
{
    rightAngle = value;
     this->repaint();
}

void GLWidget::setIsFilled(bool value)
{
    isFilled = value;
     this->repaint();
}

void GLWidget::setAlpha(int value)
{
    alpha =1.0 - value/100.0f;
     this->repaint();
}

void GLWidget::setHeightSeq(int value)
{
    heightSeq = value;
     this->repaint();
}

void GLWidget::setMainAngle(int value)
{
    mainAngle = value;
    this->repaint();
}

GLWidget::GLWidget(QWidget *parent):
    QGLWidget(parent)
{

}

void GLWidget::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
}
/*
void drawPicture(int N)
{



   // My_Figure *tr = &tr1;
    My_Figure * tr_ptr =new My_Triangle (QVector2D(28,30),
                                           QVector2D(68,30),
                                           QVector2D(50,80),
                                           QVector3D(0.6,0.9,0.1),1, false);
    //makeFractal(tr_ptr, 1, N);
    delete tr_ptr;



}*/

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);

    //glBlendFunc(GL_ZERO+this->SFactor, GL_ZERO+this->DFactor);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_ZERO,GL_ZERO);
    glBlendFunc(this->SFactor, this->DFactor);

    glAlphaFunc(GL_NEVER+this->Func, this->Ref/100.0f);
    glScissor(this->X * this->winSizeW/100, this->Y*this->winSizeH /100, this->winSizeW*this->Width/100, this->winSizeH*this->Height/100) ;

    //
    My_Figure * tr_ptr=nullptr;
    if(this->ComboBox_type == "Треугольники")
    {
         tr_ptr=new My_Triangle (      QVector2D(28,40),
                                       QVector2D(68,40),
                                       QVector2D(50,80),
                                       QVector3D((float)196/255, 0.1, 0.1),this->alpha, this->isFilled);
         makeFractal(tr_ptr, 1, this->heightSeq, this->mainAngle,this->leftAngle, this->rightAngle, N);
    }


    delete tr_ptr;
    // drawPicture(N);*/

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
    glOrtho(0.0, 150.0, -50.0, 100.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}



void GLWidget::changePicture(QString type)
{
    this->ComboBox_type = type;
    this->repaint();
   /* glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();*/
    //this->paintGL();
}


void GLWidget::changeX(int x)
{
    this->X=x;
     this->repaint();
   /* glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();*/
}

void GLWidget::changeY(int y)
{
     this->Y=y;
     this->repaint();
   /* glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();*/
}

void GLWidget::changeWidth(int width)
{
     this->Width=width;
    this->repaint();
}

void GLWidget::changeHeight(int height)
{
     this->Height=height;
    this->repaint();
}

void GLWidget::changeFunc(int f)
{
    this->Func = f;
     this->repaint();
}

void GLWidget::changeRef(int r)
{
    this->Ref = r;
     this->repaint();
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
    exit(1);
}

void GLWidget::changeSfactor(QString s)
{
    this->SFactor=getBlend(s);//+GL_ZERO;
    this->repaint();
}

void GLWidget::changeDfactor(QString d)
{
    this->DFactor=getBlend(d);//+GL_ZERO;
     this->repaint();
}

void GLWidget::changeN(int n)
{
    this->N=n;
     this->repaint();
}


