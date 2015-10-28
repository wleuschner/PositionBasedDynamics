#include "model.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>
#include <assimp/scene.h>

Model::Model()
{
}

bool Model::load(std::string path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path,aiProcess_Triangulate);
    for(int j=0;j<scene->mNumMeshes;j++)
    {
        const aiMesh* mesh = scene->mMeshes[j];
        for(int i=0;i<mesh->mNumVertices;i++)
        {
            aiVector3D v = mesh->mVertices[i];
            aiVector3D n = mesh->mNormals[i];
            position.push_back(QVector3D(v[0],v[1],v[2]));
            normal.push_back(QVector3D(n[0],n[1],n[2]));
        }
    }

    for(int i=0;i<position.length();i++)
    {
        Vertex vert;
        vert.setPos(position[i]);
        vert.setNormal(normal[i]);
        vert.setUv(QVector2D(0,0));
        vert.setAmbient(QVector3D(0.2,0.2,0.2));
        vert.setDiffuse(QVector3D(0.4,0.4,0.4));
        vert.setSpecular(QVector3D(0.8,0.8,0.8));
        vert.setShininess(1.0);
        vert.setMass(1.0f);
        vert.setVelocity(0.0f);
        vertices.push_back(vert);
    }
    createVBO();
    return true;
}

bool Model::setShader(const QString& vert,const QString& frag)
{
    bool result = shader.addShaderFromSourceFile(QOpenGLShader::Vertex,vert);
    if(!result)
    {
        qWarning()<<shader.log();
    }
    result = shader.addShaderFromSourceFile(QOpenGLShader::Fragment,frag);
    if(!result)
    {
        qWarning()<<shader.log();
    }
    result = shader.link();
    if(!result)
    {
        qWarning()<<shader.log();
    }
    return result;
}

bool Model::release()
{
    return true;
}

void Model::bind()
{
    vbo.bind();
}

bool Model::createVBO()
{
    qDebug()<<sizeof(Vertex);
    if(!vbo.create())
    {
        return false;
    }
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    if(!vbo.bind())
    {
        return false;
    }
    qDebug()<<sizeof(Vertex)*vertices.length();
    vbo.allocate(vertices.constData(),sizeof(Vertex)*vertices.length());
    return true;
}

void Model::draw()
{
    glDrawArrays(GL_TRIANGLES,0,vertices.length());
}
