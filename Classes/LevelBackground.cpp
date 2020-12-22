#include "LevelBackground.h"
#include "GameConstants.h"
#include "Definitions.h"
#include "Util.h"

LevelBackground::~LevelBackground()
{
}

LevelBackground* LevelBackground::create(std::string level)
{
    LevelBackground* background = new LevelBackground();

	if (background->init())
	{
		background->autorelease();
        background->initBackground(level);
		return background;
	}
	CC_SAFE_DELETE(background);
	return NULL;
}

void LevelBackground::initBackground(std::string level)
{
    GameConstants::loadLevel(level);

    this->setContentSize(cocos2d::Director::getInstance()->getVisibleSize());    
    auto spriteCache = cocos2d::SpriteFrameCache::getInstance();
    spriteCache->addSpriteFramesWithFile(GameConstants::getLevelAssetPath("SPRITE_SHEET"));    
    auto floor = LevelBackground::createLayer(spriteCache, "FLOOR_NUM_OF_FRAMES", "FLOOR_SPEED", "FLOOR_SPRITE");
    this->addChild(floor, FLOOR_LAYER);

    closeSpeed = GameConstants::getLevelStats("ELEVATION_SPEED") / 1;
    midSpeed = GameConstants::getLevelStats("ELEVATION_SPEED") / 2;
    farSpeed = GameConstants::getLevelStats("ELEVATION_SPEED") / 4;

    paraNodeClose = LevelBackground::createParallaxLayer(spriteCache, "CLOSE_NUM_OF_FRAMES", "CLOSE_SPEED", "CLOSE_SPRITE", 1);
    paraNodeMid = LevelBackground::createParallaxLayer(spriteCache, "MID_NUM_OF_FRAMES", "MID_SPEED", "MID_SPRITE", 2);
    paraNodeFar = LevelBackground::createParallaxLayer(spriteCache, "FAR_NUM_OF_FRAMES", "FAR_SPEED", "FAR_SPRITE", 4);

    this->addChild(paraNodeClose, BACKGROUND_CLOSE_LAYER);
    this->addChild(paraNodeMid, BACKGROUND_MID_LAYER);
    this->addChild(paraNodeFar, BACKGROUND_FAR_LAYER);    
}

void LevelBackground::update()
{
    if (paraNodeClose->getPosition().y == this->getContentSize().height / closeSpeed) {
        paraNodeClose->setPosition(0, 1.0f / closeSpeed);
        paraNodeClose->runAction(cocos2d::MoveTo::create(this->getContentSize().height / closeSpeed, cocos2d::Vec2(0, this->getContentSize().height / closeSpeed)));
    }
    if (paraNodeMid->getPosition().y == this->getContentSize().height / midSpeed) {
        paraNodeMid->setPosition(0, 1.0f / midSpeed);
        paraNodeMid->runAction(cocos2d::MoveTo::create(this->getContentSize().height / midSpeed, cocos2d::Vec2(0, this->getContentSize().height / midSpeed)));
    }
    if (paraNodeFar->getPosition().y == this->getContentSize().height / farSpeed) {
        paraNodeFar->setPosition(0, 1.0f / farSpeed);
        paraNodeFar->runAction(cocos2d::MoveTo::create(this->getContentSize().height / farSpeed, cocos2d::Vec2(0, this->getContentSize().height / farSpeed)));
    }
}

cocos2d::Sprite* LevelBackground::createLayer(cocos2d::SpriteFrameCache* spriteCache, std::string numOfFrames, std::string animSpeed, std::string assetName)
{
    auto layerAnimate = Util::createLevelAnimation(spriteCache, numOfFrames, animSpeed, assetName);
    layerAnimate->retain();

    auto layer = Sprite::create();
    layer->setScale(GameConstants::resolution);
    layer->setAnchorPoint(cocos2d::Vec2(0, 0));
    layer->runAction(cocos2d::RepeatForever::create(layerAnimate));
    return layer;
}

cocos2d::ParallaxNode* LevelBackground::createParallaxLayer(cocos2d::SpriteFrameCache* spriteCache, std::string numOfFrames, std::string animSpeed, std::string assetName, float howFar)
{
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    float speed = GameConstants::getLevelStats("ELEVATION_SPEED") / howFar;
    
    cocos2d::Animate* animate1 = Util::createLevelAnimation(spriteCache, numOfFrames, animSpeed, assetName);
    animate1->retain();
    auto parallax1 = Sprite::create();
    parallax1->getTexture()->setAliasTexParameters();
    parallax1->setScale(GameConstants::resolution);
    parallax1->setAnchorPoint(cocos2d::Vec2(0, 0));
    parallax1->runAction(cocos2d::RepeatForever::create(animate1));

    cocos2d::Animate* animate2 = Util::createLevelAnimation(spriteCache, numOfFrames, animSpeed, assetName);
    animate2->retain();
    auto parallax2 = Sprite::create();
    parallax2->getTexture()->setAliasTexParameters();
    parallax2->setScale(GameConstants::resolution);
    parallax2->setAnchorPoint(cocos2d::Vec2(0, 0));
    parallax2->runAction(cocos2d::RepeatForever::create(animate2));

    auto paraNode = cocos2d::ParallaxNode::create();
    paraNode->addChild(parallax1, 0, cocos2d::Vec2(0, speed), cocos2d::Vec2::ZERO);
    paraNode->addChild(parallax2, 0, cocos2d::Vec2(0, speed), cocos2d::Vec2(0, -visibleSize.height));
    paraNode->runAction(cocos2d::MoveTo::create(visibleSize.height / speed, cocos2d::Vec2(0, visibleSize.height / speed)));

    return paraNode;
}