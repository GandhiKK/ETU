#include "graphic.h"
int numr=1;

QGraphicsScene *graphic(BinTree *tree, QGraphicsScene *&scene, bool flag)
{
    if (tree == nullptr)
        return scene;
    scene->clear();
    QPen pen;
    pen.setWidth(6);
    QColor color;
    color.setRgb(70, 70, 170);
    pen.setColor(color);
    QBrush brush (color);
    QFont font;
    font.setFamily("Helvetica");    
    int d = static_cast<int>(pow(2, tree->deep)+2);
    int h = 60;
    int w = 12;
    font.setPointSize(w);
    int width = (w*d)/2;
    paint(scene, tree->root, width/2, h, w, h, pen, brush, font, d, 220, flag);
    numr=1;
    return scene;
}

int paint(QGraphicsScene *&scene, Node *node, int width, int height, int w, int h, QPen &pen, QBrush &brush, QFont &font, int depth, int color_c, bool flag)
{
    if (node == nullptr)
        return 0;
    QString out;
    out += node->info;

    QColor color,color_n;
    color_n.setRgb(140, 140, 140);
    color.setRgb(color_c, color_c, color_c);
    QGraphicsTextItem *elem = new QGraphicsTextItem;
    elem->setPos(width, height);
    elem->setPlainText(out);
    elem->setFont(font);
    pen.setColor(color);
    brush.setColor(color);
    if (node->left != nullptr)
        scene->addLine(width+w/2, height+w, width-(depth/2)*w+w/2, height+h+w, pen);
    if (node->right != nullptr)
        scene->addLine(width+w/2, height+w, width+(depth/2)*w+w/2, height+h+w, pen);
    QGraphicsTextItem *nd = new QGraphicsTextItem;
    nd->setPos(width, height-25);
    nd->setPlainText(out);
    nd->setFont(font);
    nd->setDefaultTextColor("Gray");
    if (flag == true)
    {
       pen.setColor(color_n);
       brush.setColor(color_n);
       scene->addRect(width-w/2, height, w*5/2, w*5/2, pen, brush);
       nd->setPlainText(QString::number(numr));
       numr++;
       scene->addItem(nd);
       paint(scene, node->left, width-(depth/2)*w, height+h, w, h, pen, brush, font, depth/2, color_c, flag);
       paint(scene, node->right, width+(depth/2)*w, height+h, w, h, pen, brush, font, depth/2, color_c, flag);
    }
    else
    {
        scene->addRect(width-w/2, height, w*5/2, w*5/2, pen, brush);
        paint(scene, node->left, width-(depth/2)*w, height+h, w, h, pen, brush, font, depth/2, color_c, flag);
        paint(scene, node->right, width+(depth/2)*w, height+h, w, h, pen, brush, font, depth/2, color_c, flag);
    }
    scene->addItem(elem);
    return 0;
}
