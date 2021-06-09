#include "table.h"

Table::Table(float width, float length, float height)
{
    this->width = width;
    this->length = length;
    this->height = height;


    // chair
    float legWidth = width * 0.04f,
            legHeight = height * 0.495f;

    float sittingHeight = height * 0.05f;

    ironLegs.append(new IronLeg(QVector3D(-width/2.0f + legWidth, legHeight, -length/2.0f + legWidth), legWidth, legHeight));
    ironLegs.append(new IronLeg(QVector3D(width/2.0f - legWidth, legHeight, -length/2.0f + legWidth), legWidth, legHeight));
    ironLegs.append(new IronLeg(QVector3D(width/2.0f - legWidth, legHeight, length/2.0f - legWidth), legWidth, legHeight));
    ironLegs.append(new IronLeg(QVector3D(-width/2.0f + legWidth, legHeight, length/2.0f - legWidth), legWidth, legHeight));

    legs.append(new Leg(width, length, sittingHeight, QVector3D(0, legHeight + sittingHeight/2.0f, 0),legHeight));

    float ironBackTop = legHeight * 2.0 ;
    float ironBackHeight =  height * 0.3f;

    ironLegs.append(new IronLeg(QVector3D(-width/2.0f + legWidth, ironBackTop,length/4.0), legWidth, ironBackHeight));
    ironLegs.append(new IronLeg(QVector3D(-width/2.0f + legWidth, ironBackTop,-length/4.0), legWidth, ironBackHeight));
    ironLegs.append(new IronLeg(QVector3D(-width/2.0f + legWidth, ironBackTop,(length/4.0-length/4.0)/2.0), legWidth, ironBackHeight));


    float backHeight = height * 0.45f ;
    float backWidth =  width * 0.1f;

    legs.append(new Leg(backWidth, length/1.1, backHeight, QVector3D(-length/2.0 + 0.35, legHeight + backHeight/2.0f+ironBackHeight, 0),backHeight));

    sitting = new Sitting(width*5.0, length*5.0, sittingHeight, QVector3D(0, legHeight + sittingHeight/2.0f, 0),-0.1);
}

Table::~Table()
{
    for (int i = 0; i < legs.length(); i++) {
        delete legs[i];
    }
    for (int i = 0; i < smallLegs.length(); i++) {
        delete smallLegs[i];
    }
    delete sitting;
}
