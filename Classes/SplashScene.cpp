#include "SplashScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* Splash::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Splash::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// show error message
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
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
    
    auto backgroundSprite = Sprite::create("res/ui/start_button.png");

    backgroundSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, origin.y + visibleSize.height/2));

    this->addChild(backgroundSprite);

    return true;
}

void Splash::GoToMainMenuScene( float dt )
{
    auto scene = MainMenu::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}