#include <GL/glew.h>
#include "canvas.h"
#include <QDebug>
#include <QGLWidget>
#include <QKeyEvent>
#include <QMatrix3x3>
#include "solver.h"

Canvas::Canvas(QWidget *parent) :
    QGLWidget(parent), vertexBuffer(QOpenGLBuffer::VertexBuffer)
{
    QGLFormat format;
    format.setVersion(3,4);
    format.setProfile(QGLFormat::CoreProfile);
    format.setSampleBuffers(true);
    setFormat(format);
    //camera.strafeZ(100.0);
    solver = new Solver();
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

    //Load Models and create Entitys
    bulletModel = Model::createSphere(2,16,16);
    mesh = Entity(Model::createPlaneXY(4,4,32,32));
    floor = Entity(Model::createPlaneXZ(128,128,8,8));
    QMatrix4x4 floorM;
    floorM.setToIdentity();
    floorM.translate(0,-30,0);
    floor.setMatrix(floorM);
    QMatrix4x4 model;
    model.setToIdentity();
    model.scale(1);
    mesh.setMatrix(model);
    solver->addSoftBody(mesh);
    //solver->addBallonBody(mesh);

    //Init Light
    QVector3D l_pos=QVector3D(10.0,0.0,10.0);
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
    light.beginShadowmap();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    light.endShadowmap();

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    view.setToIdentity();
    view=camera.lookAt();
    QVector3D position = camera.getPosition();

    shader.bind();
    shader.setUniformValue("position",position);
    shader.setUniformValueArray("view",&view,1);

    vao.bind();
    for(QList<Entity>::iterator i = bullets.begin();i!=bullets.end();i++)
    {
        i->draw(shader,view);
    }
    mesh.draw(shader,view);
    floor.draw(shader,view);
}

void Canvas::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_E:
            {
                QVector3D pos = camera.getPosition();
                QVector3D vel = -camera.getViewingNormal();
                Entity e = Entity(bulletModel,QMatrix4x4(),pos,vel);
                bullets.append(e);
            }
            break;
        case Qt::Key_W:
            camera.strafeZ(-1.0);
            break;
        case Qt::Key_S:
            camera.strafeZ(1.0);
            break;
        case Qt::Key_A:
            camera.strafeX(-1.0);
            break;
        case Qt::Key_D:
            camera.strafeX(1.0);
            break;
        case Qt::Key_PageUp:
            camera.strafeY(1.0);
            break;
        case Qt::Key_PageDown:
            camera.strafeY(-1.0);
            break;
        case Qt::Key_Left:
            camera.yaw(1.0);
            break;
        case Qt::Key_Right:
            camera.yaw(-1.0);
            break;
        case Qt::Key_Up:
            camera.roll(1.0);
            break;
        case Qt::Key_Down:
            camera.roll(-1.0);
            break;
    }
}

void Canvas::update()
{
    for(QList<Entity>::iterator i = bullets.begin();i!=bullets.end();i++)
    {
        i->update();
        QVector3D pos = i->getPosition();
        if(pos.x()>128||pos.x()<-128||pos.y()>128||pos.y()<-128||pos.z()>128||pos.z()<-128)
        {
            i = bullets.erase(i);
            if(i==bullets.end())
            {
                break;
            }
        }
    }
    solver->solve();
    updateGL();
}

void Canvas::changeSolverLoops(int num)
{
    solver->setSolverLoops(num);
}

void Canvas::changeStretchStiffness(double val)
{
    solver->setStretchStiffness(val);
}

void Canvas::changeCompressStiffness(double val)
{
    solver->setCompressStiffness(val);
}

void Canvas::changeBendingStifness(double val)
{
    solver->setBendStiffness(val);
}

void Canvas::createCylinder()
{
    mesh.release();
    mesh = Entity(Model::createCylinder(2,16,16));
}

void Canvas::createSphere()
{
    QMatrix4x4 smat;
    smat.translate(0,0,10.0);
    mesh.release();
    //Model *m = new Model();

    //m->load("/home/wladimir/Model/cube.obj");

    //m->load("/home/wladimir/Model/sphere/sphere.obj");

    //m->load("/home/wladimir/Model/Duck/DUCK.3DS");

    //mesh = Entity(m);

    //mesh.release();
    mesh = Entity(Model::createSphere(4,64,64));
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
