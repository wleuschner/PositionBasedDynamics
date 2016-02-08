#include "vertex.h"

Vertex::Vertex()
{
}

QVector3D* Vertex::getPosReference()
{
    return &pos;
}

QVector3D Vertex::getPos() const
{
    return pos;
}

void Vertex::setPos(const QVector3D &value)
{
    pos = value;
}
QVector3D Vertex::getNormal() const
{
    return normal;
}

void Vertex::setNormal(const QVector3D &value)
{
    normal = value;
}
float Vertex::getMass() const
{
    return mass;
}

void Vertex::setMass(float value)
{
    mass = value;
}

QVector3D Vertex::getVelocity() const
{
    return velocity;
}

void Vertex::setVelocity(const QVector3D& value)
{
    velocity = value;
}
QVector2D Vertex::getUv() const
{
    return uv;
}

void Vertex::setUv(const QVector2D &value)
{
    uv = value;
}









