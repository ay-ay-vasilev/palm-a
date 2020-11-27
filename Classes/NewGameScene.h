#pragma once
#ifndef __NEWGAME_SCENE_H__
#define __NEWGAME_SCENE_H__

#include "cocos2d.h"

class NewGame : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    void GoToCutscene(cocos2d::Ref* pSender);
    void GoToMainMenu(cocos2d::Ref* pSender);

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(NewGame);
};

#endif