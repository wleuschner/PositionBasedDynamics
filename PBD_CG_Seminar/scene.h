#ifndef SCENE_H
#define SCENE_H
#include"abstractscene.h"

class Scene : public AbstractScene
{
public:
    Scene();
    void reset();
    void update();
    void draw();
private:
};

#endif // SCENE_H
