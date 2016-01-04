#include "entity.h"
#include <QMatrix3x3>

Entity::Entity()
{
    this->model = NULL;
    mat.setToIdentity();
}

Entity::Entity(Model* model)
{
    this->model = model;
    mat.setToIdentity();
}

Entity::Entity(Model* model,QMatrix4x4 mat)
{
    this->model = model;
    this->mat = mat;
}

QMatrix4x4 Entity::getMatrix() const
{
    return mat;
}

void Entity::setMatrix(const QMatrix4x4 &value)
{
    mat = value;
}

Model* Entity::getModel()
{
    return model;
}

void Entity::draw(QOpenGLShaderProgram& shader)
{
    QMatrix3x3 normalMatrix = mat.normalMatrix();
    shader.setUniformValue("model",mat);
    shader.setUniformValue("normalMatrix",normalMatrix);
    model->draw(shader);
}
