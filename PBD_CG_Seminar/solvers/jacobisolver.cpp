#include "jacobisolver.h"


JacobiSolver::JacobiSolver()
{
}

void JacobiSolver::solve(QList<Entity>* colObjs)
{
    /*double t = 1/60.0;
    float k_stretch = 1 - pow(1-AbstractSolver::stretch_k,1.0/AbstractSolver::solverLoops);
    float k_compress = 1 - pow(1-AbstractSolver::compress_k,1.0/AbstractSolver::solverLoops);

    //Rigid Body Physics
    for(QList<Entity*>::iterator e=rigidList.begin();e!=rigidList.end();e++)
    {
        Model* m = (*e)->getModel();
        QMatrix4x4 mat = (*e)->getMatrix();
        QVector<unsigned int> indices = m->getIndices();
        QVector<Vertex>& vertices = m->getVertices();
        QVector<Edge>& edges = m->getEdges();
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

        for(int i=0;i<solverLoops;i++)
        {
            //Solve Distance Constraint
            for(QVector<Edge>::iterator j=edges.begin();j!=edges.end();j++)
            {
                QVector3D p1 = positions[j->v1].getPos();
                QVector3D p2 = positions[j->v2].getPos();
                QVector3D x1 = vertices[j->v1].getPos();
                QVector3D x2 = vertices[j->v2].getPos();
                QVector3D dp1(0,0,0),dp2(0,0,0);


                solveDistanceConstraint(p1,p2,m->getOriginalEdgeLength(j->v1,j->v2),k_compress,k_stretch,dp1,dp2);
                p1 += dp1;
                p2 += dp2;

                positions[j->v1].setPos(p1);
                positions[j->v2].setPos(p2);
            }
        }
    }

    //Cloth Ballon Physics
    for(QList<Entity*>::iterator e=ballonList.begin();e!=ballonList.end();e++)
    {
    }

    //Soft Body Physics
    for(QList<Entity*>::iterator e=softList.begin();e!=softList.end();e++)
    {
    }*/
}
