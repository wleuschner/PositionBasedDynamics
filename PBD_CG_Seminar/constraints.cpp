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

void solveTetrahedralConstraint(QVector<Vertex>& vertices,QVector<Face>& facelist,const QMap<int,QList<Face*>*> facemap,float volume,float pressure,QVector<QVector3D>& dp)
{
    for(int v=0;v<vertices.size();v++)
    {
        QList<Face*>* faces = facemap.value(v);
        dp[v] = QVector3D(0,0,0);
        //qDebug()<<faces->size();
        for(QList<Face*>::iterator f = faces->begin();f!=faces->end();f++)
        {
            if(v == (*f)->v1)
            {
                QVector3D fv1 = vertices[(*f)->v2].getPos();
                QVector3D fv2 = vertices[(*f)->v3].getPos();
                //qDebug()<<"Cross1:"<<QVector3D::crossProduct(fv1,fv2);
                dp[v] += QVector3D::crossProduct(fv1,fv2);
            }
            else if(v == (*f)->v2)
            {
                QVector3D fv1 = vertices[(*f)->v3].getPos();
                QVector3D fv2 = vertices[(*f)->v1].getPos();
                //qDebug()<<"Cross2:"<<QVector3D::crossProduct(fv1,fv2);
                dp[v] += QVector3D::crossProduct(fv1,fv2);
            }
            else if(v == (*f)->v3)
            {
                QVector3D fv1 = vertices[(*f)->v1].getPos();
                QVector3D fv2 = vertices[(*f)->v2].getPos();
                //qDebug()<<"Cross3:"<<QVector3D::crossProduct(fv1,fv2);
                dp[v] += QVector3D::crossProduct(fv1,fv2);
            }
        }
    }

    float sum = 0;
    for(int i=0;i<dp.size();i++)
    {
        sum += dp[i].lengthSquared();
    }

    float newVolume = 0.0;
    for(int f=0;f<facelist.size();f++)
    {
        Face face = facelist[f];
        QVector3D v1 = vertices[face.v1].getPos();
        QVector3D v2 = vertices[face.v2].getPos();
        QVector3D v3 = vertices[face.v3].getPos();
        newVolume += QVector3D::dotProduct(v3,QVector3D::crossProduct(v1,v2));
    }
    newVolume = newVolume-pressure*volume;
    float s = -(newVolume/sum);
    //qDebug()<<newVolume;

    for(int i=0;i<dp.size();i++)
    {
        dp[i] = s*dp[i];
        //qDebug()<<dp[i];
    }
}
