#ifndef LIGHT_H
#define LIGHT_H
#include<glm/glm.hpp>

class Light
{
public:
    Light();
    Light(glm::vec3& pos);
    Light(glm::vec3& pos,glm::vec3& ambient,glm::vec3& diffuse,glm::vec3& specular);

    void setPosition(glm::vec3& pos);
    void setAmbient(glm::vec3& ambient);
    void setDiffuse(glm::vec3& diffuse);
    void setSpecular(glm::vec3& specular);

    glm::vec3 getPosition();
    glm::vec3 getAmbient();
    glm::vec3 getDiffuse();
    glm::vec3 getSpecular();

private:
    glm::vec3 pos;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

#endif // LIGHT_H
