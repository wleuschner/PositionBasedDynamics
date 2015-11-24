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
QVector3D Vertex::getAmbient() const
{
    return ambient;
}

void Vertex::setAmbient(const QVector3D &value)
{
    ambient = value;
}
QVector3D Vertex::getDiffuse() const
{
    return diffuse;
}

void Vertex::setDiffuse(const QVector3D &value)
{
    diffuse = value;
}
QVector3D Vertex::getSpecular() const
{
    return specular;
}

void Vertex::setSpecular(const QVector3D &value)
{
    specular = value;
}
float Vertex::getShininess() const
{
    return shininess;
}

void Vertex::setShininess(float value)
{
    shininess = value;
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









