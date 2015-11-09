#include "solver.h"

Solver::Solver()
{
    solverLoops = 20;
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
            positions[*i].setVelocity(0.99*v);
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
            for(QVector<unsigned int>::iterator j=indices.begin();*j<411;j++)
            {
                QVector3D p1 = positions[*j].getPos();
                QVector3D p2 = positions[*j+1].getPos();

                //Stretching Constraint
                double edge_length = (p1-p2).length();
                double s1 = (edge_length-100.0);
                QVector3D dp1(0,0,0);
                QVector3D dp2(0,0,0);
                if(s1>0.0625)
                {
                    dp1 = -0.5*s1*(1/(edge_length)*(p1-p2));
                    dp2 = 0.5*s1*(1/(edge_length)*(p1-p2));
                    p1 = p1+dp1;
                    p2 = p2+dp2;
                }
                positions[*j].setPos(p1);
                positions[*j+1].setPos(p2);
            }
        }
        for(int i=0;i<positions.length();i++)
        {
            QVector3D x = vertices[i].getPos();
            QVector3D p = positions[i].getPos();
            vertices[i].setVelocity((1/t)*(p-x));
            //vertices[i].setPos(p);
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
