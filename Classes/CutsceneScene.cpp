#include "CutsceneScene.h"
#include "LevelScene.h"

USING_NS_CC;

Scene* Cutscene::createScene()
{
    return Cutscene::create();
}

// show error message
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}

bool Cutscene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    auto director = cocos2d::Director::getInstance();
    
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    director->setProjection(Director::Projection::_2D);


    auto label = Label::createWithTTF("This is a 'cutscene'. Click to start the game.", "fonts/Marker Felt.ttf", 16);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(visibleSize.width / 2, origin.y + 20 ));
        // add the label as a child to this layer
        this->addChild(label, 1);
    }


    // create touch listener
    auto listener1 = EventListenerTouchOneByOne::create();
    // trigger when you push down
    listener1->onTouchBegan = [director](Touch* touch, Event* event) mutable {
        
        auto levelScene = Level::createScene();
        director->replaceScene(levelScene);

        return true; // if you are consuming it
    };

    // Add listener
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, label);


    return true;
}
