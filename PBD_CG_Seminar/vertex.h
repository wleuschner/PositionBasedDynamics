#ifndef VERTEX_H
#define VERTEX_H
#include<QVector3D>
#include<QVector2D>

class Vertex
{
public:
    Vertex();

    QVector3D getPos() const;
    void setPos(const QVector3D &value);

    QVector3D getNormal() const;
    void setNormal(const QVector3D &value);

    QVector3D getAmbient() const;
    void setAmbient(const QVector3D &value);

    QVector3D getDiffuse() const;
    void setDiffuse(const QVector3D &value);

    QVector3D getSpecular() const;
    void setSpecular(const QVector3D &value);

    float getShininess() const;
    void setShininess(float value);

    float getMass() const;
    void setMass(float value);

    QVector3D getVelocity() const;
    void setVelocity(const QVector3D &value);

    QVector2D getUv() const;
    void setUv(const QVector2D &value);

private:
    //General Attributes
    QVector3D pos;
    QVector3D normal;
    QVector2D uv;

    //Material Attributes
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
    float shininess;

    //PBD Attributes
    float mass;
    QVector3D velocity;
};

#endif // VERTEX_H
