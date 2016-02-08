#ifndef SCENE2_H
#define SCENE2_H
#include"graphics/camera.h"
#include"framework/abstractsolver.h"
#include"abstractscene.h"

class Scene2 : public AbstractScene
{
public:
    Scene2(AbstractSolver* solver);
    ~Scene2();
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

#endif // SCENE2_H
