#ifndef SCENE3_H
#define SCENE3_H
#include"abstractscene.h"
#include"graphics/camera.h"
#include"graphics/light.h"

class Scene3 : public AbstractScene
{
public:
    Scene3(AbstractSolver* solver);
    ~Scene3();
    void reset();
    void update();
    void draw();
    void processKey(int key);
private:
    Camera camera;
    Light light;

    Entity* mesh;
    Entity* floor;
};

#endif // SCENE3_H
