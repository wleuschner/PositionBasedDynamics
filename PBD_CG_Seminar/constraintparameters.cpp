#include "constraintparameters.h"

ConstraintParameters::ConstraintParameters()
{
}

ConstraintParameters::ConstraintParameters(QVector3D* point,QVector3D normal,float distance) : point(point)
{
    this->point=point;
    this->normal=normal;
    this->distance=distance;
}

