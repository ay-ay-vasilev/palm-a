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
    void NextCadr(int i);
    void deleteCadr(int tagL, int tagC);
    cocos2d::Label* label(int i);
    //cocos2d::Vector<cocos2d::Sprite*> cadres;
    //cocos2d::Vector<cocos2d::Label*> labels;
	cocos2d::Sprite* Cadr(int i);
    int i;

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Cutscene);
};

#endif