#ifndef CONSTRAINTPARAMETERS_H
#define CONSTRAINTPARAMETERS_H
#include <QVector3D>

struct ConstraintParameters
{
    ConstraintParameters();
    ConstraintParameters(QVector3D* point,QVector3D normal,float distance);

    QVector3D* point;
    QVector3D normal;
    float distance;
};

#endif // CONSTRAINTPARAMETERS_H
