#include "CutsceneScene.h"
#include "LevelScene.h"
#include "Definitions.h"
#include "AudioEngine.h"

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
    i = 1;
    AudioEngine::stopAll();
    AudioEngine::end();
    musicID = AudioEngine::play2d("audio/music/cutscene_theme.mp3", true);
    AudioEngine::setVolume(musicID, 0.1);

    MenuItemLabel* skipItem = MenuItemLabel::create(Label::createWithTTF("Skip", "fonts/PixelForce.ttf", 23), CC_CALLBACK_1(Cutscene::GoToLevelScene, this));
    skipItem->setAnchorPoint({ 1, 1 });
    skipItem->setPosition(Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height));
    MenuItemLabel* nextItem = MenuItemLabel::create(Label::createWithTTF("Next", "fonts/PixelForce.ttf", 30), CC_CALLBACK_1(Cutscene::Next, this));
    nextItem->setAnchorPoint({ 1, 0 });
    nextItem->setPosition(Vec2(origin.x + visibleSize.width, origin.y));


    // create menu, it's an autorelease object
    auto menu = Menu::create(skipItem, nextItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    Cutscene::NextCadr(i, 1);
    i++; 

    return true;
}

void Cutscene::GoToLevelScene (cocos2d::Ref* pSender){
    finish();
}

void Cutscene::GoToLevelScene2 (float dt){
    finish();
}

void Cutscene::finish() {
    AudioEngine::stopAll();
    AudioEngine::end();
    auto scene = Level::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

Label* Cutscene::label(int i) {
    char str[200] = { 0 };
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto fontSize = 9 * RESOLUTION_VARIABLE;
    switch (i) {
    case 1:
        sprintf(str, "Legends say, that long ago humans ascended to godhood, shining in the sky\n\nAnd everyone was blessed with music, pouring from the stars");
        break;
    case 2:
        sprintf(str, "But one day, they were punished, their great work destroyed in the ashes.\n\nAnd all the music was gone with them...");
        break;
    case 3:
        sprintf(str, "But somewhere, there is an ancient vault that survived the fire\n\nOur elders believe, that the music of our ancestors will unite the lands");
        break;
    case 4:
        sprintf(str, "Stealing music from gods won't be easy...");
        break;
    case 5:
        sprintf(str, "But I am ready");
        break;
    case 6:
        sprintf(str, "");
        break;
    }
    auto label = Label::createWithTTF(str, "fonts/PixelForce.ttf", fontSize);
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 8));
    label->setOpacity(0);
    return label;
}

Sprite* Cutscene::Cadr(int i){
    char str[200] = {0};
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();

    sprintf(str, "res/cutscene/%i_test.png", i);
    auto cadr = Sprite::create(str);
    cadr->getTexture()->setAliasTexParameters();
    cadr->setScale(1.5*RESOLUTION_VARIABLE);
    cadr->setAnchorPoint({ 0.5, 1 });
    cadr->setPosition(Vec2(visibleSize.width/2 + origin.x, origin.y + visibleSize.height - 10 * RESOLUTION_VARIABLE));
    cadr->setOpacity(0);
    return cadr;
}

Sprite* Cutscene::AnimatedCadr(int i, int numOfFrames) {
    char str[200] = { 0 };

    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto spriteCache = SpriteFrameCache::getInstance();
    sprintf(str, "res/cutscene/%i.plist", i);
    spriteCache->addSpriteFramesWithFile(str);

    auto animatedCadr = Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("1.png"));
    Vector<SpriteFrame*> cadrAnimFrames(numOfFrames);

    for (int j = 1; j <= numOfFrames; j++)
    {
        sprintf(str, "%i.png", j);
        auto frame = spriteCache->getSpriteFrameByName(str);
        frame->getTexture()->setAliasTexParameters();
        cadrAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
    }
    auto cadrAnimation = Animation::createWithSpriteFrames(cadrAnimFrames, 0.1f);
    Animate* cadrAnimate = Animate::create(cadrAnimation);

    animatedCadr->getTexture()->setAliasTexParameters();
    animatedCadr->setScale(1.5 * RESOLUTION_VARIABLE);
    animatedCadr->setAnchorPoint({ 0.5, 1 });
    animatedCadr->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height - 10 * RESOLUTION_VARIABLE));
    animatedCadr->setOpacity(0);
    animatedCadr->runAction(RepeatForever::create(cadrAnimate));
    return animatedCadr;

}


void Cutscene::Next(cocos2d::Ref* pSender) {
    Cutscene::deleteCadr(1, 2);
    if (i > 6) {
        finish();
    }
    else if (i == 6) {
        Cutscene::NextCadr(i, 16);
        i++;
    }
    else{
        Cutscene::NextCadr(i, 1);
        i++;
    }
}

void Cutscene::NextCadr(int i, int numOfFrames) {
    auto fadeIn = FadeIn::create(FADE_LENGTH);
    cocos2d::Sprite* cadr;
    if (numOfFrames > 1) cadr = AnimatedCadr(i, numOfFrames);
    else cadr = Cadr(i);
    auto label = Cutscene::label(i);
    this->addChild(cadr, 1, 2);
    this->addChild(label, 1, 1);
    cadr->runAction(fadeIn);
    label->runAction(fadeIn->clone());
}

void Cutscene::deleteCadr(int tagL, int tagC) {
    auto fadeOut = FadeOut::create(FADE_LENGTH);
    auto callBackLabel = CallFunc::create([this, tagL]() {this->removeChildByTag(tagL, true); });
    auto callBackCadr = CallFunc::create([this, tagC]() {this->removeChildByTag(tagC, true); });
    this->getChildByTag(tagC)->runAction(Sequence::create(fadeOut, callBackCadr, nullptr));
    this->getChildByTag(tagL)->runAction(Sequence::create(fadeOut, callBackLabel, nullptr));
}