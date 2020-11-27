#ifndef __RECORDS_SCENE_H__
#define __RECORDS_SCENE_H__

#include "cocos2d.h"

class RecordsScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    void GoToMainMenu(cocos2d::Ref* pSender);

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(RecordsScene);
};

#endif