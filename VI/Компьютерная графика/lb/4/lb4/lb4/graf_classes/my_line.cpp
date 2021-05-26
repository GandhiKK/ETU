#include "my_line.h"
#include <QtMath>
#include "fractal.h"

float My_Line::getAlpha() const
{
    return alpha;
}

void My_Line::setAlpha(float value)
{
    alpha = value;
}

My_Line::My_Line(QVector2D p1, QVector2D p2, QVector3D c_rgb, float alpha ): My_Figure()
{
    this->point1 =p1;
    this->point2 =p2;
    this->colorRGB=c_rgb;
    this->alpha=alpha;
}
QVector2D My_Line::getPoint1() const
{
    return point1;
}
void My_Line::setPoint1(const QVector2D &value)
{
    point1 = value;
}

QVector2D My_Line::getPoint2() const
{
    return point2;
}

void My_Line::setPoint2(const QVector2D &value)
{
    point2 = value;
}


QVector3D My_Line::getColorRGB() const
{
    return colorRGB;
}

void My_Line::setColorRGB(const QVector3D &value)
{
    colorRGB = value;
}



void My_Line::draw(int line_width)
{
    glLineWidth(line_width);
    glBegin(GL_LINE_STRIP);
    glColor4f(this->colorRGB.x(), this->colorRGB.y(), this->colorRGB.z(), this->alpha);
    glVertex3f(this->point1.x(), this->point1.y(),0);
    glVertex3f( this->point2.x(), this->point2.y(), 0);
    //glVertex3f(this->point3.x(), this->point3.y(),0);
    glEnd();

}

void My_Line::turn(float angle, QVector2D center)
{
    angle=qDegreesToRadians(angle);
    this->point1 =QVector2D(center.x() + (this->point1.x() - center.x())*qCos(angle)- (this->point1.y()-center.y())*qSin(angle),
                            center.y() + (this->point1.x() - center.x())*qSin(angle)+ (this->point1.y()-center.y())*qCos(angle));
    this->point2 =QVector2D(center.x() + (this->point2.x() - center.x())*qCos(angle)- (this->point2.y()-center.y())*qSin(angle),
                            center.y() + (this->point2.x() - center.x())*qSin(angle)+ (this->point2.y()-center.y())*qCos(angle));

   /* return My_Line( QVector2D(center.x() + (this->point1.x() - center.x())*qCos(angle)- (this->point1.y()-center.y())*qSin(angle),
                                  center.y() + (this->point1.x() - center.x())*qSin(angle)+ (this->point1.y()-center.y())*qCos(angle)),
                        QVector2D(center.x() + (this->point2.x() - center.x())*qCos(angle)- (this->point2.y()-center.y())*qSin(angle),
                                  center.y() + (this->point2.x() - center.x())*qSin(angle)+ (this->point2.y()-center.y())*qCos(angle)),
                        QVector2D(center.x() + (this->point3.x() - center.x())*qCos(angle)- (this->point3.y()-center.y())*qSin(angle),
                                  center.y() + (this->point3.x() - center.x())*qSin(angle)+ (this->point3.y()-center.y())*qCos(angle)),
                        QVector3D(this->colorRGB.x(), this->colorRGB.y(), this->colorRGB.z()), this->alpha, false);*/
}


void My_Line::scale(float n, QVector2D center)// уменьшает в n раз относительно точки center
{
    this->point1 =findScale(center, this->getPoint1(), n);
    this->point2 =findScale(center, this->getPoint2(), n);
    /*return  My_Line( findScale(center, this->getPoint1(), n),
                        findScale(center, this->getPoint2(), n),
                        findScale(center, this->getPoint3(), n),
                        QVector3D(this->colorRGB.x(), this->colorRGB.y(), this->colorRGB.z()), this->alpha, false);*/

}

void My_Line::scaleX(float n, QVector2D center)
{
    this->point1 = QVector2D(( this->point1.x() - center.x())/n +center.x() , this->point1.y());
    this->point2 = QVector2D(( this->point2.x() - center.x())/n +center.x() , this->point2.y());
}
void My_Line::scaleY(float n, QVector2D center)
{
    this->point1 = QVector2D(this->point1.x(),( this->point1.y() - center.y())/n +center.y());
    this->point2 = QVector2D( this->point2.x(),( this->point2.y() - center.y())/n +center.y());
}
void My_Line::moveTo(QVector2D point)
{
    QVector2D save= (this->point1 - this->point2)/2;
    this->point2 = point+ save - this->point1 +this->point2;
    this->point1 =point+ save;
}

float My_Line::perimeter()
{
    return (this->point1-this->point2).length();

}

void My_Line::moveY(int value)
{
    this->point1.setY(this->point1.y() + value);
    this->point2.setY(this->point2.y() + value);
}
void My_Line::moveX(int value)
{
    this->point1.setX(this->point1.x() + value);
    this->point2.setX(this->point2.x() + value);
}
void My_Line::reflectX(QVector2D around)
{
   // this->point1 =findScale(center, this->getPoint1(), 1);
   // this->point2 =findScale(center, this->getPoint2(), 1);
    this->point1 = QVector2D((  this->getPoint1().x()<around.x() ?
                                around.x()+(around.x()-this->getPoint1().x()) :
                                around.x()-(this->getPoint1().x()-around.x())),this->getPoint1().y());
    this->point2 = QVector2D((  this->getPoint2().x()<around.x() ?
                                around.x()+(around.x()-this->getPoint2().x()) :
                                around.x()-(this->getPoint2().x()-around.x())),this->getPoint2().y());

}
My_Figure *My_Line::copy()
{
    return new My_Line( this->point1,
                        this->point2,
                        this->colorRGB, this->alpha);
}

void My_Line::moveFromTo(QVector2D pointFrom, QVector2D pointTo)
{
    QVector2D save= (this->point1 - this->point2)/2;
    this->point2 = pointFrom - pointTo + save - this->point1 +this->point2;
    this->point1 =pointFrom - pointTo +  save;
}

