#include "SplashScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* Splash::createScene()
{
    auto scene = Scene::create();
    auto layer = Splash::create();
    scene->addChild(layer);
    return scene;
}

bool Splash::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    auto director = cocos2d::Director::getInstance();

    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    
    auto funPointer = static_cast<cocos2d::SEL_SCHEDULE>(&Splash::GoToMainMenuScene);
    
    this->scheduleOnce(funPointer, DISPLAY_TIME_SPLASH_SCENE);
    
    auto backgroundSprite = Sprite::create("res/other/logo_original_test.png");
    backgroundSprite->getTexture()->setAliasTexParameters();
    backgroundSprite->setScale(8.0); // MAGIC NUMBER FIX LATER
    backgroundSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, origin.y + visibleSize.height/2));

    this->addChild(backgroundSprite);

    return true;
}

void Splash::GoToMainMenuScene( float dt )
{
    auto scene = MainMenu::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}