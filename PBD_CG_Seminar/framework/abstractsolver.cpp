#include "abstractsolver.h"

int AbstractSolver::solverLoops = 20;
float AbstractSolver::pressure_k = 1.0;
float AbstractSolver::stretch_k = 0.5;
float AbstractSolver::compress_k = 0.5;
float AbstractSolver::bend_k = 0.5;
QList<Entity*> AbstractSolver::rigidList;
QList<Entity*> AbstractSolver::ballonList;
QList<Entity*> AbstractSolver::softList;

AbstractSolver::AbstractSolver()
{
}

void AbstractSolver::addRigidBody(Entity* model)
{
    AbstractSolver::rigidList.append(model);
}

void AbstractSolver::addBallonBody(Entity* model)
{
    AbstractSolver::ballonList.append(model);
}

void AbstractSolver::addSoftBody(Entity* model)
{
    AbstractSolver::softList.append(model);
}

void AbstractSolver::reset()
{
    AbstractSolver::rigidList.clear();
    AbstractSolver::ballonList.clear();
    AbstractSolver::softList.clear();
}

int AbstractSolver::getSolverLoops()
{
    return AbstractSolver::solverLoops;
}

void AbstractSolver::setSolverLoops(int loops)
{
    AbstractSolver::solverLoops = loops;
}

float AbstractSolver::getPressure()
{
    return AbstractSolver::pressure_k;
}

void AbstractSolver::setPressure(float val)
{
    AbstractSolver::pressure_k = val;
}

float AbstractSolver::getStretchStiffness()
{
    return AbstractSolver::stretch_k;
}

void AbstractSolver::setStretchStiffness(double val)
{
    AbstractSolver::stretch_k = val;
}

float AbstractSolver::getCompressStiffness()
{
    return AbstractSolver::compress_k;
}

void AbstractSolver::setCompressStiffness(double val)
{
    AbstractSolver::compress_k = val;
}

float AbstractSolver::getBendStiffness()
{
    return AbstractSolver::bend_k;
}

void AbstractSolver::setBendStiffness(double val)
{
    AbstractSolver::bend_k = val;
}
