#include "GameOverScene.h"
#include "Definitions.h"
#include "MainMenuScene.h"
#include "LevelScene.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
    return GameOver::create();
}

bool GameOver::init() {
    if (!Scene::init())
    {
        return false;
    }

    auto director = cocos2d::Director::getInstance();

    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    director->setProjection(Director::Projection::_2D);

    auto Label = Label::createWithTTF("GAME OVER", "fonts/Light-Pixel-7.ttf", 18 * RESOLUTION_VARIABLE);
    Label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 2 / 3));
    this->addChild(Label);

    auto continueLabel = Label::createWithTTF("RESTART LEVEL", "fonts/PixelForce.ttf", 18 * RESOLUTION_VARIABLE);
    auto backLabel = Label::createWithTTF("BACK TO MAIN MENU", "fonts/PixelForce.ttf", 18 * RESOLUTION_VARIABLE);
    auto exitLabel = Label::createWithTTF("EXIT", "fonts/PixelForce.ttf", 18 * RESOLUTION_VARIABLE);
    MenuItemLabel* continueItem = MenuItemLabel::create(continueLabel, CC_CALLBACK_1(GameOver::RestartLevel, this));
    MenuItemLabel* backItem = MenuItemLabel::create(backLabel, CC_CALLBACK_1(GameOver::GoToMainMenu, this));
    MenuItemLabel* exitItem = MenuItemLabel::create(exitLabel, CC_CALLBACK_1(GameOver::CloseGame, this));
    auto menu = Menu::create(continueItem, backItem, exitItem, NULL);
    menu->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 3));
    menu->alignItemsVerticallyWithPadding(10 * RESOLUTION_VARIABLE);
    this->addChild(menu, 1);

    return true;
}
void GameOver::RestartLevel(cocos2d::Ref* pSender) {
    auto scene = Level::createScene();
    Director::getInstance()->replaceScene(scene);
}

void GameOver::GoToMainMenu(cocos2d::Ref* pSender) {
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(scene);
}
void GameOver::CloseGame(cocos2d::Ref* pSender) {
    Director::getInstance()->end();
}