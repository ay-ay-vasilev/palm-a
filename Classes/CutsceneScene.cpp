#include "CutsceneScene.h"
#include "LevelScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* Cutscene::createScene()
{
    auto scene = Scene::create();   
    auto layer = Cutscene::create();
    scene->addChild(layer);
    return scene;
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

    auto fadeIn = FadeIn::create(FADE_LENGTH);
    auto fadeOut = FadeOut::create(FADE_LENGTH);
    cocos2d::DelayTime* delay = cocos2d::DelayTime::create(TRANSITION_TIME);

    auto skipItem = MenuItemImage::create(
                                           "res/cutscene/next-test.png",
                                           "res/cutscene/next-test.png",
                                           CC_CALLBACK_1(Cutscene::GoToLevelScene, this));
    skipItem->setAnchorPoint({1, 0});
    skipItem->setPosition(Vec2(origin.x + visibleSize.width,origin.y));
    skipItem->setScale(2.0); // MAGIC NUMBER FIX LATER

    // create menu, it's an autorelease object
    auto menu = Menu::create(skipItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto funPointer = static_cast<cocos2d::SEL_SCHEDULE>(&Cutscene::GoToLevelScene2);
    
    auto cadrTime = (TRANSITION_TIME + FADE_LENGTH * 2);
    auto totalCutsceneTime = cadrTime * NUMBER_OF_CADRS;
    this->scheduleOnce(funPointer, totalCutsceneTime);

    Vector<Sprite*> cadres(NUMBER_OF_CADRS);
    for (int i = NUMBER_OF_CADRS; i >= 1; i--){
        cadres.pushBack(Cutscene::nextCadr(i));
    }

    auto seq = Sequence::create(fadeIn, delay, fadeOut, nullptr);

    // Maybe do a loop? 
    auto cadr = cadres.back();
    cadres.popBack();
    this->addChild(cadr);
    cadr->runAction(seq);

    auto cadr2 = cadres.back();
    cadres.popBack();
    this->addChild(cadr2);
    cocos2d::DelayTime* delayC = cocos2d::DelayTime::create(cadrTime);
    auto seq2 = Sequence::create(delayC, seq, nullptr);
    cadr2->runAction(seq2);

    auto cadr3 = cadres.back();
    cadres.popBack();
    this->addChild(cadr3);
    auto seq3 = Sequence::create(delayC, delayC, seq, nullptr);
    cadr3->runAction(seq3);

    auto cadr4 = cadres.back();
    cadres.popBack();
    this->addChild(cadr4);
    auto seq4 = Sequence::create(delayC, delayC, delayC, seq, nullptr);
    cadr4->runAction(seq4);

    auto cadr5 = cadres.back();
    cadres.popBack();
    this->addChild(cadr5);
    auto seq5 = Sequence::create(delayC, delayC, delayC, delayC, seq, nullptr);
    cadr5->runAction(seq5);

    auto cadr6 = cadres.back();
    cadres.popBack();
    this->addChild(cadr6);
    auto seq6 = Sequence::create(delayC, delayC, delayC, delayC, delayC, seq, nullptr);
    cadr6->runAction(seq6);
/*  // create touch listener
    auto listener1 = EventListenerTouchOneByOne::create();
    // trigger when you push down
    listener1->onTouchBegan = [director](Touch* touch, Event* event) mutable {
        return true; // if you are consuming it
    };

    // Add listener
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, menu);
*/
    return true;
}

void Cutscene::GoToLevelScene (cocos2d::Ref* pSender){
    auto scene = Level::createScene();   
    Director::getInstance( )->replaceScene( TransitionFade::create(TRANSITION_TIME, scene ) );
}

void Cutscene::GoToLevelScene2 (float dt){
    auto scene = Level::createScene();   
    Director::getInstance( )->replaceScene( TransitionFade::create(TRANSITION_TIME, scene ) );
}

Sprite* Cutscene::nextCadr(int i){
    char str[200] = {0};
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();

    sprintf(str, "res/cutscene/%i_test.png", i);
    auto cadr = Sprite::create(str);
    cadr->getTexture()->setAliasTexParameters();
    cadr->setScale(4.0);
    cadr->setPosition(Vec2(visibleSize.width/2 + origin.x, origin.y + visibleSize.height/2));
    cadr->setOpacity(0);
    return cadr;
}

