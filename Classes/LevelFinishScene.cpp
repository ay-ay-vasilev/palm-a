#include "LevelFinishScene.h"
#include "Definitions.h"
#include "MainMenuScene.h"
#include "LevelScene.h"

USING_NS_CC;

Scene* LevelFinish::createScene()
{
    return LevelFinish::create();
}

bool LevelFinish::init() {
    if (!Scene::init())
    {
        return false;
    }

    auto director = cocos2d::Director::getInstance();

    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    director->setProjection(Director::Projection::_2D);

    auto Label = Label::createWithTTF("FINISH", "fonts/Light-Pixel-7.ttf", 18 * (float)RESOLUTION_VARIABLE);
    Label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 2 / 3));
    this->addChild(Label);

    auto continueLabel = Label::createWithTTF("NEXT LEVEL", "fonts/PixelForce.ttf", 18 * (float)RESOLUTION_VARIABLE);
    auto backLabel = Label::createWithTTF("BACK TO MAIN MENU", "fonts/PixelForce.ttf", 18 * (float)RESOLUTION_VARIABLE);
    auto exitLabel = Label::createWithTTF("EXIT", "fonts/PixelForce.ttf", 18 * (float)RESOLUTION_VARIABLE);
    MenuItemLabel* continueItem = MenuItemLabel::create(continueLabel, CC_CALLBACK_1(LevelFinish::GoToNextLevel, this));
    MenuItemLabel* backItem = MenuItemLabel::create(backLabel, CC_CALLBACK_1(LevelFinish::GoToMainMenu, this));
    MenuItemLabel* exitItem = MenuItemLabel::create(exitLabel, CC_CALLBACK_1(LevelFinish::CloseGame, this));
    auto menu = Menu::create(continueItem, backItem, exitItem, NULL);
    menu->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 3));
    menu->alignItemsVerticallyWithPadding(10 * (float)RESOLUTION_VARIABLE);

    GameConstants::initConstants(LEVEL_NEXT);

    this->addChild(menu, 1);

    return true;
}
void LevelFinish::GoToNextLevel(cocos2d::Ref* pSender) {
    auto scene = Level::createScene();
    Director::getInstance()->replaceScene(scene);
}

void LevelFinish::GoToMainMenu(cocos2d::Ref* pSender) {
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(scene);
}
void LevelFinish::CloseGame(cocos2d::Ref* pSender) {
    Director::getInstance()->end();
}