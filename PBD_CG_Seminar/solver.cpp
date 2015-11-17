#include "solver.h"
#include <math.h>

Solver::Solver()
{
    solverLoops = 50;
    stiffness = 1.0;
}

void Solver::solve()
{
    double t = 1.0/60.0;
    for(QList<Model*>::iterator m=modelList.begin();m!=modelList.end();m++)
    {
        QVector<unsigned int> indices = (*m)->getIndices();
        QVector<Vertex>& vertices = (*m)->getVertices();
        QVector<Vertex> positions = vertices;
        for(QVector<unsigned int>::iterator i=indices.begin();i!=indices.end();i++)
        {
            double g = 9.81;
            double w = 1.0/positions[*i].getMass();
            QVector3D v = positions[*i].getVelocity();
            v = v+t*w*QVector3D(0.0,0.0,0.0);
            positions[*i].setVelocity(v);
        }

        for(QVector<unsigned int>::iterator i=indices.begin();i!=indices.end();i++)
        {
            QVector3D v = positions[*i].getVelocity();
            positions[*i].setVelocity(0.95*v);
        }

        for(QVector<unsigned int>::iterator i=indices.begin();i!=indices.end();i++)
        {
            QVector3D x = positions[*i].getPos();
            QVector3D v = positions[*i].getVelocity();
            QVector3D p = x+t*v;
            positions[*i].setPos(p);
        }
        //Project Contraints
        //Solver Loops
        for(int i=0;i<solverLoops;i++)
        {
            for(QVector<unsigned int>::iterator j=indices.begin();std::distance(j,indices.end())>3;j++)
            {
                QVector3D p1 = positions[*j].getPos();
                QVector3D p2 = positions[*j+1].getPos();
                QVector3D p1p2 = (p1-p2);


                QVector3D grad1 = -p1p2.normalized();
                QVector3D grad2 = p1p2.normalized();
                float p1p2_len = p1p2.length();
                QVector3D dp1(0,0,0);

                float s1 = (p1p2_len-20);
                if(fabs(s1)>0.0625)
                {
                    dp1 = -0.5*(p1p2_len-20)*grad2;
                }
                p1+=dp1;

                QVector3D dp2(0,0,0);
                float s2 = (p1p2_len-20);
                if(fabs(s2)>0.0625)
                {
                    dp1 = 0.5*(p1p2_len-20)*grad2;
                }
                p2+=dp2;
                //qDebug()<<i<<":("<<p1<<";"<<p2<<")";

                positions[*j].setPos(p1);
                positions[*j+1].setPos(p2);
            }
        }
        for(int i=0;i<positions.length();i++)
        {
            QVector3D x = vertices[i].getPos();
            QVector3D p = positions[i].getPos();
            vertices[i].setVelocity(((p-x)/t)*0.5);
            vertices[i].setPos(p);
        }
        (*m)->update();
    }
}

QVector3D Solver::distanceConstraintDerivative(const QVector3D& a,const QVector3D& b)
{
    QVector3D result = (1/((a-b).length()))*(a-b);
    return result;
}

void Solver::addModel(Model* model)
{
    modelList.append(model);
}

void Solver::reset()
{
    modelList.clear();
}
