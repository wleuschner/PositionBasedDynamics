#include "spatialhash.h"
#include <QVector3D>
#include <QDebug>

SpatialHash::SpatialHash(float cellSize)
{
    this->cellSize = cellSize;
}

void SpatialHash::insert(Vertex* v1,Vertex* v2,Vertex* v3)
{
    int x1,y1,z1;
    int x2,y2,z2;
    int x3,y3,z3;

    //Create Item
    Item item;
    item.v1=*v1;
    item.v2=*v2;
    item.v3=*v3;

    //Compute buckets v1
    x1 = v1->getPos().x()/cellSize;
    y1 = v1->getPos().y()/cellSize;
    z1 = v1->getPos().z()/cellSize;
    //Compute buckets v2
    x2 = v2->getPos().x()/cellSize;
    y2 = v2->getPos().y()/cellSize;
    z2 = v2->getPos().z()/cellSize;
    //Compute buckets v3
    x3 = v3->getPos().x()/cellSize;
    y3 = v3->getPos().y()/cellSize;
    z3 = v3->getPos().z()/cellSize;

    if(buckets[x1][y1][z1].empty())
    {
        buckets[x1][y1][z1].push_back(item);
    }
    if(x1!=x2 || y1!=x2 || z1!=z2)
    {
        if(buckets[x2][y2][z2].empty())
        {
            buckets[x2][y2][z2].push_back(item);
        }
    }
    if(x1!=x3 || y1!=y3 || y1!=y3)
    {
        if(buckets[x3][y3][z3].empty())
        {
            buckets[x3][y3][z3].push_back(item);
        }
    }
}

void SpatialHash::remove(Vertex* v1,Vertex* v2,Vertex* v3)
{
    int x1,y1,z1;
    int x2,y2,z2;
    int x3,y3,z3;

    //Create Item
    Item item;
    item.v1=*v1;
    item.v2=*v2;
    item.v3=*v3;

    //Compute buckets v1
    x1 = v1->getPos().x()/cellSize;
    y1 = v1->getPos().y()/cellSize;
    z1 = v1->getPos().z()/cellSize;

    //Compute buckets v2
    x2 = v2->getPos().x()/cellSize;
    y2 = v2->getPos().y()/cellSize;
    z2 = v2->getPos().z()/cellSize;

    //Compute buckets v3
    x3 = v3->getPos().x()/cellSize;
    y3 = v3->getPos().y()/cellSize;
    z3 = v3->getPos().z()/cellSize;

    buckets[x1][y1][z1].remove(item);
    buckets[x2][y2][z2].remove(item);
    buckets[x3][y3][z3].remove(item);
}

std::list<SpatialHash::Item> SpatialHash::get(float x,float y,float z)
{
    return buckets[x][y][z];
}

void SpatialHash::clear()
{
    for(unsigned int x=0;x<buckets.size();x++)
    {
        for(unsigned int y=0;y<buckets[x].size();y++)
        {
            for(unsigned int z=0;z<buckets[x][y].size();z++)
            {
                buckets[x][y][z].clear();
            }
            buckets[x][y].clear();
        }
        buckets[x].clear();
    }
    buckets.clear();
}
