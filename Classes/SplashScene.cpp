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
    
    auto backgroundSprite = Sprite::create();
    backgroundSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, origin.y + visibleSize.height/2));

    char str[200] = { 0 };
    auto spriteCache = SpriteFrameCache::getInstance();
    spriteCache->addSpriteFramesWithFile("res/logo/logo.plist");
    Vector<SpriteFrame*> logoAnimFrames(LOGO_ANIM_NUM_OF_FRAMES);

    for (int i = 1; i <= LOGO_ANIM_NUM_OF_FRAMES; i++)
    {
        sprintf(str, "logo%i.PNG", i);
        auto frame = spriteCache->getSpriteFrameByName(str);
        frame->getTexture()->setAliasTexParameters();
        logoAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
    }
    auto logoAnimation = Animation::createWithSpriteFrames(logoAnimFrames, LOGO_ANIM_SPEED);
    Animate * logoAnimate = Animate::create(logoAnimation);

    backgroundSprite->setScale(0.75*RESOLUTION_VARIABLE);
    backgroundSprite->runAction(RepeatForever::create(logoAnimate));
    this->addChild(backgroundSprite);

    return true;
}

void Splash::GoToMainMenuScene( float dt )
{
    auto scene = MainMenu::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create(TRANSITION_TIME, scene ) );
}