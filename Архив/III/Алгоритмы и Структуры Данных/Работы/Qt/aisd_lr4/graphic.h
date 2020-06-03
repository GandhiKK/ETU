#ifndef GRAPHIC_H
#define GRAPHIC_H
#include "modify.h"

QGraphicsScene *graphic(BinTree *tree, QGraphicsScene *&scene, bool flag);
int paint(QGraphicsScene *&scene, Node *node, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth, int color_c, bool flag);
#endif // GRAPHIC_H
