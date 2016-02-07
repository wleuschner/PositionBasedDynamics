#ifndef COLLISIONSPHERECONSTRAINT_H
#define COLLISIONSPHERECONSTRAINT_H
#include <QVector3D>

class CollisionSphereConstraint
{
public:
    CollisionSphereConstraint();

    int index;
    QVector3D pos;
    float radius;
};

#endif // COLLISIONSPHERECONSTRAINT_H
