#ifndef SITTING_H
#define SITTING_H

#include "figure.h"

class Sitting : public Figure
{
public:
    Sitting(float width = 1, float length = 1, float height = 1, QVector3D c = QVector3D(0, 0, 0), float z = 0);
};



#endif // SITTING_H
