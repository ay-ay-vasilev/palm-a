#include "MainMenuScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

// show error message
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}

bool MainMenu::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    auto director = cocos2d::Director::getInstance();
    
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    director->setProjection(Director::Projection::_2D);

    // add start button sprite
    auto startButton = Sprite::create("res/ui/start_button.png");

    if (startButton == nullptr)
    {
        problemLoading("'start button sprite'");
    }
    else
    {
        // make pixel art not look blurry
        startButton->getTexture()->setAliasTexParameters();
        // make the startButton 4 times bigger
        startButton->setScale(10.0);
        // make the center bottom of the startButton the anchor point
        startButton->setAnchorPoint(Vec2(0.5, 0));
        // position the startButton on the center of the screen
        startButton->setPosition(Vec2(visibleSize.width/2 + origin.x, origin.y + visibleSize.height/2));
        // add the startButton as a child to this layer
        this->addChild(startButton, 0);
    }

    auto rectNode = DrawNode::create();
    Vec2 rectangle[4];
    rectangle[0] = Vec2(-50, -50);
    rectangle[1] = Vec2(50, -50);
    rectangle[2] = Vec2(50, 50);
    rectangle[3] = Vec2(-50, 50);

    Color4F white(1, 1, 1, 1);
    rectNode->drawPolygon(rectangle, 4, white, 1, white);
    this->addChild(rectNode);


    // create touch listener
    auto listener1 = EventListenerTouchOneByOne::create();
    // trigger when you push down
    listener1->onTouchBegan = [visibleSize, startButton](Touch* touch, Event* event) mutable {
        
        if (touch->getLocation().x > visibleSize.width/2) {
  
        }
        else {
  
        }
        return true; // if you are consuming it
    };

    // Add listener
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, startButton);

    return true;
}
