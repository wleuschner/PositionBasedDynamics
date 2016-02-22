#include "edge.h"

Edge::Edge()
{
    v1=-1;
    v2=-1;
}

Edge::Edge(int v1, int v2)
{
    this->v1 = v1;
    this->v2 = v2;
}

bool operator==(const Edge& a,const Edge& b)
{
    if((a.v1==b.v1 && a.v2==b.v2) || (a.v2==b.v1 && a.v1==b.v2))
    {
        return true;
    }
    return false;
}

bool operator<(const Edge& a,const Edge& b)
{
    if(a.v1==b.v1)
    {
        if(a.v2<=b.v2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if(a.v1<b.v1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
