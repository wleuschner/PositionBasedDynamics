#ifndef ABSTRACTSCENE_H
#define ABSTRACTSCENE_H
#include "graphics/light.h"
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include "framework/abstractsolver.h"

class AbstractScene
{
public:
    AbstractScene(AbstractSolver* solver);
    virtual ~AbstractScene();

    virtual void reset()=0;
    virtual void update()=0;
    virtual void draw()=0;
    virtual void processKey(int key)=0;

    void resize(float width,float height);

protected:
    void uploadLight(Light& light,int index);
    void uploadLights(QList<Light*> &lights);
    bool prepareShader(QOpenGLShaderProgram* program,const QString& vertexShaderPath,const QString& fragmentShaderPath);

    QMatrix4x4 projection;
    QMatrix4x4 view;

    static QOpenGLVertexArrayObject* vao;
    static QOpenGLShaderProgram* shader;

    AbstractSolver *solver;
};

#endif // ABSTRACTSCENE_H
