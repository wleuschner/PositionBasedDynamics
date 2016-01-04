#ifndef SPATIALHASH_H
#define SPATIALHASH_H
#include<map>
#include<list>
#include"vertex.h"

class SpatialHash
{
public:
    struct Item
    {
        Vertex v1;
        Vertex v2;
        Vertex v3;
        bool operator==(const Item& a)
        {
            bool ret = true;
            QVector3D a1 = a.v1.getPos();
            QVector3D a2 = a.v2.getPos();
            QVector3D a3 = a.v3.getPos();
            QVector3D b1 = v1.getPos();
            QVector3D b2 = v2.getPos();
            QVector3D b3 = v3.getPos();
            if(a1!=b1 || a2!=b2 || a3!=b3)
            {
                ret = false;
            }
            return ret;
        }
    };

    SpatialHash(float cellSize);

    void insert(Vertex* v1,Vertex* v2,Vertex* v3);
    void remove(Vertex* v1,Vertex* v2,Vertex* v3);
    std::list<SpatialHash::Item> get(float x,float y,float z);
    void clear();
private:
    float cellSize;
    std::map<unsigned int,std::map<unsigned int,std::map<unsigned int,std::list<Item>>>> buckets;
};

#endif // SPATIALHASH_H
