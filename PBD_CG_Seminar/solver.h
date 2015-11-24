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
    int solverLoops;

    void solveDistanceConstraint(const QVector3D& p1,const QVector3D& p2,float l0,float compression_k,float stretch_k,QVector3D& dp1,QVector3D& dp2);
    void solveBendConstraint(const QVector3D& p1,const QVector3D& p2,float phi,QVector3D& dp1,QVector3D& dp2);
    void solveEnviromentConstraint(const QVector3D& p1,const QVector3D& n,float d,QVector3D& dp1);
    QVector<ConstraintParameters> constraints;

    QList<Model*> modelList;
};

#endif // SOLVER_H
