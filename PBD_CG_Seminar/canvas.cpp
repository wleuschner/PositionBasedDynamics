#include <GL/glew.h>
#include "canvas.h"
#include <QDebug>
#include <QGLWidget>
#include <QKeyEvent>
#include <glm/gtc/matrix_transform.hpp>

Canvas::Canvas(QWidget *parent) :
    QGLWidget(parent), vertexBuffer(QGLBuffer::VertexBuffer)
{
    QGLFormat format;
    format.setVersion(4,0);
    format.setProfile(QGLFormat::CoreProfile);
    format.setSampleBuffers(true);
    setFormat(format);
}

void Canvas::initializeGL()
{
    QGLFormat format = QGLWidget::format();
    if(!format.sampleBuffers())
    {
        qWarning()<<"Could not enable sample buffers";
    }
    int err = glewInit();
    if(err!=GLEW_OK)
    {
        qWarning()<<"Could not init GLEW";
    }
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearColor(0.0,0.0,0.0,1.0);

    if(!prepareShader("../PBD_CG_Seminar/vert.glsl","../PBD_CG_Seminar/frag.glsl"))
    {
        return;
    }

    vao.create();
    vao.bind();
    model.load("/home/wladimir/Model/Pool/Pool\ Table.3DS");

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

    shader.setAttributeBuffer("velocity",GL_FLOAT,sizeof(float)*19,1,sizeof(Vertex));
    shader.enableAttributeArray("velocity");
    modelview.setToIdentity();

    shader.setUniformValueArray("modelview",&modelview,1);
    connect(&updateTimer,SIGNAL(timeout()),this,SLOT(update()));
    updateTimer.setSingleShot(false);
    updateTimer.setInterval(15);
    updateTimer.start();
}

void Canvas::resizeGL(int w, int h)
{
    float width=w;
    float height=h;
    glViewport(0,0,w,h);
    projection.setToIdentity();
    projection.perspective(45.0f,width/height,0.1f,100.0f);
    shader.setUniformValueArray("projection",&projection,1);
}

void Canvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    modelview.setToIdentity();
    modelview.translate(pos);

    shader.bind();

    shader.setUniformValueArray("modelview",&modelview,1);
    vao.bind();
    //glEnableVertexAttribArrayARB(0);
    model.draw();
    //glDrawArrays(GL_TRIANGLES,0,3);
    //glDisableVertexAttribArrayARB(0);
}

void Canvas::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_W:
            pos += QVector3D(0.0,0.0,-1.0);
            break;
        case Qt::Key_S:
            pos += QVector3D(0.0,0.0,1.0);
            break;
        case Qt::Key_A:
            pos += QVector3D(-1.0,0.0,0.0);
            break;
        case Qt::Key_D:
            pos += QVector3D(1.0,0.0,0.0);
            break;
    }
}

void Canvas::update()
{
    updateGL();
}

bool Canvas::prepareShader(const QString& vertexShaderPath,const QString& fragmentShaderPath)
{
    bool result = shader.addShaderFromSourceFile(QGLShader::Vertex,vertexShaderPath);
    if(!result)
    {
        qWarning()<<shader.log();
    }
    result = shader.addShaderFromSourceFile(QGLShader::Fragment,fragmentShaderPath);
    if(!result)
    {
        qWarning()<<shader.log();
    }
    result = shader.link();
    if(!result)
    {
        qWarning()<<shader.log();
    }
    qDebug()<<shader.log();
    return result;
}

