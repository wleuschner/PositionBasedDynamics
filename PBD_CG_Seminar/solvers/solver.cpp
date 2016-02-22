#include "solver.h"
#include <math.h>
#include "framework/constraints.h"
#include <collisionsphereconstraint.h>

Solver::Solver()
{
}

void Solver::solve(QList<Entity>* colObjs)
{
    double t = 1/60.0;
    float k_stretch = 1 - pow(1-AbstractSolver::stretch_k,1.0/AbstractSolver::solverLoops);
    float k_compress = 1 - pow(1-AbstractSolver::compress_k,1.0/AbstractSolver::solverLoops);

    if(colObjs!=NULL)
    {
        for(QList<Entity>::iterator i = colObjs->begin();i!=colObjs->end();i++)
        {
            i->update();
            QVector3D pos = i->getPosition();
            if(pos.x()>128||pos.x()<-128||pos.y()>128||pos.y()<-128||pos.z()>128||pos.z()<-128)
            {
                i = colObjs->erase(i);
                if(i==colObjs->end())
                {
                    break;
                }
            }
        }
    }

    //Cloth Ballon Physics
    for(QList<Entity*>::iterator e=ballonList.begin();e!=ballonList.end();e++)
    {
        Model* m = (*e)->getModel();
        QMatrix4x4 mat = (*e)->getMatrix();
        QVector<unsigned int> indices = m->getIndices();
        QVector<Vertex>& vertices = m->getVertices();
        QVector<Edge>& edges = m->getEdges();
        QVector<Vertex> positions = vertices;

        //External forces
        for(QVector<Vertex>::iterator i=positions.begin();i!=positions.end();i++)
        {
            double g = 9.81;
            double m = i->getMass();
            double w = 1/m;
            if(m!=0)
            {
                QVector3D v = i->getVelocity();
                v = v+t*w*QVector3D(0.0,0.0,0.0);
                i->setVelocity(v);
            }
            else
            {
                i->setVelocity(QVector3D(0,0,0));
            }
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
                constraints.push_back(ConstraintParameters(i,QVector3D(0.0,1.0,0.0),-30.0));
            }
        }

        QVector<Face>& faces = m->getFaces();
        const QMap<int,QList<Face*>*> facemap = m->getFacemap();
        float volume = m->getVolume();
        for(int i=0;i<solverLoops;i++)
        {
            //Solve Tetrahedral Constraints
            QVector<QVector3D> dp;
            dp.resize(positions.size());
            solveTetrahedralConstraint(positions,faces,facemap,volume,AbstractSolver::pressure_k,dp);
            for(int i=0;i<dp.size();i++)
            {
                QVector3D pos = positions[i].getPos();
                QVector3D d = dp[i];
                positions[i].setPos(pos+dp[i]);
            }
            //Solve Distance Constraint
            for(QVector<Edge>::iterator j=edges.begin();j!=edges.end();j++)
            {
                float w1 = positions[j->v1].getMass();
                float w2 = positions[j->v2].getMass();
                QVector3D p1 = positions[j->v1].getPos();
                QVector3D p2 = positions[j->v2].getPos();
                QVector3D x1 = vertices[j->v1].getPos();
                QVector3D x2 = vertices[j->v2].getPos();
                QVector3D dp1(0,0,0),dp2(0,0,0);


                solveDistanceConstraint(p1,p2,w1,w2,m->getOriginalEdgeLength(j->v1,j->v2),k_compress,k_stretch,dp1,dp2);
                p1 += dp1;
                p2 += dp2;

                positions[j->v1].setPos(p1);
                positions[j->v2].setPos(p2);
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
    for(QList<Entity*>::iterator e=softList.begin();e!=softList.end();e++)
    {
        Model* m = (*e)->getModel();
        QMatrix4x4 mat = (*e)->getMatrix();
        QVector<unsigned int> indices = m->getIndices();
        QVector<Vertex>& vertices = m->getVertices();
        QVector<Edge>& edges = m->getEdges();
        QVector<Vertex> positions = vertices;
        const QMap<int,QList<Face*>*> facemap = m->getFacemap();
        const QMap<Edge*,QList<Face*>*> adjacent = m->getAdjacentmap();


        //External forces
        for(QVector<Vertex>::iterator i=positions.begin();i!=positions.end();i++)
        {
            double g = 9.81;
            double m = i->getMass();
            double w = 1/m;
            if(m!=0)
            {
                QVector3D v = i->getVelocity();
                v = v+t*w*QVector3D(0.0,-g,0.0);
                i->setVelocity(v);
            }
            else
            {
                i->setVelocity(QVector3D(0,0,0));
            }
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
        //Generate Collisions from colObjs
        if(colObjs!=NULL)
        {
            for(QList<Entity>::iterator i = colObjs->begin();i!=colObjs->end();i++)
            {
                for(int j=0;j<positions.size();j++)
                {
                    Vertex v = positions[j];
                    QVector3D pos = v.getPos();
                    QVector3D colPos = (i)->getPosition();
                    QVector3D dVec = pos-colPos;
                    float dist = dVec.length();
                    float radius = 2;
                    if(dist-radius<=0.0)
                    {
                        CollisionSphereConstraint constr;
                        constr.radius = radius;
                        constr.pos = colPos;
                        constr.index = j;
                        sphereConstraints.push_back(constr);
                    }
                }
            }
        }

        //Project Contraints
        //Solver Loops
        for(int i=0;i<AbstractSolver::solverLoops;i++)
        {
            //Solve Distance Constraint
            for(QVector<Edge>::iterator j=edges.begin();j!=edges.end();j++)
            {
                float w1 = positions[j->v1].getMass();
                float w2 = positions[j->v2].getMass();
                QVector3D p1 = positions[j->v1].getPos();
                QVector3D p2 = positions[j->v2].getPos();
                QVector3D x1 = vertices[j->v1].getPos();
                QVector3D x2 = vertices[j->v2].getPos();
                QVector3D dp1(0,0,0),dp2(0,0,0);
                float origLength = m->getOriginalEdgeLength(j->v1,j->v2);

                solveDistanceConstraint(p1,p2,w1,w2,origLength,k_compress,k_stretch,dp1,dp2);
                p1 += dp1;
                p2 += dp2;

                positions[j->v1].setPos(p1);
                positions[j->v2].setPos(p2);
            }

            //Solve Collision Constraints
            for(QVector<ConstraintParameters>::iterator i=constraints.begin();i!=constraints.end();i++)
            {
                QVector3D dp1(0,0,0);
                QVector3D point = positions[i->index].getPos();
                solveEnviromentConstraint(point,i->normal,i->distance,dp1);
                positions[i->index].setPos(positions[i->index].getPos()+dp1);
            }

            for(QVector<CollisionSphereConstraint>::iterator i=sphereConstraints.begin();i!=sphereConstraints.end();i++)
            {
                QVector3D dp1(0,0,0);
                QVector3D point = positions[i->index].getPos();
                float mass = positions[i->index].getMass();
                QVector3D colPos = i->pos;
                solveCollisionSphereConstraint(point,mass,colPos,i->radius,dp1);
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
        sphereConstraints.clear();
        constraints.clear();
        m->recalNormals();
        m->update();
    }
}
