#include"constraints.h"
#include<QVector3D>
#define NUMERIC_DELTA 0.015625


void solveDistanceConstraint(const QVector3D& p1,const QVector3D& p2,float l0,float compression_k,float stretch_k,QVector3D& dp1,QVector3D& dp2)
{
    //QVector3D result = (1/((a-b).length()))*(a-b);
    QVector3D p1p2 = (p1-p2);
    QVector3D normal = p1p2.normalized();
    float p1p2_len = p1p2.length();

    QVector3D dp = QVector3D(0,0,0);

    if(p1p2_len>l0)
    {
        dp = stretch_k*(p1p2_len-l0)*normal;
    }
    else
    {
        dp = compression_k*(p1p2_len-l0)*normal;
    }
    dp1=-dp;
    dp2=dp;
}

void solveBendConstraint(const QVector3D& p1,const QVector3D& p2,const QVector3D& p3,const QVector3D&p4,float phi,QVector3D& dp1,QVector3D& dp2,QVector3D& dp3,QVector3D& dp4)
{
    QVector3D n1 = QVector3D::crossProduct(p2-p1,p3-p1).normalized();
    QVector3D n2 = QVector3D::crossProduct(p2-p1,p4-p1).normalized();
    float d = QVector3D::dotProduct(n1,n2);

    QVector3D q2 = -(QVector3D::crossProduct(p3,n2)+(QVector3D::crossProduct(n1,p3))*d)/QVector3D::crossProduct(p2,p3).length()-
                    (QVector3D::crossProduct(p4,n1)+(QVector3D::crossProduct(n2,p4))*d)/QVector3D::crossProduct(p2,p4).length();
    QVector3D q3 = (QVector3D::crossProduct(p2,n2)+(QVector3D::crossProduct(n1,p2))*d)/QVector3D::crossProduct(p2,p3).length();
    QVector3D q4 = (QVector3D::crossProduct(p2,n1)+(QVector3D::crossProduct(n2,p2))*d)/QVector3D::crossProduct(p2,p4).length();
    QVector3D q1 = q2-q3-q4;


    float s = sqrt(1-d*d)*(acos(d)-phi)/(q1.length()+q2.length()+q3.length()+q4.length());
    dp1 = s*q1;
    dp2 = s*q2;
    dp3 = s*q3;
    dp4 = s*q4;
}

void solveEnviromentConstraint(const QVector3D& p1,const QVector3D& n,float d,QVector3D& dp1)
{
    float dist = QVector3D::dotProduct(p1,n)-d;
    if(dist<0.0)
    {
        dp1 += (fabs(dist)+NUMERIC_DELTA)*n;
    }
}
