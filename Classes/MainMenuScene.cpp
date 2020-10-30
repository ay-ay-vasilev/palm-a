#include "MainMenuScene.h"
#include "CutsceneScene.h"
#include <cstring>

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
        // make the startButton 10 times bigger
        startButton->setScale(10.0);
        // make the center of the startButton the anchor point
        startButton->setAnchorPoint(Vec2(0.5, 0.5));
        // position the startButton on the center of the screen
        startButton->setPosition(Vec2(visibleSize.width/2 + origin.x, origin.y + visibleSize.height/2));
        // add the startButton as a child to this layer
        this->addChild(startButton, 1);
    }

    Vec2 startButtonPosition = startButton->getPosition();
    auto startButtonHeight = startButton->getContentSize().height * 10;
    auto startButtonWidth = startButton->getContentSize().width * 10;
    // button coordinates
    auto startButtonLeft = startButtonPosition.x - startButtonWidth / 2;
    auto startButtonRight = startButtonPosition.x + startButtonWidth / 2;
    auto startButtonTop = startButtonPosition.y - startButtonHeight / 2;
    auto startButtonBottom = startButtonPosition.y + startButtonHeight / 2;

    // create touch listener
    auto listener1 = EventListenerTouchOneByOne::create();
    // trigger when you push down
    listener1->onTouchBegan = [director, visibleSize, startButton,
                               startButtonLeft, startButtonRight,
                               startButtonTop, startButtonBottom](Touch* touch, Event* event) mutable {
        
        if ((touch->getLocation().x > startButtonLeft && touch->getLocation().x < startButtonRight) &&
            (touch->getLocation().y > startButtonTop && touch->getLocation().y < startButtonBottom)
        ) {
            auto cutsceneScene = Cutscene::createScene();
            director->replaceScene(cutsceneScene);
        }
        return true; // if you are consuming it
    };

    // Add listener
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, startButton);


        // DEBUG STUFF
    // =====================================================================================================================
    // auto rectNode = DrawNode::create();
    // Vec2 rectangle[4];
    // rectangle[0] = startButtonPosition + Vec2(-startButtonWidth / 2, -startButtonHeight / 2);
    // rectangle[1] = startButtonPosition + Vec2(startButtonWidth / 2, -startButtonHeight / 2);
    // rectangle[2] = startButtonPosition + Vec2(startButtonWidth / 2, startButtonHeight / 2);
    // rectangle[3] = startButtonPosition + Vec2(-startButtonWidth / 2, startButtonHeight / 2);
    // Color4F color(1, 0, 0, 1);
    // rectNode->drawPolygon(rectangle, 4, color, 1, color);
    // this->addChild(rectNode, 0);

    // auto label = Label::createWithTTF("This is just a test", "fonts/Marker Felt.ttf", 24);
    // if (label == nullptr)
    // {
    //     problemLoading("'fonts/Marker Felt.ttf'");
    // }
    // else
    // {
    //     // position the label on the center of the screen
    //     label->setPosition(startButtonPosition + Vec2(0, 50));
    //     label->setString("Button Size: " + std::to_string(startButtonWidth) + " " + std::to_string(startButtonHeight));
    //     Color3B color(100, 0, 0);
    //     label->setColor(color);
    //     // add the label as a child to this layer
    //     this->addChild(label, 1);
    // }
    // =====================================================================================================================


    return true;
}
