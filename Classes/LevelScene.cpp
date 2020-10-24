#include "LevelScene.h"

USING_NS_CC;

Scene* Level::createScene()
{
    return Level::create();
}

// show error message
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}

// on "init" you need to initialize your instance
bool Level::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add player character sprite
    auto sprite = Sprite::create("res/character/idle/test_idle_right.png");
    if (sprite == nullptr)
    {
        problemLoading("'test idle sprite'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    return true;
}