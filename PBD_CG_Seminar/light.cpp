#include "light.h"

Light::Light()
{
    this->pos=glm::vec3(0.0,0.0,0.0);
    this->ambient=glm::vec3(0.2,0.2,0.2);
    this->diffuse=glm::vec3(0.5,0.5,0.5);
    this->specular=glm::vec3(0.8,0.8,0.8);
}

Light::Light(glm::vec3 &pos)
{
    this->pos=glm::vec3(pos);
    this->ambient=glm::vec3(0.2,0.2,0.2);
    this->diffuse=glm::vec3(0.5,0.5,0.5);
    this->specular=glm::vec3(0.8,0.8,0.8);
}

Light::Light(glm::vec3 &pos, glm::vec3 &ambient, glm::vec3 &diffuse, glm::vec3 &specular)
{
    this->pos=glm::vec3(pos);
    this->ambient=glm::vec3(ambient);
    this->diffuse=glm::vec3(diffuse);
    this->specular=glm::vec3(specular);
}

void Light::setPosition(glm::vec3& pos)
{
    this->pos=glm::vec3(pos);
}

void Light::setAmbient(glm::vec3& ambient)
{
    this->ambient=glm::vec3(ambient);
}

void Light::setDiffuse(glm::vec3& diffuse)
{
    this->diffuse=glm::vec3(diffuse);
}

void Light::setSpecular(glm::vec3& specular)
{
    this->specular=glm::vec3(specular);
}

glm::vec3 Light::getPosition()
{
    return pos;
}

glm::vec3 Light::getAmbient()
{
    return ambient;
}

glm::vec3 Light::getDiffuse()
{
    return diffuse;
}

glm::vec3 Light::getSpecular()
{
    return specular;
}
