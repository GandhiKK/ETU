#include "fractal.h"
#include "drawfunction.h"
#include "graf_classes/my_line.h"
#include "qmath.h"


void makeFractal(My_Figure *start, int line_width, int length, int mainAngle, int leftAngle,int rightAngle, int N, int curr_n)
{
    QVector <My_Figure*> store;
    store.push_front(start);
    foreach (My_Figure *curr_figure, store) {
        //curr_figure->scale(1.2, QVector2D(100,50));
        curr_figure->moveTo(QVector2D(50,10));
    }
    foreach (My_Figure *curr_figure, makeFractal(store,QVector2D(50,10), line_width,length, mainAngle, leftAngle, rightAngle, N, curr_n)) {
        curr_figure->draw(line_width);
        delete curr_figure;
    }
}

QVector <My_Figure*> makeFractal(QVector <My_Figure*> store,QVector2D centr,  int line_width, int length, int mainAngle, int leftAngle,int rightAngle, int N, int curr_n)
{
    if(curr_n >= N) return store;
        QVector <My_Figure*> left_Tree;
        foreach (My_Figure *curr_figure, store) {
            //curr_figure->turn(mainAngle,centr);
            curr_figure->scale(1.4,centr);
            left_Tree.push_front(curr_figure->copy());
        }
        foreach (My_Figure *curr_figure, left_Tree) {
            curr_figure->scaleY(1.4, centr);
            curr_figure->turn(-70, centr);
            //curr_figure->reflectX(centr);
            curr_figure->moveX(0.5*length*curr_n);
            curr_figure->moveX(1.5*length);
            curr_figure->moveY(-0.3*length*curr_n);
        }



        QVector <My_Figure*> right_Tree;
        foreach (My_Figure *curr_figure, store) {
            //curr_figure->turn(mainAngle,centr);
            //curr_figure->scale(1.1,centr);
            right_Tree.push_front(curr_figure->copy());
        }
        foreach (My_Figure *curr_figure, right_Tree) {
            curr_figure->scaleY(1.4, centr);
            curr_figure->turn(30, centr);
            //curr_figure->reflectX(centr);
            curr_figure->moveX(0.4*length*curr_n);
            curr_figure->moveX(1.4*length);
            curr_figure->moveY(0.2*length*curr_n);
        }

        QVector <My_Figure*> down_left_Tree;
        foreach (My_Figure *curr_figure, store) {
            //curr_figure->turn(mainAngle,centr);
           // curr_figure->scale(1.1,centr);
            down_left_Tree.push_front(curr_figure->copy());
        }
        foreach (My_Figure *curr_figure, down_left_Tree) {
            curr_figure->scale(0.8,centr);
            curr_figure->turn(0, centr);
            curr_figure->scaleY(15, centr);
            curr_figure->reflectX(centr);
            //curr_figure->moveY(0.2*length);
            curr_figure->moveX(0.4*length*curr_n);
            curr_figure->moveX(1.4*length);
            curr_figure->moveY(0.1*length);
        }

//    QVector <My_Figure*> down_right_Tree;
//    foreach (My_Figure *curr_figure, store) {
//        //curr_figure->turn(mainAngle,centr);
//        //curr_figure->scale(1.1,centr);
//        down_right_Tree.push_front(curr_figure->copy());
//    }
//    foreach (My_Figure *curr_figure, down_right_Tree) {
//        curr_figure->scale(1.1,centr);

//        curr_figure->turn(85, centr);
//        curr_figure->scaleX(15, centr);
//        curr_figure->reflectX(centr);
//        curr_figure->moveY(0.4*length);
//        curr_figure->moveX(-0.1*length);

//    }
//    foreach (My_Figure *curr_figure, store) {
//        //curr_figure->turn(mainAngle,centr);
//       // curr_figure->scale(1.8,centr);
//       curr_figure->moveY(1.0*length);

//    }
   // My_Figure * line_ptr = new My_Line(centr, QVector2D(centr.x(), centr.y()-length), store.first()->getColorRGB(), store.first()->getAlpha());
    QVector <My_Figure*> Tree;

//    foreach (My_Figure *curr_figure, store) {   //соединяем получившиеся три части
//        //curr_figure->setColorRGB(QVector3D((float)196/255, (float)0/255, (float)0/255));
//        Tree.push_front(curr_figure);
//    }
    foreach (My_Figure *curr_figure, left_Tree) {
        //curr_figure->setColorRGB(QVector3D((float)196/255, (float)36/255, (float)250/255));
        Tree.push_front(curr_figure);
    }
    foreach (My_Figure *curr_figure, right_Tree) {
        //curr_figure->setColorRGB(QVector3D((float)196/255, (float)196/255, (float)3/255));
        Tree.push_front(curr_figure);
    }
    foreach (My_Figure *curr_figure, down_left_Tree) {
        //curr_figure->setColorRGB(QVector3D((float)120/255, (float)60/255, (float)200/255));
        Tree.push_front(curr_figure);
    }
//    foreach (My_Figure *curr_figure, down_right_Tree) {
//        //curr_figure->setColorRGB(QVector3D((float)240/255, (float)120/255, (float)240/255));
//        Tree.push_front(curr_figure);
//    }
   // Tree.push_front(line_ptr);
    return makeFractal(Tree,QVector2D(centr.x(), centr.y()), line_width,length, mainAngle, leftAngle, rightAngle, N, curr_n+1);

}
/*
void copyTreangle(My_Triangle start, QVector2D sLine, QVector2D fLine, int line_width, int N, int curr_n)
{
    if(curr_n >= N) return;

    My_Triangle finish( start.getPoint1() - (sLine - fLine)/2,
                        start.getPoint2() - (sLine - fLine)/2,
                        start.getPoint3() - (sLine - fLine)/2, start.getColorRGB(),1 );

}*/


/*QVector2D getLineCenter(QVector2D p1, QVector2D p2)
{
    return QVector2D( (p1.x()<p2.x()? p1.x()+(p2.x()-p1.x())/2 : p1.x()-(p1.x()-p2.x())/2) ,
                               (p1.y()<p2.y()? p1.y()+(p2.y()-p1.y())/2 : p1.y()-(p1.y()-p2.y())/2));;
}*/
QVector2D findScale(QVector2D p1, QVector2D p2,float n)  // уменьшает в сторону первой точки
{
    return QVector2D( (p1.x()<p2.x()? p1.x()+(p2.x()-p1.x())/n : p1.x()-(p1.x()-p2.x())/n) ,
                      (p1.y()<p2.y()? p1.y()+(p2.y()-p1.y())/n : p1.y()-(p1.y()-p2.y())/n)); // т.к. действия в положительной плоскости, если нужно в отрицательной, то есно переделать.
}


// доп штуки
void makeLabirint(My_Figure *start, int line_width, int length, int mainAngle, int leftAngle,int rightAngle, int N, int curr_n)
{
    QVector <My_Figure*> store;
    store.push_front(start);
    My_Figure * save =start->copy();\
    save->turn(90);
    store.push_front(save);
    foreach (My_Figure *curr_figure, store) {
        curr_figure->scale(1.2, QVector2D(50,50));
        curr_figure->moveTo(QVector2D(50,50));
    }

    foreach (My_Figure *curr_figure, makeLabirint(store,QVector2D(50,50), line_width,length, mainAngle, leftAngle, rightAngle, N, curr_n)) {
        curr_figure->draw(line_width);
        delete curr_figure;
    }
}

QVector <My_Figure*> makeLabirint(QVector <My_Figure*> store,QVector2D centr,  int line_width, int length, int mainAngle, int leftAngle,int rightAngle, int N, int curr_n)
{
    if(curr_n >= N) return store;
    QVector <My_Figure*> left_Tree;
    foreach (My_Figure *curr_figure, store) {
        //curr_figure->turn(mainAngle,centr);
        curr_figure->scale(2, centr);
        left_Tree.push_front(curr_figure->copy());

    }
    foreach (My_Figure *curr_figure, left_Tree) {

        curr_figure->turn(90, centr);
        //curr_figure->scale(2, centr);

    }

    /*QVector <My_Figure*> right_Tree;
    foreach (My_Figure *curr_figure, store) {
        right_Tree.push_front(curr_figure->copy());
    }
    foreach (My_Figure *curr_figure, right_Tree) {
        curr_figure->scale(3, centr);
        curr_figure->reflectX(centr);
        curr_figure->turn(-rightAngle, centr);
        curr_figure->moveY(-length*2/3);
    }*/
   // My_Figure * line_ptr = new My_Line(centr, QVector2D(centr.x(), centr.y()-length), store.first()->getColorRGB(), store.first()->getAlpha());
    QVector <My_Figure*> Tree;

    foreach (My_Figure *curr_figure, store) {   //соединяем получившиеся три части
        Tree.push_front(curr_figure);
    }
    foreach (My_Figure *curr_figure, left_Tree) {
        Tree.push_front(curr_figure);
    }
    /*foreach (My_Figure *curr_figure, right_Tree) {
        Tree.push_front(curr_figure);
    }
    Tree.push_front(line_ptr);*/
    return makeLabirint(Tree,QVector2D(centr.x(), centr.y()-length), line_width,length, mainAngle, leftAngle, rightAngle, N, curr_n+1);

}
