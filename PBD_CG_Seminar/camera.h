#ifndef CAMERA_H
#define CAMERA_H
#include<QMatrix4x4>
#include<QVector3D>

class Camera
{
public:
    Camera();
    QMatrix4x4 lookAt();

    void strafeX(float x);
    void strafeY(float y);
    void strafeZ(float z);

    void roll(float angle);
    void pitch(float angle);
    void yaw(float angle);

    void reset();

    QVector3D getPosition();
    QVector3D getViewingNormal();
private:
    QVector3D s;
    QVector3D u;
    QVector3D v;


    QVector3D pos;
};

#endif // CAMERA_H
