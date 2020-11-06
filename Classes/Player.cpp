#include "Player.h"

auto director = cocos2d::Director::getInstance();
auto visibleSize = director->getVisibleSize();
Vec2 origin = director->getVisibleOrigin();

Player::~Player()
{
	CC_SAFE_RELEASE(idleLeftAnimate);
	CC_SAFE_RELEASE(runLeftAnimate);

	CC_SAFE_RELEASE(idleRightAnimate);
	CC_SAFE_RELEASE(runRightAnimate);
}

Player * Player::create()
{
	Player * player = new Player();
	if(player && player->initWithFile("res/character/idle/sprites/character_unarmed_idle_left_test_1.png"))
	{
		player->autorelease();
		player->initPlayer();
		return player;
	}

	CC_SAFE_DELETE(player);
	return NULL;
}

void Player::initPlayer()
{
	moving = false;
	char str[200] = {0};

	Vector<SpriteFrame*> idleLeftAnimFrames(5);
	Vector<SpriteFrame*> idleRightAnimFrames(5);
	for(int i = 1; i <= 5; i++) //Iterate for the number of images you have
	{
		sprintf(str, "res/character/idle/sprites/character_unarmed_idle_left_test_%i.png",i);
		auto frameLeft = SpriteFrame::create(str,Rect(0,0,112,112)); //The size of the images in an action should be the same
        frameLeft->getTexture()->setAliasTexParameters();
		idleLeftAnimFrames.pushBack(frameLeft);

		sprintf(str, "res/character/idle/sprites/character_unarmed_idle_right_test_%i.png",i);
		auto frameRight = SpriteFrame::create(str,Rect(0,0,112,112));
        frameRight->getTexture()->setAliasTexParameters();
		idleRightAnimFrames.pushBack(frameRight);
	}
	auto idleLeftAnimation = Animation::createWithSpriteFrames(idleLeftAnimFrames, 0.1f);
	idleLeftAnimate = Animate::create(idleLeftAnimation);
	idleLeftAnimate->retain(); //Retain to use it later
	
	auto idleRightAnimation = Animation::createWithSpriteFrames(idleRightAnimFrames, 0.1f);
	idleRightAnimate = Animate::create(idleRightAnimation);
	idleRightAnimate->retain();
	
	this->runAction(RepeatForever::create(idleLeftAnimate)); //This will be the starting animation

	Vector<SpriteFrame*> runLeftAnimFrames(8);
	Vector<SpriteFrame*> runRightAnimFrames(8);
	
	for(int i = 1; i <= 8; i++)
	{
		sprintf(str, "res/character/run/sprites/character_unarmed_run_left_test_%i.png",i);
		auto frameLeft = SpriteFrame::create(str,Rect(0,0,112,112));
		frameLeft->getTexture()->setAliasTexParameters();
		runLeftAnimFrames.pushBack(frameLeft);

		sprintf(str, "res/character/run/sprites/character_unarmed_run_right_test_%i.png",i);
		auto frameRight = SpriteFrame::create(str,Rect(0,0,112,112));
		frameRight->getTexture()->setAliasTexParameters();
		runRightAnimFrames.pushBack(frameRight);
	}

	auto runLeftAnimation = Animation::createWithSpriteFrames(runLeftAnimFrames, 0.06f);
	runLeftAnimate = Animate::create(runLeftAnimation);
	runLeftAnimate->retain();

	auto runRightAnimation = Animation::createWithSpriteFrames(runRightAnimFrames, 0.06f);
	runRightAnimate = Animate::create(runRightAnimation);
	runRightAnimate->retain();
}

void Player::run(int directionParam)
{
	this->stopAllActions();

	if (directionParam == 0) {
		this->runAction(RepeatForever::create(runLeftAnimate));
	}
	else {
		this->runAction(RepeatForever::create(runRightAnimate));
	}
	
	direction = directionParam;
	moving = true;
}

void Player::idle()
{
	moving = false;
	this->stopAllActions();

	if (direction == 0) {
		this->runAction(RepeatForever::create(idleLeftAnimate));
	}
	else {
		this->runAction(RepeatForever::create(idleRightAnimate));
	}
}

void Player::update()
{
	if(moving) //check if moving
	{
		auto newPosX = this->getPositionX();
		if(direction == 0) //check if going left
		{
			//this->setScaleX(1); //flip
			newPosX -= 4;
		}
		else
		{
			//this->setScaleX(-1); //flip
			newPosX += 4;
		}
		this->setPositionX(clampf(newPosX, origin.x +80, director->getVisibleSize().width + origin.x));
	}
}