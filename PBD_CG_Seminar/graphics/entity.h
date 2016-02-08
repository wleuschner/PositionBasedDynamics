#ifndef ENTITY_H
#define ENTITY_H
#include "model.h"

class Entity
{
public:
    Entity();
    ~Entity();
    Entity(Model* model);
    Entity(Model* model,QMatrix4x4 mat);
    Entity(Model* model,QMatrix4x4 mat,QVector3D position,QVector3D velocity);

    QMatrix4x4 getMatrix() const;
    void setMatrix(const QMatrix4x4 &value);

    Model* getModel();
    QVector3D getPosition();
    QVector3D getVelocity();

    void release();
    void update();
    void draw(QOpenGLShaderProgram* shader,QMatrix4x4& view);
private:
    QVector3D position;
    QVector3D velocity;
    Model* model;
    QMatrix4x4 mat;
};

#endif // ENTITY_H
