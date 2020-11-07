#ifndef __CUTSCENE_SCENE_H__
#define __CUTSCENE_SCENE_H__

#include "cocos2d.h"

class Cutscene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

	void GoToLevelScene (cocos2d::Ref* pSender);
	void GoToLevelScene2 (float dt);
	cocos2d::Sprite* nextCadr(int i);

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Cutscene);
};

#endif
