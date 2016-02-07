#include "abstractscene.h"
#include<QOpenGLShader>

QOpenGLVertexArrayObject* AbstractScene::vao=NULL;
QOpenGLShaderProgram* AbstractScene::shader=NULL;

AbstractScene::AbstractScene(AbstractSolver* solver)
{
    if(vao==NULL)
    {
        vao = new QOpenGLVertexArrayObject();
        vao->create();
        vao->bind();
    }
    if(shader==NULL)
    {
        shader = new QOpenGLShaderProgram();
        if(!prepareShader(shader,"../PBD_CG_Seminar/vert.glsl","../PBD_CG_Seminar/frag.glsl"))
        {
            qDebug()<<"ERROR";
        }
        shader->bind();
    }
    this->solver = solver;
}

AbstractScene::~AbstractScene()
{
    solver->reset();
}

void AbstractScene::resize(float width,float height)
{
    glViewport(0,0,width,height);
    projection.setToIdentity();
    projection.perspective(45.0f,width/height,0.1f,100.0f);
    shader->setUniformValueArray("projection",&projection,1);
}

void AbstractScene::uploadLight(Light& light,int index)
{
    QVector3D pos = light.getPosition();
    QVector3D ambient = light.getAmbient();
    QVector3D diffuse = light.getDiffuse();
    QVector3D specular = light.getSpecular();

    std::string pos_string = QString("light[%0].pos").arg(index).toStdString();
    std::string ambient_string = QString("light[%0].amb").arg(index).toStdString();
    std::string diffuse_string = QString("light[%0].dif").arg(index).toStdString();
    std::string specular_string = QString("light[%0].spec").arg(index).toStdString();

    shader->setUniformValue(pos_string.c_str(),pos);
    shader->setUniformValue(ambient_string.c_str(),ambient);
    shader->setUniformValue(diffuse_string.c_str(),diffuse);
    shader->setUniformValue(specular_string.c_str(),specular);
}

bool AbstractScene::prepareShader(QOpenGLShaderProgram* program,const QString& vertexShaderPath,const QString& fragmentShaderPath)
{
    bool result = program->addShaderFromSourceFile(QOpenGLShader::Vertex,vertexShaderPath);
    if(!result)
    {
        qWarning()<<program->log();
    }
    result = program->addShaderFromSourceFile(QOpenGLShader::Fragment,fragmentShaderPath);
    if(!result)
    {
        qWarning()<<program->log();
    }
    result = program->link();
    if(!result)
    {
        qWarning()<<program->log();
    }
    qDebug()<<program->log();
    return result;
}

