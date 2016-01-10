#ifndef ENTITY_H
#define ENTITY_H
#include "model.h"

class Entity
{
public:
    Entity();
    Entity(Model* model);
    Entity(Model* model,QMatrix4x4 mat);

    QMatrix4x4 getMatrix() const;
    void setMatrix(const QMatrix4x4 &value);

    Model* getModel();

    void release();
    void draw(QOpenGLShaderProgram& shader,QMatrix4x4& view);
private:
    Model* model;
    QMatrix4x4 mat;
};

#endif // ENTITY_H
