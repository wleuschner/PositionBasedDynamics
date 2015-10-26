#ifndef CANVAS_H
#define CANVAS_H

#include <QTimer>
#include <QGLWidget>
#include <QGLFunctions>
#include <QGLBuffer>
#include <QGLShaderProgram>
#include <glm/glm.hpp>

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

    void solveSeidel();
    void solveJacobi();
    bool prepareShader(const QString& vertexShaderPath,const QString& fragmentShaderPath);

    unsigned int vao;

    QGLFunctions* extFunctions;
    QTimer updateTimer;

    QGLBuffer vertexBuffer;
    QGLShaderProgram shader;

    QVector3D pos;

    QMatrix4x4 projection;
    QMatrix4x4 modelview;

};

#endif // CANVAS_H
