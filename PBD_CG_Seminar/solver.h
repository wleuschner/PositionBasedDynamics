#ifndef SOLVER_H
#define SOLVER_H
#include<QVector>
#include<QVector3D>
#include<QList>
#include"entity.h"
#include"constraintparameters.h"

class Solver
{
public:
    Solver();

    void solve();
    void addModel(Entity model);
    void reset();
private:
    int solverLoops;

    QVector<ConstraintParameters> constraints;

    QList<Entity> softList;
    QList<Entity> rigidList;
};

#endif // SOLVER_H
