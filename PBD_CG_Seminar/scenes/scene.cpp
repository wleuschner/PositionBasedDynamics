#include <GL/glew.h>
#include "scene.h"

Scene::Scene(AbstractSolver* solver) : AbstractScene(solver)
{
    //Load Models and create Entitys
    Material mmat = Material(QVector3D(0.0,0.0,0.0),QVector3D(0.5,0.0,0.0),QVector3D(0.7,0.6,0.6),256);
    Material bmat = Material(QVector3D(0.19225,0.19225,0.19225),QVector3D(0.50754,0.50754,0.50754),QVector3D(0.508273,0.508273,0.508273),128);
    Material fmat = Material(QVector3D(0.24725,0.1995,0.0745),QVector3D(0.75164,0.60648,0.22648),QVector3D(0.628281,0.555802,0.366065),128);
    bulletModel = Model::createSphere(2,64,64);
    bulletModel->setMaterial(bmat);
    mesh = new Entity(Model::createPlaneXY(16,16,32,32));
    mesh->getModel()->setMaterial(mmat);
    floor = new Entity(Model::createPlaneXZ(128,128,8,8),QMatrix4x4(),QVector3D(0,-30,0),QVector3D(0,0,0));
    floor->getModel()->setMaterial(fmat);
    solver->addSoftBody(mesh);
    //solver->addBallonBody(mesh);

    //Init Light
    QVector3D l_pos1=QVector3D(30.0,0.0,10.0);
    QVector3D l_pos2=QVector3D(0.0,0.0,10.0);
    QVector3D l_pos3=QVector3D(-30,0.0,10);
    QVector3D l_amb=QVector3D(0.1,0.1,0.1);
    QVector3D l_dif=QVector3D(0.4,0.4,0.4);
    QVector3D l_spec = QVector3D(0.8,0.8,0.8);

    Light::addLight(new Light(l_pos1,l_amb,l_dif,l_spec));
    Light::addLight(new Light(l_pos2,l_amb,l_dif,l_spec));
    Light::addLight(new Light(l_pos3,l_amb,l_dif,l_spec));

    uploadLights(Light::getLights());

    camera.strafeZ(20.0);
}

Scene::~Scene()
{
    for(QList<Entity>::iterator i = bullets.begin();i!=bullets.end();i++)
    {
        i = bullets.erase(i);
        if(i==bullets.end())
        {
            break;
        }
    }
    Light::clearLights();
    bulletModel->release();
    mesh->release();
    floor->release();
    mesh->getModel()->release();
    floor->getModel()->release();
    delete mesh;
    delete floor;
}

void Scene::reset()
{
}

void Scene::update()
{
    solver->solve(&bullets);
}

void Scene::draw()
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


    for(QList<Entity>::iterator i = bullets.begin();i!=bullets.end();i++)
    {
        i->draw(shader,view);
    }
    mesh->draw(shader,view);
    floor->draw(shader,view);
}

void Scene::processKey(int key)
{
    switch(key)
    {
        case Qt::Key_E:
            {
                QVector3D pos = camera.getPosition();
                QVector3D vel = -camera.getViewingNormal()*(1/60.0)*10;
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
