#include "MainMenuScene.h"
#include "RecordsScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* RecordsScene::createScene()
{
    return RecordsScene::create();
}

bool RecordsScene::init() {
    if (!Scene::init())
    {
        return false;
    }
    auto director = cocos2d::Director::getInstance();

    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    director->setProjection(Director::Projection::_2D);

    auto Label = Label::createWithTTF("#Some records", "fonts/Light-Pixel-7.ttf", 18 * RESOLUTION_VARIABLE);
    Label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 2 / 3));
    this->addChild(Label);

    auto backLabel = Label::createWithTTF("BACK", "fonts/PixelForce.ttf", 18 * RESOLUTION_VARIABLE);
    MenuItemLabel* backItem = MenuItemLabel::create(backLabel, CC_CALLBACK_1(RecordsScene::GoToMainMenu, this));

    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 3));
    menu->alignItemsVerticallyWithPadding(10 * RESOLUTION_VARIABLE);
    this->addChild(menu, 1);

    return true;
}
void RecordsScene::GoToMainMenu(cocos2d::Ref* pSender) {
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(scene);
}