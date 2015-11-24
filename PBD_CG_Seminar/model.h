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

class Model
{
public:
    Model();
    bool load(std::string path);
    bool setShader(const QString& vert,const QString& frag);
    void setMatrix(const QMatrix4x4& mat);
    const QMatrix4x4& getMatrix();
    bool release();
    void bind();
    void draw();

    QVector<Vertex>& getVertices();
    QVector<unsigned int>& getIndices();

    //Primitives
    static Model* createPlaneXZ(float width,float height,int xPatches,int zPatches);
    static Model* createPlaneXY(float width,float height,int xPatches,int yPatches);
    static Model* createPlaneYZ(float width,float height,int yPatches,int zPatches);
    static Model* createCylinder(float radius,int stacks,int slices);
    static Model* createSphere(float radius,int stacks,int slices);
    static Model* createTorus(float inner,float outer,int stacks,int slices);

    void update();
private:
    bool createVBO();
    bool createIndex();

    std::string name;
    QVector<unsigned int> indices;
    QVector<Face> faces;

    QVector<QVector3D> position;
    QVector<QVector3D> normal;
    QVector<QVector2D> uv_coords;

    QVector<Vertex> vertices;

    QMatrix4x4 mat;

    QOpenGLShaderProgram shader;
    QOpenGLBuffer vbo;
    QOpenGLBuffer index;
};

#endif // MODEL_H
