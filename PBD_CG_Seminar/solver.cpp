#include "solver.h"
#include <math.h>
#define NUMERIC_DELTA 0.015625

Solver::Solver()
{
    solverLoops = 5;
}

void Solver::solve()
{
    double t = 1.0/60.0;
    for(QList<Model*>::iterator m=modelList.begin();m!=modelList.end();m++)
    {
        QVector<unsigned int> indices = (*m)->getIndices();
        QVector<Vertex>& vertices = (*m)->getVertices();
        QVector<Vertex> positions = vertices;
        for(QVector<Vertex>::iterator i=positions.begin();i!=positions.end();i++)
        {
            double g = 9.81;
            double w = 1.0/i->getMass();
            QVector3D v = i->getVelocity();
            v = v+t*w*QVector3D(0.0,-g,0.0);
            i->setVelocity(v);
        }

        for(QVector<Vertex>::iterator i=positions.begin();i!=positions.end();i++)
        {
            QVector3D x = i->getPos();
            QVector3D v = i->getVelocity();
            QVector3D p = x+t*v;
            i->setPos(p);
        }

        //Generate Enviroment Collision Constraints
        for(QVector<Vertex>::iterator i=positions.begin();i!=positions.end();i++)
        {
            QVector3D* pos = i->getPosReference();
            float dist = QVector3D::dotProduct(*pos,QVector3D(0.0,1.0,0.0))-10.0;
            if(dist<0.0)
            {
                constraints.push_back(ConstraintParameters(pos,QVector3D(0.0,1.0,0.0),-10.0));
            }
        }
        //Project Contraints
        //Solver Loops
        for(int i=0;i<solverLoops;i++)
        {
            for(QVector<unsigned int>::iterator j=indices.begin();std::distance(j,indices.end())>1;j++)
            {
                QVector3D p1 = positions[*j].getPos();
                QVector3D p2 = positions[*(j+1)].getPos();
                QVector3D x1 = vertices[*j].getPos();
                QVector3D x2 = vertices[*(j+1)].getPos();
                QVector3D dp1(0,0,0),dp2(0,0,0);

                solveDistanceConstraint(p1,p2,(x1-x2).length(),0.5,0.5,dp1,dp2);
                p1 += dp1;
                p2 += dp2;

                positions[*j].setPos(p1);
                positions[*(j+1)].setPos(p2);
            }
            for(QVector<ConstraintParameters>::iterator i=constraints.begin();i!=constraints.end();i++)
            {
                QVector3D dp1(0,0,0);
                QVector3D point = *(i->point);
                solveEnviromentConstraint(point,i->normal,i->distance,dp1);
                *(i->point)+=dp1;
            }
        }
        for(int i=0;i<positions.length();i++)
        {
            QVector3D x = vertices[i].getPos();
            QVector3D p = positions[i].getPos();
            vertices[i].setVelocity(((p-x)/t)*0.95);
            vertices[i].setPos(p);
        }
        constraints.clear();
        (*m)->update();
    }
}

void Solver::solveDistanceConstraint(const QVector3D& p1,const QVector3D& p2,float l0,float compression_k,float stretch_k,QVector3D& dp1,QVector3D& dp2)
{
    //QVector3D result = (1/((a-b).length()))*(a-b);
    QVector3D p1p2 = (p1-p2);
    QVector3D normal = p1p2.normalized();
    float p1p2_len = p1p2.length();

    QVector3D dp = QVector3D(0,0,0);

    if(p1p2_len>l0)
    {
        dp = (1-pow((1-stretch_k),1.0/solverLoops))*(p1p2_len-l0)*normal;
    }
    else
    {
        dp = (1-pow((1-compression_k),1.0/solverLoops))*(p1p2_len-l0)*normal;
    }
    dp1=-dp;
    dp2=dp;
}

void Solver::solveBendConstraint(const QVector3D& p1,const QVector3D& p2,float phi,QVector3D& dp1,QVector3D& dp2)
{

}


void Solver::solveEnviromentConstraint(const QVector3D& p1,const QVector3D& n,float d,QVector3D& dp1)
{
    float dist = QVector3D::dotProduct(p1,n)-d;
    if(dist<0.0)
    {
        dp1 += (fabs(dist)+NUMERIC_DELTA)*n;
    }
}

void Solver::addModel(Model* model)
{
    modelList.append(model);
}

void Solver::reset()
{
    modelList.clear();
}
