#ifndef LIGHT_H
#define LIGHT_H
#include<QVector3D>

class Light
{
public:
    Light();
    Light(QVector3D& pos);
    Light(QVector3D& pos,QVector3D& ambient,QVector3D& diffuse,QVector3D& specular);

    void setPosition(QVector3D& pos);
    void setAmbient(QVector3D& ambient);
    void setDiffuse(QVector3D& diffuse);
    void setSpecular(QVector3D& specular);

    const QVector3D& getPosition();
    const QVector3D& getAmbient();
    const QVector3D& getDiffuse();
    const QVector3D& getSpecular();

    void beginShadowmap();
    void endShadowmap();

private:
    QVector3D pos;
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;

    unsigned int framebuffer;
    unsigned int shadowmap;
};

#endif // LIGHT_H
