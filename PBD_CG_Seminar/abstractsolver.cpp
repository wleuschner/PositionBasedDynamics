#include "abstractsolver.h"

AbstractSolver::AbstractSolver()
{
    solverLoops = 20;
}

void AbstractSolver::addRigidBody(Entity model)
{
    rigidList.append(model);
}

void AbstractSolver::addBallonBody(Entity model)
{
    ballonList.append(model);
}

void AbstractSolver::addSoftBody(Entity model)
{
    softList.append(model);
}

void AbstractSolver::reset()
{
    rigidList.clear();
    ballonList.clear();
    softList.clear();
}
