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
#include "solver.h"

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
    QOpenGLVertexArrayObject vao;
    QGLBuffer vertexBuffer;
    QGLShaderProgram shader;

    QVector3D pos;

    QMatrix4x4 projection;
    QMatrix4x4 view;
    QMatrix4x4 model;

    Solver solver;
};

#endif // CANVAS_H
