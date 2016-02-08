#include "constraintparameters.h"

ConstraintParameters::ConstraintParameters()
{
}

ConstraintParameters::ConstraintParameters(int index,QVector3D normal,float distance)
{
    this->index=index;
    this->normal=normal;
    this->distance=distance;
}

