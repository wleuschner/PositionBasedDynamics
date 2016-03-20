#include <GL/glew.h>
#include "canvas.h"
#include <QDebug>
#include <QGLWidget>
#include <QKeyEvent>
#include <QMatrix3x3>
#include "solvers/solver.h"
#include "scenes/scene.h"
#include "scenes/scene2.h"
#include "scenes/scene3.h"

Canvas::Canvas(QWidget *parent) :
    QGLWidget(parent)
{
    QGLFormat format;
    format.setVersion(3,4);
    format.setProfile(QGLFormat::CoreProfile);
    format.setSampleBuffers(true);
    setFormat(format);
    solver = new Solver();
}

void Canvas::initializeGL()
{
    QGLFormat format = QGLWidget::format();
    if(!format.sampleBuffers())
    {
        qWarning()<<"Could not enable sample buffers";
    }
    if(glewInit()!=GLEW_OK)
    {
        qWarning()<<"Could not init GLEW";
    }
    glCullFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearColor(1.0,1.0,1.0,1.0);

    scene = new Scene(solver);

    resize(800,600);

    connect(&updateTimer,SIGNAL(timeout()),this,SLOT(update()));
    updateTimer.setSingleShot(false);
    updateTimer.setInterval(15);
    updateTimer.start();
}

void Canvas::resizeGL(int w, int h)
{
    scene->resize(w,h);
}

void Canvas::paintGL()
{
    scene->draw();
}

void Canvas::keyPressEvent(QKeyEvent* event)
{
    scene->processKey(event->key());
}

void Canvas::update()
{
    scene->update();
    updateGL();
}

bool Canvas::initCL()
{
}

void Canvas::changeSolverLoops(int num)
{
    solver->setSolverLoops(num);
}

void Canvas::changePressure(double val)
{
    solver->setPressure(val);
}

void Canvas::changeStretchStiffness(double val)
{
    solver->setStretchStiffness(val);
}

void Canvas::changeCompressStiffness(double val)
{
    solver->setCompressStiffness(val);
}

void Canvas::changeBendingStifness(double val)
{
    solver->setBendStiffness(val);
}

void Canvas::scene1Triggered()
{
    delete scene;
    scene = new Scene(solver);
}

void Canvas::scene2Triggered()
{
    delete scene;
    scene = new Scene2(solver);
}

void Canvas::scene3Triggered()
{
    delete scene;
    scene = new Scene3(solver);
}
