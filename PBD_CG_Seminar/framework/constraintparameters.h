#ifndef CONSTRAINTPARAMETERS_H
#define CONSTRAINTPARAMETERS_H
#include <QVector3D>

struct ConstraintParameters
{
    ConstraintParameters();
    ConstraintParameters(int index,QVector3D normal,float distance);

    int index;
    QVector3D normal;
    float distance;
};

#endif // CONSTRAINTPARAMETERS_H
