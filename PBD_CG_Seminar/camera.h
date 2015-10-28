#ifndef CAMERA_H
#define CAMERA_H
#include<QMatrix4x4>
#include<QVector3D>

class Camera
{
public:
    Camera();
    QMatrix4x4 lookAt();
private:
    QVector3D pos;
    QVector3D at;
    QVector3D up;
};

#endif // CAMERA_H