#ifndef VERTEX_H
#define VERTEX_H
#include<QVector3D>

class Vertex
{
public:
    Vertex();
private:
    //General Attributes
    QVector3D pos;
    QVector3D normal;
    QVector3D color;

    //PBD Attributes
    float mass;
    QVector3D velocity;

    //Lighting Attributes
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
    float shininess;
};

#endif // VERTEX_H
