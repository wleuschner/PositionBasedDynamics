#ifndef CANVAS_H
#define CANVAS_H

#include <QTimer>
#include <QGLWidget>
#include <QGLFunctions>
#include <QGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QGLShaderProgram>

#include "camera.h"
#include "light.h"
#include "entity.h"
#include "abstractsolver.h"

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
    void changeModel(QString file);
    void createCube();
    void createCylinder();
    void createSphere();
    void createTorus();

private:
    void uploadLight(Light& light,int index);

    void solveSeidel();
    void solveJacobi();
    bool prepareShader(const QString& vertexShaderPath,const QString& fragmentShaderPath);

    QGLFunctions* extFunctions;
    QTimer updateTimer;

    Camera camera;
    Light light;
    Entity mesh;
    Entity sphere;
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vertexBuffer;
    QOpenGLShaderProgram shader;

    QVector3D pos;

    QMatrix4x4 projection;
    QMatrix4x4 view;
    QMatrix4x4 model;

    AbstractSolver* solver;
};

#endif // CANVAS_H
