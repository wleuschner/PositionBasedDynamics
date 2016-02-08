#include "entity.h"
#include <QMatrix3x3>

Entity::Entity()
{
    velocity = QVector3D(0,0,0);
    this->model = NULL;
    mat.setToIdentity();
}

Entity::~Entity()
{
}

Entity::Entity(Model* model)
{
    velocity = QVector3D(0,0,0);
    this->model = model;
    mat.setToIdentity();
}

Entity::Entity(Model* model,QMatrix4x4 mat)
{
    velocity = QVector3D(0,0,0);
    this->model = model;
    this->mat = mat;
}

Entity::Entity(Model* model,QMatrix4x4 mat,QVector3D position,QVector3D velocity)
{
    mat.translate(position);
    this->model = model;
    this->mat = mat;
    this->position = position;
    this->velocity = velocity;
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

void Entity::release()
{
    if(model!=NULL)
    {
        model->release();
    }
}

void Entity::update()
{
    position += velocity;
    mat.translate(velocity);
}

void Entity::draw(QOpenGLShaderProgram* shader,QMatrix4x4& view)
{
    QMatrix4x4 modelView = view*mat;
    QMatrix3x3 normalMatrix = modelView.normalMatrix();
    shader->setUniformValue("model",mat);
    shader->setUniformValue("modelView",modelView);
    shader->setUniformValue("normalMatrix",normalMatrix);
    model->draw(shader);
}

QVector3D Entity::getPosition()
{
    return position;
}

QVector3D Entity::getVelocity()
{
    return position;
}
