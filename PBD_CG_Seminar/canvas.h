#ifndef CANVAS_H
#define CANVAS_H

#include <QTimer>
#include <QGLWidget>
#include <QGLFunctions>
#include <QGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QGLShaderProgram>

#include "graphics/camera.h"
#include "graphics/light.h"
#include "graphics/entity.h"
#include "framework/abstractsolver.h"
#include "abstractscene.h"

class Canvas : public QGLWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = 0);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void keyPressEvent(QKeyEvent* event);

signals:

public slots:
    void update();
    void changeSolverLoops(int num);
    void changePressure(double val);
    void changeStretchStiffness(double val);
    void changeCompressStiffness(double val);
    void changeBendingStifness(double val);

    void scene1Triggered();
    void scene2Triggered();
    void scene3Triggered();
private:
    bool initCL();

    QTimer updateTimer;

    AbstractScene *scene;
    AbstractSolver* solver;
};

#endif // CANVAS_H
