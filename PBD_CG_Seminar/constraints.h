#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H
#include<QVector3D>

extern void solveDistanceConstraint(const QVector3D& p1,const QVector3D& p2,float l0,float compression_k,float stretch_k,QVector3D& dp1,QVector3D& dp2);
extern void solveBendConstraint(const QVector3D& p1,const QVector3D& p2,const QVector3D& p3,const QVector3D&p4,float phi,QVector3D& dp1,QVector3D& dp2,QVector3D& dp3,QVector3D& dp4);
extern void solveEnviromentConstraint(const QVector3D& p1,const QVector3D& n,float d,QVector3D& dp1);

#endif // CONSTRAINTS_H
