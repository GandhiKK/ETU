#include "glasspanel.h"
#include "glasspanelsides.h"
#include "leg.h"
#include "sitting.h"

#include <ironleg.h>

#ifndef TABLE_H
#define TABLE_H


class Table
{
public:
    float height, length, width;
    Table(float width, float length, float height);
    ~Table();
    QVector<Leg*> legs;
    QVector<Leg*> smallLegs;
    QVector<IronLeg*> ironLegs;
    Sitting * sitting;
    GlassPanel * bigPanel;
    GlassPanelSides * bigPanelSides;
    GlassPanel * smallPanel;
    GlassPanelSides * smallPanelSides;
};

#endif // TABLE_H
