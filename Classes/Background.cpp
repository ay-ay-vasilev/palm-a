#include "Background.h"
#include "GameController.h"
#include "Definitions.h"

Background* Background::create()
{
	Background* background = new Background();

	if (background->init())
	{
		background->autorelease();
        background->initBackground();
		return background;
	}
	CC_SAFE_RELEASE(background);
	return NULL;
}

void Background::initBackground()
{
    auto director = cocos2d::Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    
    this->setContentSize(visibleSize);
    
    Vec2 origin = director->getVisibleOrigin();

    char str[200] = { 0 };
    auto spriteCache = SpriteFrameCache::getInstance();
    spriteCache->addSpriteFramesWithFile("res/levels/1/background/background.plist");
    
    Vector<SpriteFrame*> floorAnimFrames(3);
    for (int i = 1; i <= 3; i++)
    {
        sprintf(str, "static_level/%i.png", i);
        auto frame = spriteCache->getSpriteFrameByName(str);
        frame->getTexture()->setAliasTexParameters();
        floorAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
    }
    auto floorAnimation = Animation::createWithSpriteFrames(floorAnimFrames, 0.1);
    Animate* floorAnimate = Animate::create(floorAnimation);
    auto floor = Sprite::create();
    floor->getTexture()->setAliasTexParameters();
    floor->setScale(RESOLUTION_VARIABLE);
    floor->setAnchorPoint(Vec2(0, 0));
    floor->setPosition(Vec2(origin.x, origin.y));
    floor->runAction(RepeatForever::create(floorAnimate));

    Vector<SpriteFrame*> closeAnimFrames(2);
    for (int i = 1; i <= 2; i++)
    {
        sprintf(str, "close/%i.png", i);
        auto frame = spriteCache->getSpriteFrameByName(str);
        frame->getTexture()->setAliasTexParameters();
        closeAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
    }
    auto closeAnimation = Animation::createWithSpriteFrames(closeAnimFrames, 0.15);
    Animate* closeAnimate1 = Animate::create(closeAnimation);
    Animate* closeAnimate2 = Animate::create(closeAnimation);
    auto closeLayer1 = Sprite::create();
    auto closeLayer2 = Sprite::create();
    closeLayer1->runAction(RepeatForever::create(closeAnimate1));
    closeLayer2->runAction(RepeatForever::create(closeAnimate2));


    Vector<SpriteFrame*> midAnimFrames(2);
    for (int i = 1; i <= 2; i++)
    {
        sprintf(str, "mid/%i.png", i);
        auto frame = spriteCache->getSpriteFrameByName(str);
        frame->getTexture()->setAliasTexParameters();
        midAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
    }
    auto midAnimation = Animation::createWithSpriteFrames(midAnimFrames, 0.15*2);
    Animate* midAnimate1 = Animate::create(midAnimation);
    Animate* midAnimate2 = Animate::create(midAnimation);
    auto midLayer1 = Sprite::create();
    auto midLayer2 = Sprite::create();
    midLayer1->runAction(RepeatForever::create(midAnimate1));
    midLayer2->runAction(RepeatForever::create(midAnimate2));

    Vector<SpriteFrame*> farAnimFrames(2);
    for (int i = 1; i <= 2; i++)
    {
        sprintf(str, "far/%i.png", i);
        auto frame = spriteCache->getSpriteFrameByName(str);
        frame->getTexture()->setAliasTexParameters();
        farAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
    }
    auto farAnimation = Animation::createWithSpriteFrames(farAnimFrames, 0.15*4);
    Animate* farAnimate1 = Animate::create(farAnimation);
    Animate* farAnimate2 = Animate::create(farAnimation);
    auto farLayer1 = Sprite::create();
    auto farLayer2 = Sprite::create();
    farLayer1->runAction(RepeatForever::create(farAnimate1));
    farLayer2->runAction(RepeatForever::create(farAnimate2));


    //PARALLAX
    closeSpeed = 100 * (float)RESOLUTION_VARIABLE;
    midSpeed = closeSpeed / 2;
    farSpeed = closeSpeed / 4;

    auto parallaxClose1 = closeLayer1;
    auto parallaxClose2 = closeLayer2;
    auto parallaxMid1 = midLayer1;
    auto parallaxMid2 = midLayer2;
    auto parallaxFar1 = farLayer1;
    auto parallaxFar2 = farLayer2;

    parallaxClose1->getTexture()->setAliasTexParameters();
    parallaxClose1->setScale(RESOLUTION_VARIABLE);
    parallaxClose1->setAnchorPoint(Vec2(0, 0));
    parallaxClose2->getTexture()->setAliasTexParameters();
    parallaxClose2->setScale(RESOLUTION_VARIABLE);
    parallaxClose2->setAnchorPoint(Vec2(0, 0));
    parallaxMid1->getTexture()->setAliasTexParameters();
    parallaxMid1->setScale(RESOLUTION_VARIABLE);
    parallaxMid1->setAnchorPoint(Vec2(0, 0));
    parallaxMid2->getTexture()->setAliasTexParameters();
    parallaxMid2->setScale(RESOLUTION_VARIABLE);
    parallaxMid2->setAnchorPoint(Vec2(0, 0));
    parallaxFar1->getTexture()->setAliasTexParameters();
    parallaxFar1->setScale(RESOLUTION_VARIABLE);
    parallaxFar1->setAnchorPoint(Vec2(0, 0));
    parallaxFar2->getTexture()->setAliasTexParameters();
    parallaxFar2->setScale(RESOLUTION_VARIABLE);
    parallaxFar2->setAnchorPoint(Vec2(0, 0));

    paraNodeClose = ParallaxNode::create();
    paraNodeMid = ParallaxNode::create();
    paraNodeFar = ParallaxNode::create();

    paraNodeClose->addChild(parallaxClose1, -1, Vec2(0, closeSpeed), Vec2::ZERO);
    paraNodeClose->addChild(parallaxClose2, -1, Vec2(0, closeSpeed), Vec2(0, -visibleSize.height));
    paraNodeMid->addChild(parallaxMid1, -2, Vec2(0, midSpeed), Vec2::ZERO);
    paraNodeMid->addChild(parallaxMid2, -2, Vec2(0, midSpeed), Vec2(0, -visibleSize.height));
    paraNodeFar->addChild(parallaxFar1, -3, Vec2(0, farSpeed), Vec2::ZERO);
    paraNodeFar->addChild(parallaxFar2, -3, Vec2(0, farSpeed), Vec2(0, -visibleSize.height));

    paraNodeClose->runAction(MoveTo::create(visibleSize.height / closeSpeed, Vec2(0, visibleSize.height / closeSpeed)));
    paraNodeMid->runAction(MoveTo::create(visibleSize.height / midSpeed, Vec2(0, visibleSize.height / midSpeed)));
    paraNodeFar->runAction(MoveTo::create(visibleSize.height / farSpeed, Vec2(0, visibleSize.height / farSpeed)));

    this->addChild(floor, FLOOR_LAYER);
    this->addChild(paraNodeClose, BACKGROUND_CLOSE_LAYER);
    this->addChild(paraNodeMid, BACKGROUND_MID_LAYER);
    this->addChild(paraNodeFar, BACKGROUND_FAR_LAYER);
}

void Background::update()
{
    if (paraNodeClose->getPosition().y == this->getContentSize().height / closeSpeed) {
        paraNodeClose->setPosition(0, 1.0f / closeSpeed);
        paraNodeClose->runAction(MoveTo::create(this->getContentSize().height / closeSpeed, Vec2(0, this->getContentSize().height / closeSpeed)));
    }
    if (paraNodeMid->getPosition().y == this->getContentSize().height / midSpeed) {
        paraNodeMid->setPosition(0, 1.0f / midSpeed);
        paraNodeMid->runAction(MoveTo::create(this->getContentSize().height / midSpeed, Vec2(0, this->getContentSize().height / midSpeed)));
    }
    if (paraNodeFar->getPosition().y == this->getContentSize().height / farSpeed) {
        paraNodeFar->setPosition(0, 1.0f / farSpeed);
        paraNodeFar->runAction(MoveTo::create(this->getContentSize().height / farSpeed, Vec2(0, this->getContentSize().height / farSpeed)));
    }
}