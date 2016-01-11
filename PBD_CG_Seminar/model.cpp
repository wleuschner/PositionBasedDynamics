#include "model.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#define PI2 6.28318530718

Model::Model()
{
    shash = NULL;
}

Model::~Model()
{
    if(shash!=NULL)
    {
        delete shash;
    }
}

bool Model::load(std::string path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path,aiProcess_Triangulate|aiProcess_PreTransformVertices|aiProcess_JoinIdenticalVertices|aiProcess_GenNormals);
    for(unsigned int j=0;j</*scene->mNumMeshes*/1;j++)
    {
        const aiMesh* mesh = scene->mMeshes[j];
        aiColor3D mat_ambient;
        aiColor3D mat_diffuse;
        aiColor3D mat_specular;

        int mat_index = mesh->mMaterialIndex;
        const aiMaterial* mat = scene->mMaterials[mat_index];

        float mat_shininess;

        mat->Get(AI_MATKEY_COLOR_AMBIENT,mat_ambient);
        mat->Get(AI_MATKEY_COLOR_DIFFUSE,mat_diffuse);
        mat->Get(AI_MATKEY_COLOR_SPECULAR,mat_specular);
        mat->Get(AI_MATKEY_SHININESS,mat_shininess);
        position.reserve(mesh->mNumVertices);
        for(unsigned int i=0;i<mesh->mNumVertices;i++)
        {
            aiVector3D v = mesh->mVertices[i];
            QVector3D pos = QVector3D(v.x,v.y,v.z);
            position.push_back(pos);
            if(mesh->HasNormals())
            {
                aiVector3D n = mesh->mNormals[i];
                normal.push_back(QVector3D(n.x,n.y,n.z));
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
            Face f;
            f.v1=mesh->mFaces[i].mIndices[0];
            f.v2=mesh->mFaces[i].mIndices[1];
            f.v3=mesh->mFaces[i].mIndices[2];
            indices.push_back(f.v1);
            indices.push_back(f.v2);
            indices.push_back(f.v3);
            faces.push_back(f);
        }
    }
    createFacemap();
    volume = calcVolume();
    qDebug()<<volume;
    recalNormals();
    createVBO();
    createIndex();
    return true;
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

float Model::calcVolume()
{
    float volume = 0;
    for(int f=0;f<faces.size();f++)
    {
        Face face = faces[f];
        QVector3D v1 = vertices[face.v1].getPos();
        QVector3D v2 = vertices[face.v2].getPos();
        QVector3D v3 = vertices[face.v3].getPos();
        volume += QVector3D::dotProduct(v3,QVector3D::crossProduct(v1,v2));
    }
    return volume;
}

void Model::createFacemap()
{
    for(int v=0;v<vertices.size();v++)
    {
        for(int f=0;f<faces.size();f++)
        {
            Face face = faces[f];
            if(face.v1 == v || face.v2 == v || face.v3 == v)
            {
                if(!facemap.contains(v))
                {
                    facemap.insert(v,new QList<Face*>());
                }
                facemap.value(v)->append(&faces[f]);
            }
        }
    }
}

void Model::recalNormals()
{
    for(int f=0;f<faces.size();f++)
    {
        Face face = faces[f];
        QVector3D v1 = vertices[face.v1].getPos();
        QVector3D v2 = vertices[face.v2].getPos();
        QVector3D v3 = vertices[face.v3].getPos();
        faces[f].normal = QVector3D::crossProduct(v1-v2,v1-v3).normalized();
    }
    for(int v=0;v<vertices.size();v++)
    {
        QVector3D norm = QVector3D(0,0,0);
        QList<Face*>* facelist = facemap.value(v);
        int numFaces = facelist->size();
        for(QList<Face*>::iterator f = facelist->begin();f!=facelist->end();f++)
        {
            norm += (*f)->normal;
        }
        norm = (norm/numFaces).normalized();
        vertices[v].setNormal(norm);
    }
}

float Model::getOriginalEdgeLength(int v1,int v2)
{
    QVector3D a=position[v1];
    QVector3D b=position[v2];
    return (a-b).length();
}

QVector<Vertex>& Model::getVertices()
{
    return vertices;
}

QVector<unsigned int>& Model::getIndices()
{
    return indices;
}

QVector<Face>& Model::getFaces()
{
    return faces;
}

const QMap<int,QList<Face*>*>& Model::getFacemap()
{
    return facemap;
}

float Model::getVolume()
{
    return volume;
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

void Model::draw(QOpenGLShaderProgram& shader)
{
    bind();
    shader.setAttributeBuffer("vertex",GL_FLOAT,0,3,sizeof(Vertex));
    shader.enableAttributeArray("vertex");

    shader.setAttributeBuffer("normal",GL_FLOAT,sizeof(float)*3,3,sizeof(Vertex));
    shader.enableAttributeArray("normal");

    shader.setAttributeBuffer("uv",GL_FLOAT,sizeof(float)*6,2,sizeof(Vertex));
    shader.enableAttributeArray("uv");

    shader.setAttributeBuffer("ambient",GL_FLOAT,sizeof(float)*8,3,sizeof(Vertex));
    shader.enableAttributeArray("ambient");

    shader.setAttributeBuffer("diffuse",GL_FLOAT,sizeof(float)*11,3,sizeof(Vertex));
    shader.enableAttributeArray("diffuse");

    shader.setAttributeBuffer("specular",GL_FLOAT,sizeof(float)*14,3,sizeof(Vertex));
    shader.enableAttributeArray("specular");

    shader.setAttributeBuffer("shininess",GL_FLOAT,sizeof(float)*17,1,sizeof(Vertex));
    shader.enableAttributeArray("shininess");

    shader.setAttributeBuffer("mass",GL_FLOAT,sizeof(float)*18,1,sizeof(Vertex));
    shader.enableAttributeArray("mass");

    shader.setAttributeBuffer("velocity",GL_FLOAT,sizeof(float)*19,3,sizeof(Vertex));
    shader.enableAttributeArray("velocity");

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
    model->createFacemap();
    model->createVBO();
    model->createIndex();
    return model;
}

Model* Model::createPlaneXY(float width,float height,int xPatches,int yPatches)
{
    float centerX=width/2;
    float centerY=height/2;

    float patchXStep = width/xPatches;
    float patchYStep = height/yPatches;

    Model *model = new Model();
    for(int y=0;y<yPatches;y++)
    {
        for(int x=0;x<xPatches;x++)
        {
            model->position.push_back(QVector3D(x*patchXStep-centerX,y*patchYStep-centerY,0.0));
            model->normal.push_back(QVector3D(0.0,0.0,1.0));
            model->uv_coords.push_back(QVector2D(x/((float)width),y/((float)height)));
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
    for(int y=0;y<yPatches-1;y++)
    {
        for(int x=0;x<xPatches-1;x++)
        {
            Face f1,f2;
            //Face 1
            model->indices.push_back(y*xPatches+x);
            f1.v1=y*xPatches+x;
            model->indices.push_back((y+1)*xPatches+x);
            f1.v2=(y+1)*xPatches+x;
            model->indices.push_back(y*xPatches+(x+1));
            f1.v3=y*xPatches+(x+1);
            model->faces.push_back(f1);

            //Face 2
            model->indices.push_back((y+1)*xPatches+x);
            f2.v1=(y+1)*xPatches+x;
            model->indices.push_back((y+1)*xPatches+(x+1));
            f2.v2=(y+1)*xPatches+(x+1);
            model->indices.push_back(y*xPatches+(x+1));
            f2.v3=y*xPatches+(x+1);
            model->faces.push_back(f2);
        }
    }
    model->createFacemap();
    model->createVBO();
    model->createIndex();
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
    model->createFacemap();
    model->createVBO();
    model->createIndex();
    return model;
}

Model* Model::createCylinder(float radius,int stacks,int slices)
{
    Model *model = new Model();
    float angle_inc = PI2/slices;
    float r = radius;
    for(int y=-stacks/2;y<stacks/2;y++)
    {
        float angle = 0.0;
        for(int x=0;x<slices;x++,angle+=angle_inc)
        {
            fmax(r,y);
            model->position.push_back(QVector3D(radius*cosf(angle),y,radius*sinf(angle)));
            model->normal.push_back(QVector3D(cosf(angle),0.0,sinf(angle)));
            model->uv_coords.push_back(QVector2D(x/((float)slices),y/((float)stacks)));
        }
    }

    model->shash = new SpatialHash(2.0);
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
    int y;
    for(y=0;y<stacks-1;y++)
    {
        int x;
        for(x=0;x<slices-1;x++)
        {
            Face f1,f2;
            //Face 1
            model->indices.push_back(y*slices+x);
            f1.v1=y*slices+x;
            model->indices.push_back((y+1)*slices+x);
            f1.v2=(y+1)*slices+x;
            model->indices.push_back(y*slices+(x+1));
            f1.v3=y*slices+(x+1);
            model->faces.push_back(f1);

            //Insert into Spatial Hash
            Vertex* p1 = &model->vertices[f1.v1];
            Vertex* p2 = &model->vertices[f1.v2];
            Vertex* p3 = &model->vertices[f1.v3];
            model->shash->insert(p1,p2,p3);

            //Face 2
            model->indices.push_back((y+1)*slices+x);
            f2.v1=(y+1)*slices+x;
            model->indices.push_back((y+1)*slices+(x+1));
            f2.v2=(y+1)*slices+(x+1);
            model->indices.push_back(y*slices+(x+1));
            f2.v3=y*slices+(x+1);
            model->faces.push_back(f2);

            //Insert into Spatial Hash
            p1 = &model->vertices[f2.v1];
            p2 = &model->vertices[f2.v2];
            p3 = &model->vertices[f2.v3];
            model->shash->insert(p1,p2,p3);
        }

        Face f1,f2;

        //Face 1
        model->indices.push_back(y*slices+x);
        f1.v1=y*slices+x;
        model->indices.push_back((y+1)*slices+x);
        f1.v2=(y+1)*slices+x;
        model->indices.push_back(y*slices);
        f1.v3=y*slices;
        model->faces.push_back(f1);

        //Insert into Spatial Hash
        Vertex* p1 = &model->vertices[f1.v1];
        Vertex* p2 = &model->vertices[f1.v2];
        Vertex* p3 = &model->vertices[f1.v3];
        model->shash->insert(p1,p2,p3);

        //Face 2
        model->indices.push_back((y+1)*slices+x);
        f2.v1=(y+1)*slices+x;
        model->indices.push_back((y+1)*slices);
        f2.v2=(y+1)*slices;
        model->indices.push_back(y*slices);
        f2.v3=y*slices;
        model->faces.push_back(f2);

        //Insert into Spatial Hash
        p1 = &model->vertices[f2.v1];
        p2 = &model->vertices[f2.v2];
        p3 = &model->vertices[f2.v3];
        model->shash->insert(p1,p2,p3);
    }
    model->createFacemap();
    model->volume = model->calcVolume();
    model->createVBO();
    model->createIndex();
    qDebug()<<model->volume;
    return model;
}

Model* Model::createSphere(float radius,int stacks,int slices)
{
    Model *model = new Model();
    float angle1_inc = (PI2/2)/(stacks-1);
    float angle2_inc = PI2/slices;
    float angle1 = 0.0;
    for(int y=0;y<stacks;y++,angle1+=angle1_inc)
    {
        float angle2 = 0.0;
        float a1_sinf = sinf(angle1);
        float a1_cosf = cosf(angle1);
        for(int x=0;x<slices;x++,angle2+=angle2_inc)
        {
            model->position.push_back(QVector3D(radius*a1_cosf*sinf(angle2),radius*cosf(angle2),radius*a1_sinf*sinf(angle2)));
            model->normal.push_back(QVector3D(a1_cosf*sinf(angle2),cosf(angle2),a1_sinf*sinf(angle2)));
            model->uv_coords.push_back(QVector2D(x/((float)slices),y/((float)stacks)));
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
    for(int y=0;y<stacks-1;y++)
    {
        int x;
        for(x=0;x<slices-1;x++)
        {
            Face f1,f2;
            //Face 1
            model->indices.push_back(y*slices+x);
            f1.v1=y*slices+x;
            model->indices.push_back((y+1)*slices+x);
            f1.v2=(y+1)*slices+x;
            model->indices.push_back(y*slices+(x+1));
            f1.v3=y*slices+(x+1);
            model->faces.push_back(f1);

            //Face 2
            model->indices.push_back((y+1)*slices+x);
            f2.v1=(y+1)*slices+x;
            model->indices.push_back((y+1)*slices+(x+1));
            f2.v2=(y+1)*slices+(x+1);
            model->indices.push_back(y*slices+(x+1));
            f2.v3=y*slices+(x+1);
            model->faces.push_back(f2);
        }
        Face f1,f2;

        //Face 1
        model->indices.push_back(y*slices+x);
        f1.v1=y*slices+x;
        model->indices.push_back((y+1)*slices+x);
        f1.v2=(y+1)*slices+x;
        model->indices.push_back(y*slices);
        f1.v3=y*slices;
        model->faces.push_back(f1);

        //Face 2
        model->indices.push_back((y+1)*slices+x);
        f2.v1=(y+1)*slices+x;
        model->indices.push_back((y+1)*slices);
        f2.v2=(y+1)*slices;
        model->indices.push_back(y*slices);
        f2.v3=y*slices;
        model->faces.push_back(f2);

    }
    model->createFacemap();
    model->volume = model->calcVolume();
    model->recalNormals();
    model->createVBO();
    model->createIndex();
    return model;
}

Model* Model::createTorus(float inner,float outer,int stacks,int slices)
{
}
