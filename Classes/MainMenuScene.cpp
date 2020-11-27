#include "MainMenuScene.h"
#include "CutsceneScene.h"
#include "Definitions.h"
#include <cstring>

USING_NS_CC;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
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

    auto title = Sprite::create("res/ui/main_title_test.png");
    title->getTexture()->setAliasTexParameters();
    title->setScale(3.5*RESOLUTION_VARIABLE);
    title->setAnchorPoint(Vec2(0.5, 0.5));
    title->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height / 4 * 3));
    this->addChild(title, 1);    
    auto startButton = Sprite::create("res/ui/start_button.png");
    startButton->getTexture()->setAliasTexParameters();
    MenuItemSprite* startItem = MenuItemSprite::create(startButton, Sprite::create("res/ui/start_button.png"), Sprite::create("res/ui/start_button.png"), CC_CALLBACK_1(MainMenu::GoToCutscene, this));
    startItem->setAnchorPoint(Vec2(0.5, 0.5));      
    startItem->setScale(2.5*RESOLUTION_VARIABLE);

    auto exitLabel = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 18 * RESOLUTION_VARIABLE);
    MenuItemLabel* exitItem = MenuItemLabel::create(exitLabel, CC_CALLBACK_1(MainMenu::CloseGame, this));

    auto menu = Menu::create(startItem, exitItem, NULL);
    menu->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 3));
    menu->alignItemsVerticallyWithPadding(10*RESOLUTION_VARIABLE);
    this->addChild(menu, 1);

    return true;
}

void MainMenu::GoToCutscene(cocos2d::Ref* pSender) {
    auto scene = Cutscene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void MainMenu::CloseGame(cocos2d::Ref* pSender) {
    Director::getInstance()->end();
}