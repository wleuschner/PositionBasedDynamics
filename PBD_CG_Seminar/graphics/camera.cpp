#include "camera.h"

Camera::Camera()
{
    reset();
}

QMatrix4x4 Camera::lookAt()
{
    QMatrix4x4 ret(s.x(),s.y(),s.z(),QVector3D::dotProduct(s,-pos),
                   u.x(),u.y(),u.z(),QVector3D::dotProduct(u,-pos),
                   v.x(),v.y(),v.z(),QVector3D::dotProduct(v,-pos),
                   0,0,0,1);
    return ret;
}

void Camera::strafeX(float x)
{
    QVector3D n = QVector3D::crossProduct(QVector3D(0.0,1.0,0.0),v);
    pos+=x*n;
}

void Camera::strafeY(float y)
{
    pos+=y*QVector3D(0.0,1.0,0.0);
}

void Camera::strafeZ(float z)
{

    pos+=z*v;
}

void Camera::yaw(float angle)
{
    QMatrix4x4 rot;
    rot.rotate(angle,u);
    s = rot*s;
    v = rot*v;
}


void Camera::roll(float angle)
{
    QMatrix4x4 rot;
    rot.rotate(angle,s);
    u = rot*u;
    v = rot*v;
}

void Camera::reset()
{
    s = QVector3D(1.0,0.0,0.0);
    u = QVector3D(0.0,1.0,0.0);
    v = QVector3D(0.0,0.0,1.0);
}

QVector3D Camera::getPosition()
{
    return pos;
}

QVector3D Camera::getViewingNormal()
{
    return v;
}
