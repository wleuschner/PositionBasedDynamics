#ifndef MODEL_H
#define MODEL_H
#include<string>
#include<QVector3D>
#include<QVector2D>
#include<QOpenGLShader>
#include<QOpenGLShaderProgram>
#include<QOpenGLBuffer>
#include<QVector>
#include"vertex.h"

class Model
{
public:
    Model();
    bool load(std::string path);
    bool setShader(const QString& vert,const QString& frag);
    bool release();
    void bind();
    void draw();
private:
    bool createVBO();
    bool createIndex();

    std::string name;
    QVector<QVector3D> position;
    QVector<QVector3D> normal;
    QVector<QVector2D> uv_coords;

    QVector<Vertex> vertices;

    QOpenGLShaderProgram shader;
    QOpenGLBuffer vbo;
};

#endif // MODEL_H
