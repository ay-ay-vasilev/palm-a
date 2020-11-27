#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    //void GoToCutscene(cocos2d::Ref* pSender);
    void CloseGame(cocos2d::Ref* pSender);
    void GoToNewGameScene(cocos2d::Ref* pSender);
    void ContinueGame(cocos2d::Ref* pSender);
    void GoToRecordsScene(cocos2d::Ref* pSender);

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
};

#endif
