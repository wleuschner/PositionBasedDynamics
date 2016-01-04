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

    void solveDistanceConstraint(const QVector3D& p1,const QVector3D& p2,float l0,float compression_k,float stretch_k,QVector3D& dp1,QVector3D& dp2);
    void solveBendConstraint(const QVector3D& p1,const QVector3D& p2,float phi,QVector3D& dp1,QVector3D& dp2);
    void solveTetrahedralConstraint(const QVector3D& p1,const QVector3D& p2,const QVector3D& p3,const QVector3D& p4,float v0);
    void solveEnviromentConstraint(const QVector3D& p1,const QVector3D& n,float d,QVector3D& dp1);
    QVector<ConstraintParameters> constraints;

    QList<Entity> softList;
    QList<Entity> rigidList;
};

#endif // SOLVER_H
