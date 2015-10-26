#ifndef CONSTRAINTPARAMETERS_H
#define CONSTRAINTPARAMETERS_H

class ConstraintParameters
{
public:
    ConstraintParameters();
private:
    int cardinality;
    float stiffness;
    bool equal;
};

#endif // CONSTRAINTPARAMETERS_H
