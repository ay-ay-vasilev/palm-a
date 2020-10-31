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

bool Level::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    // important variables
    auto director = cocos2d::Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    // makes the game 2d
    director->setProjection(Director::Projection::_2D);

    // add player character sprite
    auto character = Sprite::create("res/character/idle/test_idle_right.png");

    if (character == nullptr)
    {
        problemLoading("'test idle sprite'");
    }
    else
    {
        // make pixel art not look blurry
        character->getTexture()->setAliasTexParameters();
        // make the character 4 times bigger
        character->setScale(4.0);
        // make the center bottom of the character the anchor point
        character->setAnchorPoint(Vec2(0.5, 0));
        // position the character on the center of the screen
        character->setPosition(Vec2(visibleSize.width/2 + origin.x, origin.y + 20));
        // add the character as a child to this layer
        this->addChild(character, 0);
    }

    auto direction = "right";

    // create touch listener
    auto listener1 = EventListenerTouchOneByOne::create();
    // trigger when you push down
    listener1->onTouchBegan = [visibleSize, character, direction](Touch* touch, Event* event) mutable {
        
        if (touch->getLocation().x > visibleSize.width/2) {
            character->setTexture("res/character/run/test_right.png");
            auto action = RepeatForever::create(MoveBy::create(1, Vec2(200, 0)));
            character->runAction(action);
            direction = "right";
        }
        else {
            character->setTexture("res/character/run/test_left.png");
            auto action = RepeatForever::create(MoveBy::create(1, Vec2(-200, 0)));
            character->runAction(action);
            direction = "left";
        }
        return true; // if you are consuming it
    };


    // REMOVE LATER, THIS IS CLOSE BUTTON =======================================================
    auto closeItem = MenuItemImage::create("res/ui/close-test.png",
                                           "res/ui/close-test.png",
                                        CC_CALLBACK_1(Level::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("res/ui/close-test.png wasn't able to be loaded");
    }
    else
    {
        closeItem->setScale(2.0);
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width;
        float y = origin.y + visibleSize.height - closeItem->getContentSize().height;
        closeItem->setPosition(Vec2(x,y));
    }
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    // ===========================================================================================


    // trigger when you let up
    listener1->onTouchEnded = [character, direction](Touch* touch, Event* event){
        if (strncmp(direction, "left", 4)) {
            character->setTexture("res/character/idle/test_idle_left.png");
        }
        else if (strncmp(direction, "right", 5)) {
            character->setTexture("res/character/idle/test_idle_right.png");
        }
        else {
            character->setTexture("res/character/idle/test_idle_right.png");
        }

        character->stopAllActions();
    };

    // Add listener
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, character);

    return true;
}



void Level::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}