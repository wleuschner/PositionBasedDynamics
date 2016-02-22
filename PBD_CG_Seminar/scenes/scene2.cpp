#include "scene2.h"

Scene2::Scene2(AbstractSolver* solver) : AbstractScene(solver)
{
    //Load Models and create Entitys
    Material mmat = Material(QVector3D(0.0,0.0,0.0),QVector3D(0.5,0.0,0.0),QVector3D(0.7,0.6,0.6),256);
    Material fmat = Material(QVector3D(0.24725,0.1995,0.0745),QVector3D(0.75164,0.60648,0.22648),QVector3D(0.628281,0.555802,0.366065),128);
    mesh = new Entity(Model::createCylinder(2,32,32));
    mesh->getModel()->setMaterial(mmat);
    floor = new Entity(Model::createPlaneXZ(128,128,8,8),QMatrix4x4(),QVector3D(0,-30,0),QVector3D(0,0,0));
    floor->getModel()->setMaterial(fmat);
    solver->addSoftBody(mesh);
    //solver->addBallonBody(mesh);

    //Init Light
    QVector3D l_pos=QVector3D(10.0,0.0,10.0);
    QVector3D l_amb=QVector3D(0.2,0.2,0.2);
    QVector3D l_dif=QVector3D(0.4,0.4,0.4);
    QVector3D l_spec = QVector3D(0.8,0.8,0.8);
    light = Light(l_pos,l_amb,l_dif,l_spec);
    uploadLight(light,0);

    camera.strafeZ(20.0);
}

Scene2::~Scene2()
{
    mesh->release();
    floor->release();
    mesh->getModel()->release();
    floor->getModel()->release();
    delete mesh;
    delete floor;
}

void Scene2::reset()
{
}

void Scene2::update()
{
    solver->solve();
}

void Scene2::draw()
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

void Scene2::processKey(int key)
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
