#ifndef EDGE_H
#define EDGE_H

class Edge
{
public:
    int v1;
    int v2;

    Edge();
    Edge(int v1,int v2);
};

bool operator==(const Edge& a,const Edge& b);
bool operator<(const Edge& a,const Edge& b);

#endif // EDGE_H
