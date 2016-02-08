#ifndef JACOBISOLVER_H
#define JACOBISOLVER_H
#include"framework/abstractsolver.h"

class JacobiSolver : public AbstractSolver
{
public:
    JacobiSolver();
    void solve(QList<Entity>* colObjs=0);
};

#endif // JACOBISOLVER_H
