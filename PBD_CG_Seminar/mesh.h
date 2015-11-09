#ifndef MESH_H
#define MESH_H
#include<QOpenGLBuffer>
#include<QVector>
#include<QVector2D>
#include<QVector3D>
#include<QMatrix4x4>
#include"vertex.h"

class Mesh
{
public:
    Mesh();
private:
    QOpenGLBuffer vbo;

    QVector<QVector3D> position;
    QVector<QVector3D> normal;
    QVector<QVector2D> uv_coords;

    QMatrix4x4 mat;
    QVector<Vertex> vertices;
};

#endif // MESH_H
