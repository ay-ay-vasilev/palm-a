#include "Background.h"
#include "GameController.h"
#include "GameConstants.h"
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
    spriteCache->addSpriteFramesWithFile(GameConstants::getLevelAssetPath("SPRITE_SHEET"));
    
    Vector<SpriteFrame*> floorAnimFrames(3);
    for (int i = 1; i <= 3; i++)
    {
        sprintf(str, "floor/%i.png", i);
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


    this->addChild(floor, FLOOR_LAYER);


    closeSpeed = GameConstants::getLevelStats("ELEVATION_SPEED") / 1;
    midSpeed = GameConstants::getLevelStats("ELEVATION_SPEED") / 2;
    farSpeed = GameConstants::getLevelStats("ELEVATION_SPEED") / 4;


    paraNodeClose = Background::createParallaxLayer(spriteCache, "CLOSE_SPRITE", 1);
    paraNodeMid = Background::createParallaxLayer(spriteCache, "MID_SPRITE", 2);
    paraNodeFar = Background::createParallaxLayer(spriteCache, "FAR_SPRITE", 4);

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

cocos2d::ParallaxNode* Background::createParallaxLayer(cocos2d::SpriteFrameCache* spriteCache, std::string assetPath, float howFar)
{
    float speed = 100* (float)RESOLUTION_VARIABLE / howFar;

    char str[200] = { 0 };
    auto visibleSize = Director::getInstance()->getVisibleSize();
    std::string spriteName = GameConstants::getLevelAssetPath(assetPath);

    Vector<SpriteFrame*> animFrames(2);
    for (int i = 1; i <= 2; i++)
    {
        sprintf(str, spriteName.c_str(), i);
        auto frame = spriteCache->getSpriteFrameByName(str);
        frame->getTexture()->setAliasTexParameters();
        animFrames.pushBack(spriteCache->getSpriteFrameByName(str));
    }
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.15*howFar);

    Animate* animate1 = Animate::create(animation);
    auto layer1 = Sprite::create();
    layer1->runAction(RepeatForever::create(animate1));
    auto parallax1 = layer1;
    parallax1->getTexture()->setAliasTexParameters();
    parallax1->setScale(RESOLUTION_VARIABLE);
    parallax1->setAnchorPoint(Vec2(0, 0));

    Animate* animate2 = Animate::create(animation);
    auto layer2 = Sprite::create();
    layer2->runAction(RepeatForever::create(animate2));
    auto parallax2 = layer2;
    parallax2->getTexture()->setAliasTexParameters();
    parallax2->setScale(RESOLUTION_VARIABLE);
    parallax2->setAnchorPoint(Vec2(0, 0));
    auto paraNode = ParallaxNode::create();
    paraNode->addChild(parallax1, -1, Vec2(0, speed), Vec2::ZERO);
    paraNode->addChild(parallax2, -1, Vec2(0, speed), Vec2(0, -visibleSize.height));
    paraNode->runAction(MoveTo::create(visibleSize.height / speed, Vec2(0, visibleSize.height / speed)));

    return paraNode;
}