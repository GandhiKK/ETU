#include "sitting.h"

Sitting::Sitting(float width, float length, float height, QVector3D c, float z)
{
    materials = {
        &MaterialConfig::ironLeg,
    };

    QVector<QVector3D> vertices = {
        c + QVector3D(width/2.0f, height/2.0f + z, -length/2.0f),
        c + QVector3D(-width/2.0f, height/2.0f + z, -length/2.0f),
        c + QVector3D(-width/2.0f, height/2.0f + z, length/2.0f),
        c + QVector3D(width/2.0f, height/2.0f + z, length/2.0f),
        c + QVector3D(width/2.0f, -height/2.0f + z, -length/2.0f),
        c + QVector3D(-width/2.0f, -height/2.0f + z, -length/2.0f),
        c + QVector3D(-width/2.0f, -height/2.0f + z, length/2.0f),
        c + QVector3D(width/2.0f, -height/2.0f + z, length/2.0f),
    };
    QVector3D* verticesData = vertices.data();
    edges = {
        {{verticesData[0],
          verticesData[1],
          verticesData[2],
          verticesData[3]}},
        {{verticesData[4],
          verticesData[5],
          verticesData[6],
          verticesData[7]}},
        {{verticesData[5],
          verticesData[6],
          verticesData[2],
          verticesData[1]}},
        {{verticesData[2],
          verticesData[6],
          verticesData[7],
          verticesData[3]}},
        {{verticesData[0],
          verticesData[3],
          verticesData[7],
          verticesData[4]}},
        {{verticesData[0],
          verticesData[4],
          verticesData[5],
          verticesData[1]}},
    };
}
