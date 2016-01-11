#ifndef ABSTRACTSOLVER_H
#define ABSTRACTSOLVER_H
#include"entity.h"

class AbstractSolver
{
public:
    AbstractSolver();
    void addRigidBody(Entity model);
    void addBallonBody(Entity model);
    void addSoftBody(Entity model);

    virtual void solve()=0;

    void reset();
protected:
    int solverLoops;

    QList<Entity> rigidList;
    QList<Entity> ballonList;
    QList<Entity> softList;
};

#endif // ABSTRACTSOLVER_H
