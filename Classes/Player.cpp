#include "Player.h"

Player::~Player()
{
	CC_SAFE_RELEASE(idleAnimate);
	CC_SAFE_RELEASE(runAnimate);
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

	Vector<SpriteFrame*> idleAnimFrames(5);
	for(int i = 1; i <= 5; i++) //Iterate for the number of images you have
	{
		sprintf(str, "res/character/idle/sprites/character_unarmed_idle_left_test_%i.png",i);
		auto frame = SpriteFrame::create(str,Rect(0,0,112,112)); //The size of the images in an action should be the same
        frame->getTexture()->setAliasTexParameters();
		idleAnimFrames.pushBack(frame);
	}

	auto idleAnimation = Animation::createWithSpriteFrames(idleAnimFrames, 0.1f);
	idleAnimate = Animate::create(idleAnimation);
	idleAnimate->retain(); //Retain to use it later
	this->runAction(RepeatForever::create(idleAnimate)); //This will be the starting animation

	Vector<SpriteFrame*> runAnimFrames(8);
	for(int i = 1; i <= 8; i++)
	{
		sprintf(str, "res/character/run/sprites/character_unarmed_run_left_test_%i.png",i);
		auto frame = SpriteFrame::create(str,Rect(0,0,112,112));
		frame->getTexture()->setAliasTexParameters();
		runAnimFrames.pushBack(frame);
	}

	auto runAnimation = Animation::createWithSpriteFrames(runAnimFrames, 0.06f);
	runAnimate = Animate::create(runAnimation);
	runAnimate->retain();
}

void Player::run(int directionParam)
{
	this->stopAllActions();
	this->runAction(RepeatForever::create(runAnimate));

	direction = directionParam;
	moving = true;
}

void Player::idle()
{
	moving = false;
	this->stopAllActions();
	this->runAction(RepeatForever::create(idleAnimate));
}

void Player::update()
{
	if(moving) //check if moving
	{
		if(direction == 0) //check if going left
		{
			this->setScaleX(1); //flip
			this->setPositionX(this->getPositionX() - 4);
		}
		else
		{
			this->setScaleX(-1); //flip
			this->setPositionX(this->getPositionX() + 4);
		}
	}
}