#include <GL/glew.h>
#include "canvas.h"
#include <QDebug>
#include <QGLWidget>
#include <QKeyEvent>
#include <QMatrix3x3>
#include <glm/gtc/matrix_transform.hpp>

Canvas::Canvas(QWidget *parent) :
    QGLWidget(parent), vertexBuffer(QOpenGLBuffer::VertexBuffer)
{
    QGLFormat format;
    format.setVersion(3,4);
    format.setProfile(QGLFormat::CoreProfile);
    format.setSampleBuffers(true);
    setFormat(format);
    camera.move(QVector3D(0.0,0.0,100.0));
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
    shader.bind();
    //mesh = Entity(Model::createCylinder(2,4,4));
    //createSphere();
    createCylinder();
    //mesh = Entity(Model::createPlaneXY(16,16,32,32));
    //mesh->load("/home/wladimir/Model/triangle.obj");
    QMatrix4x4 model;
    model.setToIdentity();
    mesh.setMatrix(model);
    //sphere.setMatrix(model);
    //mesh = Entity(Model::createPlaneXY(16,16,16,16));
    solver.addModel(mesh);

    QVector3D l_pos=QVector3D(20.0,0.0,0.0);
    QVector3D l_amb=QVector3D(0.2,0.2,0.2);
    QVector3D l_dif=QVector3D(0.4,0.4,0.4);
    QVector3D l_spec = QVector3D(0.8,0.8,0.8);
    light = Light(l_pos,l_amb,l_dif,l_spec);
    resize(800,600);
    uploadLight(light,0);


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
    view.setToIdentity();
    view=camera.lookAt();

    shader.bind();
    shader.setUniformValueArray("view",&view,1);

    vao.bind();
    mesh.draw(shader,view);
    //sphere.draw(shader);
}

void Canvas::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_W:
            camera.move(QVector3D(0.0,0.0,-1.0));
            break;
        case Qt::Key_S:
            camera.move(QVector3D(0.0,0.0,1.0));
            break;
        case Qt::Key_A:
            camera.move(QVector3D(-1.0,0.0,0.0));
            break;
        case Qt::Key_D:
            camera.move(QVector3D(1.0,0.0,0.0));
            break;
        case Qt::Key_PageUp:
            camera.move(QVector3D(0.0,1.0,0.0));
            break;
        case Qt::Key_PageDown:
            camera.move(QVector3D(0.0,-1.0,0.0));
            break;
    }
}

void Canvas::update()
{
    solver.solve();
    updateGL();
}

void Canvas::changeModel(QString file)
{
    mesh.release();
    //mesh = Entity(Model::load(file.toStdString()));
}

void Canvas::createCube()
{
}

void Canvas::createCylinder()
{
    mesh.release();
    mesh = Entity(Model::createCylinder(2,16,16));
}

void Canvas::createSphere()
{
    mesh.release();
    mesh = Entity(Model::createSphere(2,16,16));
}

void Canvas::createTorus()
{
}


bool Canvas::prepareShader(const QString& vertexShaderPath,const QString& fragmentShaderPath)
{
    bool result = shader.addShaderFromSourceFile(QOpenGLShader::Vertex,vertexShaderPath);
    if(!result)
    {
        qWarning()<<shader.log();
    }
    result = shader.addShaderFromSourceFile(QOpenGLShader::Fragment,fragmentShaderPath);
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

void Canvas::uploadLight(Light& light,int index)
{
    QVector3D pos = light.getPosition();
    QVector3D ambient = light.getAmbient();
    QVector3D diffuse = light.getDiffuse();
    QVector3D specular = light.getSpecular();

    std::string pos_string = QString("light[%0].pos").arg(index).toStdString();
    std::string ambient_string = QString("light[%0].amb").arg(index).toStdString();
    std::string diffuse_string = QString("light[%0].dif").arg(index).toStdString();
    std::string specular_string = QString("light[%0].spec").arg(index).toStdString();

    shader.setUniformValue(pos_string.c_str(),pos);
    shader.setUniformValue(ambient_string.c_str(),ambient);
    shader.setUniformValue(diffuse_string.c_str(),diffuse);
    shader.setUniformValue(specular_string.c_str(),specular);
}
