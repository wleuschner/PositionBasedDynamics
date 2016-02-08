#include "material.h"

Material::Material(const QVector3D& ambient,const QVector3D& diffuse,const QVector3D& specular,float shininess)
{
    this->ambient=ambient;
    this->diffuse=diffuse;
    this->specular=specular;
    this->shininess=shininess;
}

Material::Material()
{
    this->ambient=QVector3D(0.2,0.2,0.2);
    this->diffuse=QVector3D(0.4,0.4,0.4);
    this->specular=QVector3D(0.8,0.8,0.8);
    this->shininess=16.0;
}

QVector3D Material::getSpecular() const
{
    return specular;
}

void Material::setSpecular(const QVector3D &value)
{
    specular = value;
}

QVector3D Material::getDiffuse() const
{
    return diffuse;
}

void Material::setDiffuse(const QVector3D &value)
{
    diffuse = value;
}

QVector3D Material::getAmbient() const
{
    return ambient;
}

void Material::setAmbient(const QVector3D &value)
{
    ambient = value;
}

float Material::getShininess() const
{
    return shininess;
}

void Material::setShininess(float value)
{
    shininess = value;
}


