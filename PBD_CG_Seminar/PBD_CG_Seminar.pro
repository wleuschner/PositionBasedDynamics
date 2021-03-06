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
    graphics/light.cpp \
    geometry/vertex.cpp \
    graphics/camera.cpp \
    framework/constraintparameters.cpp \
    graphics/model.cpp \
    solvers/solver.cpp \
    geometry/face.cpp \
    graphics/entity.cpp \
    structs/spatialhash.cpp \
    framework/abstractsolver.cpp \
    framework/constraints.cpp \
    graphics/material.cpp \
    geometry/edge.cpp \
    solvers/jacobisolver.cpp \
    scenes/scene.cpp \
    abstractscene.cpp \
    scenes/scene2.cpp \
    scenes/scene3.cpp \
    collisionsphereconstraint.cpp

HEADERS  += mainwindow.h \
    canvas.h \
    graphics/light.h \
    geometry/vertex.h \
    graphics/camera.h \
    framework/constraintparameters.h \
    graphics/model.h \
    solvers/solver.h \
    geometry/face.h \
    graphics/entity.h \
    structs/spatialhash.h \
    framework/abstractsolver.h \
    framework/constraints.h \
    graphics/material.h \
    geometry/edge.h \
    solvers/jacobisolver.h \
    scenes/scene.h \
    abstractscene.h \
    scenes/scene2.h \
    scenes/scene3.h \
    collisionsphereconstraint.h

FORMS    += mainwindow.ui

LIBS     += -lGLEW -lassimp

OTHER_FILES += \
    frag.glsl \
    vert.glsl \
    shadow.vert \
    shadow.frag

CONFIG += c++11

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp
