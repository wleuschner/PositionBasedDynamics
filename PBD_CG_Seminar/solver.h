#ifndef SOLVER_H
#define SOLVER_H
#include<QVector>
#include<QVector3D>
#include<QList>
#include"model.h"
#include"constraintparameters.h"

class Solver
{
public:
    Solver();

    void solve();
    void addModel(Model* model);
    void reset();
private:
    float stiffness;
    float bendness;
    int solverLoops;

    QVector3D distanceConstraintDerivative(const QVector3D& a,const QVector3D& b);
    QVector<ConstraintParameters> constraints;

    QList<Model*> modelList;
};

#endif // SOLVER_H
