#ifndef __CUTSCENE_SCENE_H__
#define __CUTSCENE_SCENE_H__

#include "cocos2d.h"

class Cutscene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

	void GoToLevelScene (cocos2d::Ref* pSender);
	void GoToLevelScene2 (float dt);
    void Next(cocos2d::Ref* pSender);
    void NextCadr(int i, int numOfFrames);
    void deleteCadr(int tagL, int tagC);
    void finish();
    cocos2d::Label* label(int i);
	cocos2d::Sprite* Cadr(int i);
    cocos2d::Sprite* AnimatedCadr(int i, int numOfFrames);
    int i;
    int musicID;

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Cutscene);
};

#endif