#ifndef FACE_H
#define FACE_H
#include<QVector3D>

class Face
{
public:
    Face();
    Face(int v1,int v2,int v3);

    int v1;
    int v2;
    int v3;

    QVector3D normal;
};

#endif // FACE_H
