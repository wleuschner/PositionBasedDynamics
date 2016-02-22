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

    glGenBuffers(1,&framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glGenTextures(1,&shadowmap);
    glBindTexture(GL_TEXTURE_2D,shadowmap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16,1024,1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowmap, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, NULL);
    glBindTexture(GL_TEXTURE_2D,0);
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
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glBindTexture(GL_TEXTURE_2D,shadowmap);
    glDrawBuffer(GL_NONE);
}

void Light::endShadowmap()
{
    glDrawBuffer(GL_FRONT_AND_BACK);
    glBindTexture(GL_TEXTURE_2D,0);
    glBindFramebuffer(GL_FRAMEBUFFER, NULL);
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
