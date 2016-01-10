#include "solver.h"
#include <math.h>
#include "constraints.h"

Solver::Solver()
{
    solverLoops = 10;
}

void Solver::solve()
{
    double t = 1.0/60.0;

    //Soft Body Physics
    for(QList<Entity>::iterator e=softList.begin();e!=softList.end();e++)
    {
        Model* m = e->getModel();
        QMatrix4x4 mat = e->getMatrix();
        QVector<unsigned int> indices = m->getIndices();
        QVector<Vertex>& vertices = m->getVertices();
        QVector<Vertex> positions = vertices;

        //External forces
        for(QVector<Vertex>::iterator i=positions.begin();i!=positions.end();i++)
        {
            double g = 9.81;
            double w = 1.0/i->getMass();
            QVector3D v = i->getVelocity();
            v = v+t*w*QVector3D(0.0,-g,0.0);
            i->setVelocity(v);
        }

        //Calculate estimates
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
            //TODO Collision with other Objects

            //TODO Selfcolision

            //Collision with floor
            float dist = QVector3D::dotProduct(*pos,QVector3D(0.0,1.0,0.0))-40;
            if(dist<0.0)
            {
                constraints.push_back(ConstraintParameters(pos,QVector3D(0.0,1.0,0.0),-40.0));
            }
        }
        //Project Contraints
        //Solver Loops
        for(int i=0;i<solverLoops;i++)
        {
            //Solve General Constraints
            float k_stretch = 1 - pow(1-0.5,1.0/solverLoops);
            for(QVector<unsigned int>::iterator j=indices.begin();std::distance(j,indices.end())>1;j++)
            {
                QVector3D p1 = positions[*j].getPos();
                QVector3D p2 = positions[*(j+1)].getPos();
                QVector3D x1 = vertices[*j].getPos();
                QVector3D x2 = vertices[*(j+1)].getPos();
                QVector3D dp1(0,0,0),dp2(0,0,0);


                solveDistanceConstraint(p1,p2,(x1-x2).length(),k_stretch,k_stretch,dp1,dp2);
                p1 += dp1;
                p2 += dp2;

                positions[*j].setPos(p1);
                positions[*(j+1)].setPos(p2);
            }
            //Solve Collision Constraints
            for(QVector<ConstraintParameters>::iterator i=constraints.begin();i!=constraints.end();i++)
            {
                QVector3D dp1(0,0,0);
                QVector3D point = *(i->point);
                solveEnviromentConstraint(point,i->normal,i->distance,dp1);
                *(i->point)+=dp1;
            }
        }
        //Set new Positions
        for(int i=0;i<positions.length();i++)
        {
            QVector3D x = vertices[i].getPos();
            QVector3D p = positions[i].getPos();
            vertices[i].setVelocity(((p-x)/t)*0.95);
            vertices[i].setPos(p);
        }
        //Recalculate normals
        constraints.clear();
        m->recalNormals();
        m->update();
    }
}

void Solver::addModel(Entity model)
{
    softList.append(model);
}

void Solver::reset()
{
    softList.clear();
}
