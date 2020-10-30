#ifndef __CUTSCENE_SCENE_H__
#define __CUTSCENE_SCENE_H__

#include "cocos2d.h"

class Cutscene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Cutscene);
};

#endif
