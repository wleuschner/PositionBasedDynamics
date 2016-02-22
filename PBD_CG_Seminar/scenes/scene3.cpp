#include "scene3.h"
#include "graphics/model.h"

Scene3::Scene3(AbstractSolver* solver) : AbstractScene(solver)
{
    Material mmat = Material(QVector3D(0.0,0.0,0.0),QVector3D(0.5,0.0,0.0),QVector3D(0.7,0.6,0.6),256);
    Material fmat = Material(QVector3D(0.24725,0.1995,0.0745),QVector3D(0.75164,0.60648,0.22648),QVector3D(0.628281,0.555802,0.366065),128);
    //Load Models and create Entitys
    Model* model = new Model();
    model->load("/home/wladimir/Model/sphere/sphere.obj");
    QMatrix4x4 mat;
    mat.scale(10);
    model->setMaterial(mmat);
    mesh = new Entity(model);
    //mesh = new Entity(Model::createSphere(2,32,32));
    floor = new Entity(Model::createPlaneXZ(128,128,8,8),QMatrix4x4(),QVector3D(0,-30,0),QVector3D(0,0,0));
    floor->getModel()->setMaterial(fmat);
    solver->addBallonBody(mesh);

    //Init Light
    QVector3D l_pos=QVector3D(10.0,0.0,10.0);
    QVector3D l_amb=QVector3D(0.2,0.2,0.2);
    QVector3D l_dif=QVector3D(0.4,0.4,0.4);
    QVector3D l_spec = QVector3D(0.8,0.8,0.8);
    light = Light(l_pos,l_amb,l_dif,l_spec);
    uploadLight(light,0);

    camera.strafeZ(20.0);
}

Scene3::~Scene3()
{
    mesh->release();
    floor->release();
    mesh->getModel()->release();
    floor->getModel()->release();
    delete mesh;
    delete floor;
}

void Scene3::reset()
{
}

void Scene3::update()
{
    solver->solve();
}

void Scene3::draw()
{
    //Create Shadowmaps
    light.beginShadowmap();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    light.endShadowmap();

    //Draw Scene
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    view=camera.lookAt();
    QVector3D position = camera.getPosition();
    //vao->bind();

    shader->bind();
    shader->setUniformValue("position",position);
    shader->setUniformValueArray("view",&view,1);

    mesh->draw(shader,view);
    floor->draw(shader,view);
}

void Scene3::processKey(int key)
{
    switch(key)
    {
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
