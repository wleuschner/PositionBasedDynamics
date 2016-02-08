#ifndef MODEL_H
#define MODEL_H
#include<string>
#include<QVector3D>
#include<QVector2D>
#include<QOpenGLShader>
#include<QOpenGLShaderProgram>
#include<QOpenGLBuffer>
#include<QOpenGLTexture>
#include<QMatrix>
#include<QVector>
#include"geometry/vertex.h"
#include"geometry/face.h"
#include"geometry/edge.h"
#include"structs/spatialhash.h"
#include"graphics/material.h"

class Model
{
public:
    Model();
    ~Model();
    bool load(std::string path);
    bool release();
    void bind();
    void draw(QOpenGLShaderProgram* shader);

    Material getMaterial() const;
    void setMaterial(const Material &value);
    float getOriginalEdgeLength(int v1,int v2);
    QVector<Vertex>& getVertices();
    QVector<unsigned int>& getIndices();
    QVector<Face>& getFaces();
    QVector<Edge>& getEdges();
    const QMap<int,QList<Face*>*>& getFacemap();
    float getVolume();


    //Primitives
    static Model* createPlaneXZ(float width,float height,int xPatches,int zPatches);
    static Model* createPlaneXY(float width,float height,int xPatches,int yPatches);
    static Model* createPlaneYZ(float width,float height,int yPatches,int zPatches);
    static Model* createCylinder(float radius,int stacks,int slices);
    static Model* createSphere(float radius,int stacks,int slices);
    static Model* createTorus(float inner,float outer,int stacks,int slices);

    void update();
    void recalNormals();

private:
    float calcVolume();
    void createFacemap();
    bool createVBO();
    bool createIndex();

    std::string name;
    bool doubleFaced;
    float volume;
    Material material;
    QVector<unsigned int> indices;
    QVector<Face> faces;
    QVector<Edge> edges;
    QMap<int,QList<Face*>*> facemap;

    QVector<QVector3D> position;
    QVector<QVector3D> normal;
    QVector<QVector2D> uv_coords;

    QVector<Vertex> vertices;

    QOpenGLBuffer vbo;
    QOpenGLBuffer index;

    SpatialHash* shash;
};

#endif // MODEL_H
