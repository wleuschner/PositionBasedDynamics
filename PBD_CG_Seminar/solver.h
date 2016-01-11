#ifndef SOLVER_H
#define SOLVER_H
#include<QVector>
#include<QVector3D>
#include<QList>
#include"abstractsolver.h"
#include"entity.h"
#include"constraintparameters.h"

class Solver : public AbstractSolver
{
public:
    Solver();

    void solve();
    void addSoftBody(Entity model);
    void addBallonBody(Entity model);
    void addRigidBody(Entity model);
    void reset();
private:
    QVector<ConstraintParameters> constraints;
};

#endif // SOLVER_H
