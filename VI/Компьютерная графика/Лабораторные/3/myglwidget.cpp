#include "myglwidget.h"

//MyGLWidget::MyGLWidget(QWidget *parent):QGLWidget(parent)
//{
//}


//void MyGLWidget::initializeGL()
//{
//    qglClearColor(Qt::white); // заполняем экран белым цветом
//    glShadeModel(GL_SMOOTH);
//}

//void MyGLWidget::resizeGL(int w, int h)
//{
//    this->winSizeW = w;
//    this->winSizeH = h;
//    glViewport(0,0,w,h);//вывод во всей области виджета
//    glMatrixMode(GL_PROJECTION);//задает матрицу(проекций)
//    glLoadIdentity();//заменяет текущую матрицу на единичную
//    glOrtho(0.0, this->Width, 0.0, this->Height, 0, this->Width);//умножает текущую матрицу на ортогональную ей
//    glMatrixMode(GL_MODELVIEW);//применяет послед операции в стек матричного представления
//    glLoadIdentity();//заменяет текущую матрицу на единичную
//}


//void MyGLWidget::paintGL()
//{
//    glClear(GL_COLOR_BUFFER_BIT);
//    glEnable(GL_SCISSOR_TEST);
//    glEnable(GL_ALPHA_TEST);
//    glEnable(GL_BLEND);

//    glBlendFunc(this->sfactor, this->dfactor);
//    glAlphaFunc(this->func, this->ref);
//    glScissor(this->X * this->winSizeW/100, this->Y*this->winSizeH/100, this->winSizeW*this->Width/100, this->winSizeH*this->Height/100) ;
//    render();
//    glDisable(GL_BLEND);
//    glDisable(GL_ALPHA_TEST);
//    glDisable(GL_SCISSOR_TEST);

//}

float p1=1.0f, p2=1.0f, p3=1.0f, p4=1.0f, p5=1.0f,p6=1.0f;
float g_Weight[] = {p1, p2, p3, p4, p5, p6};
float q_Size;

MyGLWidget::MyGLWidget(QWidget *parent) : QGLWidget(parent)
{
    selected = NULL;
    start = QPointF(0.0,0.0);
    d = 4;
    bones = true;
}


void MyGLWidget::initializeGL()
{
    qglClearColor(Qt::black);
    glShadeModel(GL_SMOOTH);
}


void MyGLWidget::resizeGL(int nWidth, int nHeight)
{
    glViewport(0, 0, nWidth, nHeight);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, nWidth, 0, nHeight, -10.0, 1.0);
}


void MyGLWidget::paintGL() // рисование
{
    glClear ( GL_COLOR_BUFFER_BIT );
    glColor3f(0, 0.8078f, 0.8196f);
    glPointSize(10.0f);

    if(bones){
        glBegin(GL_LINE_STRIP);
        for(auto& p : points){
            glVertex2f(p.x(),p.y());
        }
        glEnd();
        glBegin(GL_POINTS);

        for(auto& p : points){
            glVertex2f(p.x(),p.y());
        }
        glEnd();
    }
    Bspline();
}


void MyGLWidget::mousePressEvent(QMouseEvent *event){

    if(event->button()==Qt::RightButton)
    {
        start=QPointF(event->x(),(-1)*event->y()+520);
        qDebug()<<event->button();
        points.append(start);
        updateGL();
    }
    if(event->button()==Qt::LeftButton)
    {
        qDebug()<<event->pos();
        for(auto& p : points)
        {
            if(QLineF(QPointF(event->x(),(-1)*event->y()+520),p).length()<=20.0f)
            {
                selected=&p;
                qDebug()<<selected;
            }
        }
    }
}


void MyGLWidget::mouseReleaseEvent(QMouseEvent *event){
    selected=NULL;
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event){
    if(selected){
        start.setX(event->x()-start.x());
        start.setY(event->y()-start.y());
        selected->setX(event->x());
        selected->setY((-1)*event->y()+520);
        start=event->pos();
        updateGL();
    }
}


void MyGLWidget::setd(int d){
    this->d = d;
}

void MyGLWidget::CrKnotVector(){
    QVector <float> knots;

    for(int i = 0; i < d; i++)
    {
        knots.append(0.0f);
    }

    for(int i=0; i < points.length()-d+1; i++)
    {
        knots.append((float)i);
    }

    for(int i=0; i< d;i++)
    {
        knots.append((float)(points.length()-d));
    }

    this->knots=knots;
}


float MyGLWidget::B(float x, int n, int d){
    if(d == 0)
    {
        if(knots[n] <= x && x < knots[n+1])
        {
            return 1.0f;
        }
        return 0.0f;
    }
    float a = B(x,n,d-1);
    float b = B(x,n+1,d-1);
    float c = 0.0f, e = 0.0f;

    if(a != 0.0f)
    {
        c = (x - knots[n]) / (knots[n+d] - knots[n]);
    }
    if(b != 0)
    {
        e = (knots[n+d+1] - x) / (knots[n+d+1] - knots[n+1]);
    }
    return (a*c + b*e);
}


void MyGLWidget::Bspline(){
    if(points.length()<6)
    {
        return;
    }

    glColor3d(1,0.8,0);
    glBegin(GL_LINE_STRIP);

    CrKnotVector();

    float xmin=knots[0];
    float xmax=knots.last();

    float delta = xmax - xmin;
    float step = delta/300;

    for(float t = xmin; t < xmax; t += step){
        float x = 0.0f, y = 0.0f;

        for(int i = 0; i < points.length(); i++){
            x+=B(t,i,d) * points[i].x() * g_Weight[i];
            y+=B(t,i,d) * points[i].y() * g_Weight[i];
        }
        glVertex2f(x,y);
    }
    glVertex2f(points.last().x(),points.last().y());
    glEnd();
}

void MyGLWidget::setb(bool f){
    bones = f;
}

void MyGLWidget::clear(){
    this->points.clear();
}
