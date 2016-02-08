#ifndef SCENE_H
#define SCENE_H
#include"abstractscene.h"
#include"graphics/entity.h"
#include"graphics/light.h"
#include"graphics/camera.h"
#include"framework/abstractsolver.h"
#include<QList>

class Scene : public AbstractScene
{
public:
    Scene(AbstractSolver* solver);
    ~Scene();
    void reset();
    void update();
    void draw();
    void processKey(int key);
private:
    Camera camera;
    Light light;

    Model* bulletModel;
    Entity* mesh;
    Entity* floor;
    QList<Entity> bullets;
};

#endif // SCENE_H
