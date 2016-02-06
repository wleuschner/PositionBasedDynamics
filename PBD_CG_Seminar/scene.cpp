#include "scene.h"

Scene::Scene()
{
}

void Scene::reset()
{
}

void Scene::update()
{
}

void Scene::draw()
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
