#include "mywidget.h"

//веса
float p1=1.0f, p2=1.0f, p3=1.0f, p4=1.0f, p5=1.0f, p6=1.0f;
float g_Weight[] = {p1, p2, p3, p4, p5, p6};
float q_Size;

MyWidget::MyWidget(QWidget *parent) // конструктор
    : QGLWidget(parent)
{
    selected = NULL;
    start = QPointF(0.0,0.0);
    d = 4;
    bones = true;
}


void MyWidget::initializeGL()
{
    qglClearColor(Qt::white); // заполняем экран белым цветом
    glShadeModel(GL_SMOOTH);
}


void MyWidget::resizeGL(int nWidth, int nHeight)
{
    glViewport(0, 0, nWidth, nHeight);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, nWidth, 0, nHeight, -10.0, 1.0);
}


void MyWidget::paintGL() // рисование
{
    glClear ( GL_COLOR_BUFFER_BIT );
    glColor3f(1.0,0.0,1.0);
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
    NURBspline();
}


void MyWidget::mousePressEvent(QMouseEvent *event){

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


void MyWidget::mouseReleaseEvent(QMouseEvent *event){
    selected=NULL;
}

void MyWidget::mouseMoveEvent(QMouseEvent *event){
    if(selected){
        start.setX(event->x()-start.x());
        start.setY(event->y()-start.y());
        selected->setX(event->x());
        selected->setY((-1)*event->y()+520);
        start=event->pos();
        updateGL();
    }
}

void MyWidget::setd(int d){
    this->d = d;
}

void MyWidget::CrKnotVector(){
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

float MyWidget::B(float x, int n, int d){
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


void MyWidget::NURBspline(){
    if(points.length() < 6)
    {
        return;
    }
    glColor3d(0,1,1);
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

void MyWidget::setb(bool f){
    bones = f;
}

void MyWidget::clear(){
    this->points.clear();
}

