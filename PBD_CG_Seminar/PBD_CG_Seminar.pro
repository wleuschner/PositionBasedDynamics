#-------------------------------------------------
#
# Project created by QtCreator 2015-10-22T01:20:25
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PBD_CG_Seminar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    canvas.cpp \
    light.cpp \
    vertex.cpp \
    camera.cpp \
    constraintparameters.cpp

HEADERS  += mainwindow.h \
    canvas.h \
    light.h \
    vertex.h \
    camera.h \
    constraintparameters.h

FORMS    += mainwindow.ui

LIBS     += -lGLEW

OTHER_FILES += \
    frag.glsl \
    vert.glsl
