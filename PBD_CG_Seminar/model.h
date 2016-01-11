#ifndef MODEL_H
#define MODEL_H
#include<string>
#include<QVector3D>
#include<QVector2D>
#include<QOpenGLShader>
#include<QOpenGLShaderProgram>
#include<QOpenGLBuffer>
#include<QMatrix>
#include<QVector>
#include"vertex.h"
#include"face.h"
#include"spatialhash.h"

class Model
{
public:
    Model();
    ~Model();
    bool load(std::string path);
    bool release();
    void bind();
    void draw(QOpenGLShaderProgram& shader);

    float getOriginalEdgeLength(int v1,int v2);
    QVector<Vertex>& getVertices();
    QVector<unsigned int>& getIndices();
    QVector<Face>& getFaces();
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
    float volume;
    QVector<unsigned int> indices;
    QVector<Face> faces;
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
