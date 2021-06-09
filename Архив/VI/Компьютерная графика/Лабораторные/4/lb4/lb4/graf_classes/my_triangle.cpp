#include "my_triangle.h"
#include <QtMath>
#include "fractal.h"


QVector2D My_Triangle::getPoint1() const
{
    return point1;
}

void My_Triangle::setPoint1(const QVector2D &value)
{
    point1 = value;
}

QVector2D My_Triangle::getPoint2() const
{
    return point2;
}

void My_Triangle::setPoint2(const QVector2D &value)
{
    point2 = value;
}
void My_Triangle::moveY(int value)
{
    this->point1.setY(this->point1.y() + value);
    this->point2.setY(this->point2.y() + value);
    this->point3.setY(this->point3.y() + value);
}
void My_Triangle::moveX(int value)
{
    this->point1.setX(this->point1.x() + value);
    this->point2.setX(this->point2.x() + value);
    this->point3.setX(this->point3.x() + value);
}

void My_Triangle::reflectX(QVector2D around)
{
   // this->point1 =findScale(center, this->getPoint1(), 1);
   // this->point2 =findScale(center, this->getPoint2(), 1);
    this->point1 = QVector2D((  this->getPoint1().x()<around.x() ?
                                around.x()+(around.x()-this->getPoint1().x()) :
                                around.x()-(this->getPoint1().x()-around.x())),this->getPoint1().y());
    this->point2 = QVector2D((  this->getPoint2().x()<around.x() ?
                                around.x()+(around.x()-this->getPoint2().x()) :
                                around.x()-(this->getPoint2().x()-around.x())),this->getPoint2().y());
    this->point3 = QVector2D((  this->getPoint3().x()<around.x() ?
                                around.x()+(around.x()-this->getPoint3().x()) :
                                around.x()-(this->getPoint3().x()-around.x())),this->getPoint3().y());

}

QVector2D My_Triangle::getPoint3() const
{
    return point3;
}

void My_Triangle::setPoint3(const QVector2D &value)
{
    point3 = value;
}

QVector3D My_Triangle::getColorRGB() const
{
    return colorRGB;
}

void My_Triangle::setColorRGB(const QVector3D &value)
{
    colorRGB = value;
}

float My_Triangle::getAlpha() const
{
    return alpha;
}

void My_Triangle::setAlpha(float value)
{
    alpha = value;
}

My_Triangle::My_Triangle(QVector2D p1, QVector2D p2, QVector2D p3, QVector3D c_rgb, float alpha, bool filled ): My_Figure()
{
    this->point1 =p1;
    this->point2 =p2;
    this->point3 =p3;

    this->colorRGB=c_rgb;
    this->alpha=alpha;
    this->filled =filled;
}

void My_Triangle::draw(int line_width)
{
    if(this->filled)
    {
    glBegin(GL_TRIANGLES);
    glColor4f(this->colorRGB.x(), this->colorRGB.y(), this->colorRGB.z(), this->alpha);
    glVertex3f(this->point1.x(), this->point1.y(),0);
    glVertex3f( this->point2.x(), this->point2.y(), 0);
    glVertex3f(this->point3.x(), this->point3.y(),0);
    glEnd();
    }
    else
    {
        glLineWidth(line_width);
        glBegin(GL_LINE_LOOP);
        glColor4f(this->colorRGB.x(), this->colorRGB.y(), this->colorRGB.z(), this->alpha);
        glVertex3f(this->point1.x(), this->point1.y(),0);
        glVertex3f( this->point2.x(), this->point2.y(), 0);
        glVertex3f(this->point3.x(), this->point3.y(),0);
        glEnd();
    }
}

void My_Triangle::turn(float angle, QVector2D center)
{
    angle=qDegreesToRadians(angle);
    this->point1 =QVector2D(center.x() + (this->point1.x() - center.x())*qCos(angle)- (this->point1.y()-center.y())*qSin(angle),
                            center.y() + (this->point1.x() - center.x())*qSin(angle)+ (this->point1.y()-center.y())*qCos(angle));
    this->point2 =QVector2D(center.x() + (this->point2.x() - center.x())*qCos(angle)- (this->point2.y()-center.y())*qSin(angle),
                            center.y() + (this->point2.x() - center.x())*qSin(angle)+ (this->point2.y()-center.y())*qCos(angle));
    this->point3 =QVector2D(center.x() + (this->point3.x() - center.x())*qCos(angle)- (this->point3.y()-center.y())*qSin(angle),
                            center.y() + (this->point3.x() - center.x())*qSin(angle)+ (this->point3.y()-center.y())*qCos(angle));

   /* return My_Triangle( QVector2D(center.x() + (this->point1.x() - center.x())*qCos(angle)- (this->point1.y()-center.y())*qSin(angle),
                                  center.y() + (this->point1.x() - center.x())*qSin(angle)+ (this->point1.y()-center.y())*qCos(angle)),
                        QVector2D(center.x() + (this->point2.x() - center.x())*qCos(angle)- (this->point2.y()-center.y())*qSin(angle),
                                  center.y() + (this->point2.x() - center.x())*qSin(angle)+ (this->point2.y()-center.y())*qCos(angle)),
                        QVector2D(center.x() + (this->point3.x() - center.x())*qCos(angle)- (this->point3.y()-center.y())*qSin(angle),
                                  center.y() + (this->point3.x() - center.x())*qSin(angle)+ (this->point3.y()-center.y())*qCos(angle)),
                        QVector3D(this->colorRGB.x(), this->colorRGB.y(), this->colorRGB.z()), this->alpha, false);*/
}


void My_Triangle::scale(float n, QVector2D center)// уменьшает в n раз относительно точки center
{
    this->point1 =findScale(center, this->getPoint1(), n);
    this->point2 =findScale(center, this->getPoint2(), n);
    this->point3 =findScale(center, this->getPoint3(), n);
    /*return  My_Triangle( findScale(center, this->getPoint1(), n),
                        findScale(center, this->getPoint2(), n),
                        findScale(center, this->getPoint3(), n),
                        QVector3D(this->colorRGB.x(), this->colorRGB.y(), this->colorRGB.z()), this->alpha, false);*/

}

void My_Triangle::scaleX(float n, QVector2D center)
{
    this->point1 = QVector2D(( this->point1.x() - center.x())/n +center.x() , this->point1.y());
    this->point2 = QVector2D(( this->point2.x() - center.x())/n +center.x() , this->point2.y());
    this->point3 = QVector2D(( this->point3.x() - center.x())/n +center.x() , this->point3.y());
   // this->point2 =findScale(center, this->getPoint2(), n);
    //this->point3 =findScale(center, this->getPoint3(), n);
}

void My_Triangle::scaleY(float n, QVector2D center)
{
    this->point1 = QVector2D(this->point1.x(),( this->point1.y() - center.y())/n +center.y());
    this->point2 = QVector2D(this->point2.x(),( this->point2.y() - center.y())/n +center.y());
    this->point3 = QVector2D(this->point3.x(),( this->point3.y() - center.y())/n +center.y());
   // this->point2 =findScale(center, this->getPoint2(), n);
    //this->point3 =findScale(center, this->getPoint3(), n);
}
void My_Triangle::moveTo(QVector2D point)
{
    QVector2D save= (this->point1 - this->point2)/2;
    this->point2 = point+ save - this->point1 +this->point2;
    this->point3 =point+ save - this->point1 +this->point3;
    this->point1 =point+ save;
   /* return new My_Triangle( point,
                            point - this->point1 +this->point2,
                            point - this->point1 +this->point3,
                            this->colorRGB, this->alpha, this->filled);*/
}

void My_Triangle::moveFromTo(QVector2D pointFrom, QVector2D pointTo)
{
    QVector2D save= (this->point1 - this->point2)/2;
    this->point2 = pointFrom - pointTo + save - this->point1 +this->point2;
    this->point3 =pointFrom - pointTo +  save - this->point1 +this->point3;
    this->point1 =pointFrom - pointTo +  save;
}

float My_Triangle::perimeter()
{
    return (this->point1-this->point2).length()+
           (this->point2-this->point3).length()+
           (this->point3-this->point1).length();
}

My_Figure *My_Triangle::copy()
{
    return new My_Triangle( this->point1,
                            this->point2,
                            this->point3,
                            this->colorRGB, this->alpha, this->filled);
}
