#ifndef ABSTRACTSCENE_H
#define ABSTRACTSCENE_H

class AbstractScene
{
public:
    AbstractScene();
    virtual void reset()=0;
    virtual void update()=0;
    virtual void draw()=0;
};

#endif // ABSTRACTSCENE_H
