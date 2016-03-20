#include "light.h"
#include <GL/glew.h>

QList<Light*> Light::lights;

Light::Light()
{
    this->pos=QVector3D(0.0,0.0,0.0);
    this->ambient=QVector3D(0.2,0.2,0.2);
    this->diffuse=QVector3D(0.5,0.5,0.5);
    this->specular=QVector3D(0.8,0.8,0.8);
}

Light::Light(QVector3D &pos)
{
    this->pos=QVector3D(pos);
    this->ambient=QVector3D(0.2,0.2,0.2);
    this->diffuse=QVector3D(0.5,0.5,0.5);
    this->specular=QVector3D(0.8,0.8,0.8);
}

Light::Light(QVector3D &pos, QVector3D &ambient, QVector3D &diffuse, QVector3D &specular)
{
    this->pos=QVector3D(pos);
    this->ambient=QVector3D(ambient);
    this->diffuse=QVector3D(diffuse);
    this->specular=QVector3D(specular);
}

void Light::setPosition(QVector3D& pos)
{
    this->pos=QVector3D(pos);
}

void Light::setAmbient(QVector3D& ambient)
{
    this->ambient=QVector3D(ambient);
}

void Light::setDiffuse(QVector3D& diffuse)
{
    this->diffuse=QVector3D(diffuse);
}

void Light::setSpecular(QVector3D& specular)
{
    this->specular=QVector3D(specular);
}

const QVector3D& Light::getPosition()
{
    return pos;
}

const QVector3D& Light::getAmbient()
{
    return ambient;
}

const QVector3D& Light::getDiffuse()
{
    return diffuse;
}

const QVector3D& Light::getSpecular()
{
    return specular;
}

void Light::beginShadowmap()
{
}

void Light::endShadowmap()
{
}

void Light::addLight(Light* light)
{
    lights.append(light);
}

void Light::removeLight(Light* light)
{
    lights.removeOne(light);
}

void Light::getLight(int index)
{
    lights.removeAt(index);
}

void Light::clearLights()
{
    for(QList<Light*>::iterator i = lights.begin();i!=lights.end();i++)
    {
        delete *i;
        lights.erase(i);
    }
}

QList<Light*>& Light::getLights()
{
    return lights;
}
