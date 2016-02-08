#ifndef SOLVER_H
#define SOLVER_H
#include<QVector>
#include<QVector3D>
#include<QList>
#include"framework/abstractsolver.h"
#include"graphics/entity.h"
#include"framework/constraintparameters.h"
#include"collisionsphereconstraint.h"

class Solver : public AbstractSolver
{
public:
    Solver();

    void solve(QList<Entity>* colObjs=0);
private:
    QVector<ConstraintParameters> constraints;
    QVector<CollisionSphereConstraint> sphereConstraints;
};

#endif // SOLVER_H
