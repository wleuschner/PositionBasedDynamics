#include "camera.h"

Camera::Camera()
{
    pos=QVector3D(0.0,0.0,0.0);
    up=QVector3D(0.0,1.0,0.0);
    at=QVector3D(0.0,0.0,-1.0);
}

QMatrix4x4 Camera::lookAt()
{
    QMatrix4x4 ret;
    ret.lookAt(pos,at,up);
    return ret;
}

void Camera::move(const QVector3D& a)
{
    pos+=a;
    at+=a;
}

void Camera::reset()
{
    pos=QVector3D(0.0,0.0,0.0);
    at=QVector3D(0.0,0.0,-1.0);
}
