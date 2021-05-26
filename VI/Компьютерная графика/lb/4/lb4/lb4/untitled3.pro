#-------------------------------------------------
#
# Project created by QtCreator 2017-03-05T22:14:30
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled3
TEMPLATE = app

LIBS += -lglu32 -lopengl32
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    graf_classes/my_figure.cpp \
    graf_classes/my_line.cpp \
    graf_classes/my_quad.cpp \
    graf_classes/my_triangle.cpp \
    drawfunction.cpp \
    fractal.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    graf_classes/my_figure.h \
    graf_classes/my_line.h \
    graf_classes/my_quad.h \
    graf_classes/my_triangle.h \
    drawfunction.h \
    fractal.h

FORMS    += mainwindow.ui

DISTFILES += \
    ../../kg_labs/computer_graphic_lb3/styles/styles.css \
    styles/styles.css

RESOURCES += \
    styles.qrc
