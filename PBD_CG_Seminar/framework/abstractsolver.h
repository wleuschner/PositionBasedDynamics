#ifndef ABSTRACTSOLVER_H
#define ABSTRACTSOLVER_H
#include"graphics/entity.h"

class AbstractSolver
{
public:
    AbstractSolver();
    void addRigidBody(Entity* model);
    void addBallonBody(Entity* model);
    void addSoftBody(Entity* model);

    virtual void solve(QList<Entity>* colObjs=0)=0;

    void reset();

    int getSolverLoops();
    void setSolverLoops(int loops);

    float getPressure();
    void setPressure(float val);

    float getStretchStiffness();
    void setStretchStiffness(double val);

    float getCompressStiffness();
    void setCompressStiffness(double val);

    float getBendStiffness();
    void setBendStiffness(double val);

protected:
    static int solverLoops;
    static float pressure_k;
    static float stretch_k;
    static float compress_k;
    static float bend_k;

    static QList<Entity*> rigidList;
    static QList<Entity*> ballonList;
    static QList<Entity*> softList;
};

#endif // ABSTRACTSOLVER_H
