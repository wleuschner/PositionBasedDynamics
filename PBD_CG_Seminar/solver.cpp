#include "solver.h"
#include <math.h>
#include "constraints.h"

Solver::Solver()
{
}

void Solver::solve()
{
    double t = 1/60.0;

    //Rigid Body Physics
    for(QList<Entity>::iterator e=rigidList.begin();e!=rigidList.end();e++)
    {

    }

    //Cloth Ballon Physics
    for(QList<Entity>::iterator e=ballonList.begin();e!=ballonList.end();e++)
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
        for(int i=0;i<positions.size();i++)
        {
            Vertex v = positions[i];
            QVector3D pos = v.getPos();

            //Collision with floor
            float dist = QVector3D::dotProduct(pos,QVector3D(0.0,1.0,0.0))+5;
            if(dist<0.0)
            {
                constraints.push_back(ConstraintParameters(i,QVector3D(0.0,1.0,0.0),-5.0));
            }
        }
        QVector<Face>& faces = m->getFaces();
        const QMap<int,QList<Face*>*> facemap = m->getFacemap();
        float volume = m->getVolume();
        for(int i=0;i<20;i++)
        {
            //Solve Distance Constraint
            float k_stretch = 1 - pow(1-0.2,1.0/solverLoops);
            for(QVector<unsigned int>::iterator j=indices.begin();std::distance(j,indices.end())>1;j++)
            {
                QVector3D p1 = positions[*j].getPos();
                QVector3D p2 = positions[*(j+1)].getPos();
                QVector3D x1 = vertices[*j].getPos();
                QVector3D x2 = vertices[*(j+1)].getPos();
                QVector3D dp1(0,0,0),dp2(0,0,0);


                solveDistanceConstraint(p1,p2,m->getOriginalEdgeLength(*j,*(j+1)),k_stretch,k_stretch,dp1,dp2);
                p1 += dp1;
                p2 += dp2;

                positions[*j].setPos(p1);
                positions[*(j+1)].setPos(p2);
            }
            //Solve Tetrahedral Constraints
            QVector<QVector3D> dp;
            dp.resize(positions.size());
            solveTetrahedralConstraint(positions,faces,facemap,volume,1.0,dp);
            for(int i=0;i<dp.size();i++)
            {
                QVector3D pos = positions[i].getPos();
                QVector3D d = dp[i];
                positions[i].setPos(pos+dp[i]);
            }
            //Solve Collision Constraints
            for(QVector<ConstraintParameters>::iterator i=constraints.begin();i!=constraints.end();i++)
            {
                QVector3D dp1(0,0,0);
                QVector3D point = positions[i->index].getPos();
                solveEnviromentConstraint(point,i->normal,i->distance,dp1);
                positions[i->index].setPos(positions[i->index].getPos()+dp1);
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

    //Soft Body Physics
    for(QList<Entity>::iterator e=softList.begin();e!=softList.end();e++)
    {
        Model* m = e->getModel();
        QMatrix4x4 mat = e->getMatrix();
        QVector<unsigned int> indices = m->getIndices();
        QVector<Vertex>& vertices = m->getVertices();
        QVector<Vertex> positions = vertices;
        const QMap<int,QList<Face*>*> facemap = m->getFacemap();

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
        for(int i=0;i<positions.size();i++)
        {
            Vertex v = positions[i];
            QVector3D pos = v.getPos();

            //Collision with floor
            float dist = QVector3D::dotProduct(pos,QVector3D(0.0,1.0,0.0))+30;
            if(dist<0.0)
            {
                constraints.push_back(ConstraintParameters(i,QVector3D(0.0,1.0,0.0),-30.0));
            }
        }
        //Project Contraints
        //Solver Loops
        for(int i=0;i<solverLoops;i++)
        {
            //Solve Distance Constraint
            float k_stretch = 1 - pow(1-0.1,1.0/solverLoops);
            for(QVector<unsigned int>::iterator j=indices.begin();std::distance(j,indices.end())>1;j++)
            {
                QVector3D p1 = positions[*j].getPos();
                QVector3D p2 = positions[*(j+1)].getPos();
                QVector3D x1 = vertices[*j].getPos();
                QVector3D x2 = vertices[*(j+1)].getPos();
                QVector3D dp1(0,0,0),dp2(0,0,0);


                solveDistanceConstraint(p1,p2,m->getOriginalEdgeLength(*j,*(j+1)),k_stretch,k_stretch,dp1,dp2);
                p1 += dp1;
                p2 += dp2;

                positions[*j].setPos(p1);
                positions[*(j+1)].setPos(p2);
            }

            //Sove Bending Constraint
            /*for(QVector<unsigned int>::iterator j=indices.begin();std::distance(j,indices.end())>4;j++)
            {
                QList<Face*>* facemap.value(i);
                QVector3D p1 = positions[*j].getPos();
                QVector3D p2 = positions[*(j+1)].getPos();
                QVector3D p3 = positions[*(j+2)].getPos();
                QVector3D p4 = positions[*(j+3)].getPos();
                QVector3D dp1(0,0,0),dp2(0,0,0),dp3(0,0,0),dp4(0,0,0);


                solveBendConstraint(p1,p2,p3,p4,0.5235987755983,dp1,dp2,dp3,dp4);
                p1 += dp1;
                p2 += dp2;
                p3 += dp3;
                p4 += dp4;

                positions[*j].setPos(p1);
                positions[*(j+1)].setPos(p2);
                positions[*(j+2)].setPos(p3);
                positions[*(j+3)].setPos(p4);
            }*/

            //Solve Collision Constraints
            for(QVector<ConstraintParameters>::iterator i=constraints.begin();i!=constraints.end();i++)
            {
                QVector3D dp1(0,0,0);
                QVector3D point = positions[i->index].getPos();
                solveEnviromentConstraint(point,i->normal,i->distance,dp1);
                positions[i->index].setPos(positions[i->index].getPos()+dp1);
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
