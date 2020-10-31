#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h"

class Splash : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
private:
    void GoToMainMenuScene( float dt );

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Splash);

};

#endif
