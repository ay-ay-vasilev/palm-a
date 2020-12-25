#include "MainMenuScene.h"
#include "NewGameScene.h"
#include "CutsceneScene.h"
#include "AudioEngine.h"
#include "Definitions.h"
#include "GameConstants.h"

USING_NS_CC;

Scene* NewGame::createScene()
{
    return NewGame::create();
}

bool NewGame::init() {
    if (!Scene::init())
    {
        return false;
    }

    auto director = cocos2d::Director::getInstance();

    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    director->setProjection(Director::Projection::_2D);

    auto easyLabel = Label::createWithTTF("EASY", "fonts/Light-Pixel-7.ttf", 18 * RESOLUTION_VARIABLE);

    auto mediumLabel = Label::createWithTTF("MEDIUM", "fonts/Light-Pixel-7.ttf", 18 * RESOLUTION_VARIABLE);

    auto hardLabel = Label::createWithTTF("HARD", "fonts/Light-Pixel-7.ttf", 18 * RESOLUTION_VARIABLE);


    auto backLabel = Label::createWithTTF("BACK", "fonts/PixelForce.ttf", 18 * RESOLUTION_VARIABLE);
    auto startLabel = Label::createWithTTF("START", "fonts/PixelForce.ttf", 18 * RESOLUTION_VARIABLE);

    MenuItemLabel* backItem = MenuItemLabel::create(backLabel, CC_CALLBACK_1(NewGame::GoToMainMenu, this));
//    MenuItemLabel* startItem = MenuItemLabel::create(startLabel, CC_CALLBACK_1(NewGame::GoToCutscene, this));

    MenuItemLabel* startItemEasy = MenuItemLabel::create(easyLabel, CC_CALLBACK_1(NewGame::GoToCutsceneEasy, this));
    MenuItemLabel* startItemMedium = MenuItemLabel::create(mediumLabel, CC_CALLBACK_1(NewGame::GoToCutsceneMedium, this));
    MenuItemLabel* startItemHard = MenuItemLabel::create(hardLabel, CC_CALLBACK_1(NewGame::GoToCutsceneHard, this));

    startItemEasy->setPosition(Vec2(origin.x + visibleSize.width / 4, origin.y + visibleSize.height * 2 / 3));
    //this->addChild(easyLabel);
    startItemMedium->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 2 / 3));
    //this->addChild(mediumLabel);
    startItemHard->setPosition(Vec2(origin.x + visibleSize.width * 3 / 4, origin.y + visibleSize.height * 2 / 3));
    //this->addChild(hardLabel);

    //auto menu = Menu::create(startItem, backItem, NULL);
    auto menu = Menu::create(startItemEasy, startItemMedium, startItemHard, backItem, NULL);
    menu->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 3));
    menu->alignItemsVerticallyWithPadding(10 * RESOLUTION_VARIABLE);
    this->addChild(menu, 1);

    return true;
}

void NewGame::GoToCutsceneEasy(cocos2d::Ref* pSender) {
    GameConstants::setPlayerType("jetpack");
    GameConstants::setDifficultyModifier(EASY);

    auto scene = Cutscene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void NewGame::GoToCutsceneMedium(cocos2d::Ref* pSender) {
    GameConstants::setPlayerType("jetpack");
    GameConstants::setDifficultyModifier(MEDIUM);

    auto scene = Cutscene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void NewGame::GoToCutsceneHard(cocos2d::Ref* pSender) {
    GameConstants::setPlayerType("jetpack");
    GameConstants::setDifficultyModifier(HARD);

    auto scene = Cutscene::createScene();
    Director::getInstance()->replaceScene(scene);
}


void NewGame::GoToCutscene(cocos2d::Ref* pSender) {
    auto scene = Cutscene::createScene();
    Director::getInstance()->replaceScene(scene);
}


void NewGame::GoToMainMenu(cocos2d::Ref* pSender) {
    AudioEngine::stopAll();
    AudioEngine::end();
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(scene);
}