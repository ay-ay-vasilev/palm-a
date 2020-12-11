#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    void CloseGame(cocos2d::Ref* pSender);
    void GoToNewGameScene(cocos2d::Ref* pSender);
    void ContinueGame(cocos2d::Ref* pSender);
    void GoToRecordsScene(cocos2d::Ref* pSender);
    int musicID;

    virtual bool init();
    CREATE_FUNC(MainMenu);
};

#endif
