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
    const aiScene* scene = importer.ReadFile(path,aiProcess_Triangulate|aiProcess_PreTransformVertices|aiProcess_JoinIdenticalVertices|aiProcess_GenNormals);
    for(unsigned int j=0;j<scene->mNumMeshes;j++)
    {
        const aiMesh* mesh = scene->mMeshes[j];

        int mat_index = mesh->mMaterialIndex;
        const aiMaterial* mat = scene->mMaterials[mat_index];

        aiColor3D mat_ambient;
        aiColor3D mat_diffuse;
        aiColor3D mat_specular;
        float mat_shininess;
        mat->Get(AI_MATKEY_COLOR_AMBIENT,mat_ambient);
        mat->Get(AI_MATKEY_COLOR_DIFFUSE,mat_diffuse);
        mat->Get(AI_MATKEY_COLOR_SPECULAR,mat_specular);
        mat->Get(AI_MATKEY_SHININESS,mat_shininess);
        for(unsigned int i=0;i<mesh->mNumVertices;i++)
        {
            aiVector3D v = mesh->mVertices[i];
            position.push_back(QVector3D(v[0],v[1],v[2]));
            if(mesh->HasNormals())
            {
                aiVector3D n = mesh->mNormals[i];
                normal.push_back(QVector3D(n[0],n[1],n[2]));
            }
            //if(mesh->HasTextureCoords())
            //{
            //    aiVector2D uv = mesh->mTextureCoords[i];
            //    uv_coords.push_back(QVector2D(uv[0],uv[1]));
            //}
            Vertex vert;
            vert.setPos(position[i]);
            vert.setNormal(normal[i]);
            vert.setUv(QVector2D(0,0));
            vert.setAmbient(QVector3D(mat_ambient.r,mat_ambient.g,mat_ambient.b));
            vert.setDiffuse(QVector3D(mat_diffuse.r,mat_diffuse.g,mat_specular.b));
            vert.setSpecular(QVector3D(mat_specular.r,mat_specular.g,mat_specular.b));
            vert.setShininess(1.0);
            vert.setMass(1.0f);
            vert.setVelocity(QVector3D(0,0,0));
            vertices.push_back(vert);
        }
        for(int i=0;i<mesh->mNumFaces;i++)
        {
            indices.push_back(mesh->mFaces[i].mIndices[0]);
            indices.push_back(mesh->mFaces[i].mIndices[1]);
            indices.push_back(mesh->mFaces[i].mIndices[2]);
        }
    }
    createVBO();
    createIndex();
    mat.setToIdentity();
    return true;
}

void Model::setMatrix(const QMatrix4x4& mat)
{
    this->mat=mat;
}

const QMatrix4x4& Model::getMatrix()
{
    return mat;
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
    vbo.release();
    return true;
}

void Model::bind()
{
    vbo.bind();
    index.bind();
}

void Model::update()
{
    release();
    createVBO();
    bind();
}

QVector<Vertex>& Model::getVertices()
{
    return vertices;
}

QVector<unsigned int>& Model::getIndices()
{
    return indices;
}

bool Model::createVBO()
{
    if(!vbo.create())
    {
        return false;
    }
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    if(!vbo.bind())
    {
        return false;
    }
    vbo.allocate(vertices.constData(),sizeof(Vertex)*vertices.length());
    return true;
}

bool Model::createIndex()
{
    index = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    if(!index.create())
    {
        return false;
    }
    if(!index.bind())
    {
        return false;
    }
    index.setUsagePattern(QOpenGLBuffer::StaticDraw);
    index.allocate(indices.constData(),sizeof(unsigned int)*indices.length());
    return true;
}

void Model::draw()
{
    glDrawElements(GL_TRIANGLES,indices.length(),GL_UNSIGNED_INT,(void*)0);
}

Model* Model::createPlaneXZ(float width,float height,int xPatches,int zPatches)
{
    float centerX=width/2;
    float centerZ=height/2;

    float patchXStep = width/xPatches;
    float patchZStep = height/zPatches;

    Model *model = new Model();

    for(int z=0;z<zPatches-1;z++)
    {
        for(int x=0;x<xPatches-1;x++)
        {
            //Error in UV COORDS cast float
            model->position.push_back(QVector3D(patchXStep*x-centerX,0,patchZStep*z-centerZ));
            model->normal.push_back(QVector3D(0,1,0));
            model->uv_coords.push_back(QVector2D(x/xPatches,z/zPatches));
            model->position.push_back(QVector3D(patchXStep*(x+1)-centerX,0,patchZStep*z-centerZ));
            model->normal.push_back(QVector3D(0,1,0));
            model->uv_coords.push_back(QVector2D(x/xPatches,z/zPatches));
            model->position.push_back(QVector3D(patchXStep*(x+1)-centerX,0,patchZStep*(z+1)-centerZ));
            model->normal.push_back(QVector3D(0,1,0));
            model->uv_coords.push_back(QVector2D(x/xPatches,z/zPatches));

            model->position.push_back(QVector3D(patchXStep*(x+1)-centerX,0,patchZStep*(z+1)-centerZ));
            model->normal.push_back(QVector3D(0,1,0));
            model->uv_coords.push_back(QVector2D(x/xPatches,z/zPatches));
            model->position.push_back(QVector3D(patchXStep*x-centerX,0,patchZStep*(z+1)-centerZ));
            model->normal.push_back(QVector3D(0,1,0));
            model->uv_coords.push_back(QVector2D(x/xPatches,z/zPatches));
            model->position.push_back(QVector3D(patchXStep*x-centerX,0,patchZStep*z-centerZ));
            model->normal.push_back(QVector3D(0,1,0));
            model->uv_coords.push_back(QVector2D(x/xPatches,z/zPatches));
        }
    }
    for(int i=0;i<model->position.length();i++)
    {
        Vertex v;
        v.setPos(model->position[i]);
        v.setNormal(model->normal[i]);
        v.setUv(model->uv_coords[i]);

        v.setAmbient(QVector3D(0.2,0.2,0.2));
        v.setDiffuse(QVector3D(0.4,0.4,0.4));
        v.setSpecular(QVector3D(0.8,0.8,0.8));
        v.setShininess(1.0);
        v.setMass(1.0f);
        v.setVelocity(QVector3D(0,0,0));
        model->vertices.push_back(v);
    }
    model->createVBO();
    model->mat.setToIdentity();
    return model;
}

Model* Model::createPlaneXY(float width,float height,int xPatches,int yPatches)
{
    float centerX=width/2;
    float centerY=height/2;

    float patchXStep = width/xPatches;
    float patchYStep = height/yPatches;

    Model *model = new Model();

    for(int y=0;y<yPatches-1;y++)
    {
        for(int x=0;x<xPatches-1;x++)
        {
            //Error in UV COORDS cast float
            model->position.push_back(QVector3D(patchXStep*x-centerX,patchYStep*y-centerY,0));
            model->normal.push_back(QVector3D(0,0,1));
            model->uv_coords.push_back(QVector2D(x/xPatches,y/yPatches));
            model->position.push_back(QVector3D(patchXStep*(x+1)-centerX,patchYStep*y-centerY,0));
            model->normal.push_back(QVector3D(0,0,1));
            model->uv_coords.push_back(QVector2D(x/xPatches,y/yPatches));
            model->position.push_back(QVector3D(patchXStep*(x+1)-centerX,patchYStep*(y+1)-centerY,0));
            model->normal.push_back(QVector3D(0,0,1));
            model->uv_coords.push_back(QVector2D(x/xPatches,y/yPatches));

            model->position.push_back(QVector3D(patchXStep*(x+1)-centerX,patchYStep*(y+1)-centerY,0));
            model->normal.push_back(QVector3D(0,0,1));
            model->uv_coords.push_back(QVector2D(x/xPatches,y/yPatches));
            model->position.push_back(QVector3D(patchXStep*x-centerX,patchYStep*(y+1)-centerY,0));
            model->normal.push_back(QVector3D(0,0,1));
            model->uv_coords.push_back(QVector2D(x/xPatches,y/yPatches));
            model->position.push_back(QVector3D(patchXStep*x-centerX,patchYStep*y-centerY,0));
            model->normal.push_back(QVector3D(0,0,1));
            model->uv_coords.push_back(QVector2D(x/xPatches,y/yPatches));
        }
    }
    for(int i=0;i<model->position.length();i++)
    {
        Vertex v;
        v.setPos(model->position[i]);
        v.setNormal(model->normal[i]);
        v.setUv(model->uv_coords[i]);

        v.setAmbient(QVector3D(0.2,0.2,0.2));
        v.setDiffuse(QVector3D(0.4,0.4,0.4));
        v.setSpecular(QVector3D(0.8,0.8,0.8));
        v.setShininess(1.0);
        v.setMass(1.0f);
        v.setVelocity(QVector3D(0,0,0));
        model->vertices.push_back(v);
    }
    model->createVBO();
    model->mat.setToIdentity();
    return model;
}

Model* Model::createPlaneYZ(float width,float height,int yPatches,int zPatches)
{
    float centerZ=width/2;
    float centerY=height/2;

    float patchZStep = width/zPatches;
    float patchYStep = height/yPatches;

    Model *model = new Model();

    for(int y=0;y<yPatches-1;y++)
    {
        for(int z=0;z<zPatches-1;z++)
        {
            //Error in UV COORDS cast float
            model->position.push_back(QVector3D(0,patchYStep*y-centerY,patchZStep*z-centerZ));
            model->normal.push_back(QVector3D(1,0,0));
            model->uv_coords.push_back(QVector2D(z/zPatches,y/yPatches));
            model->position.push_back(QVector3D(0,patchYStep*(y+1)-centerY,patchZStep*z-centerZ));
            model->normal.push_back(QVector3D(1,0,0));
            model->uv_coords.push_back(QVector2D(z/zPatches,y/yPatches));
            model->position.push_back(QVector3D(0,patchYStep*(y+1)-centerY,patchZStep*(z+1)-centerZ));
            model->normal.push_back(QVector3D(1,0,0));
            model->uv_coords.push_back(QVector2D(z/zPatches,y/yPatches));

            model->position.push_back(QVector3D(0,patchYStep*(y+1)-centerY,patchZStep*(z+1)-centerZ));
            model->normal.push_back(QVector3D(1,0,0));
            model->uv_coords.push_back(QVector2D(z/zPatches,y/yPatches));
            model->position.push_back(QVector3D(0,patchYStep*y-centerY,patchZStep*(z+1)-centerZ));
            model->normal.push_back(QVector3D(1,0,0));
            model->uv_coords.push_back(QVector2D(z/zPatches,y/yPatches));
            model->position.push_back(QVector3D(0,patchYStep*y  -centerY,patchZStep*z-centerZ));
            model->normal.push_back(QVector3D(1,0,0));
            model->uv_coords.push_back(QVector2D(z/zPatches,y/yPatches));
        }
    }
    for(int i=0;i<model->position.length();i++)
    {
        Vertex v;
        v.setPos(model->position[i]);
        v.setNormal(model->normal[i]);
        v.setUv(model->uv_coords[i]);

        v.setAmbient(QVector3D(0.2,0.2,0.2));
        v.setDiffuse(QVector3D(0.4,0.4,0.4));
        v.setSpecular(QVector3D(0.8,0.8,0.8));
        v.setShininess(1.0);
        v.setMass(1.0f);
        v.setVelocity(QVector3D(0,0,0));
        model->vertices.push_back(v);
    }
    model->createVBO();
    model->mat.setToIdentity();
    return model;
}

Model* Model::createCylinder(float radius,int stacks,int slices)
{
}

Model* Model::createSphere(float radius,int stacks,int slices)
{
}

Model* Model::createTorus(float inner,float outer,int stacks,int slices)
{
}
