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
    glClearColor(0.0,0.0,0.0,1.0);
    if(!prepareShader("../PBD_CG_Seminar/vert.glsl","../PBD_CG_Seminar/frag.glsl"))
    {
        return;
    }
    float points[] = { -0.5f,-0.5f,-2.0f,1.0f,
                       0.5f,-0.5f,-2.0f,1.0f,
                       0.0f,0.5f,-2.0f,1.0f};
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    vertexBuffer.create();
    vertexBuffer.setUsagePattern(QGLBuffer::StaticDraw);
    if(!vertexBuffer.bind())
    {
        qWarning()<<"Could not bind vertex buffer";
        return;
    }
    vertexBuffer.allocate(points,3*4*sizeof(float));
    if(!shader.bind())
    {
        qWarning()<<"Could not bind shader";
        return;
    }
    shader.setAttributeBuffer("vertex",GL_FLOAT,0,4);
    shader.enableAttributeArray("vertex");
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
    glDrawArrays(GL_TRIANGLES,0,3);
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
    modelview.setToIdentity();
    modelview.translate(pos);
    shader.setUniformValueArray("modelview",&modelview,1);
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
    return result;
}

