#ifndef MODIFY_H
#define MODIFY_H
#include "bt.h"

int beginning(QTextEdit *&uiInput, QTextEdit *&uiOutput, QGraphicsScene *&scene, bool flag);
QString processing(QString input, BinTree *&tree, bool flag);
QString modding(Node *root);

#endif // MODIFY_H
