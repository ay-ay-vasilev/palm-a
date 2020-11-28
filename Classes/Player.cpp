#include "Player.h"
#include "Definitions.h"

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
	if(player->init())
	{
		player->setContentSize(Size(PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE));
		player->autorelease();
		player->initPlayer();
		return player;
	}

	CC_SAFE_DELETE(player);
	return NULL;
}

void Player::initPlayer()
{
	Player::hp=PLAYER_START_HP;
	moving = false;
	vertForce = 0;
	char str[200] = {0};

	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("res/character/character_sheet.plist");

	Vector<SpriteFrame*> idleLeftAnimFrames(PLAYER_ANIM_IDLE_NUM_OF_FRAMES);
	Vector<SpriteFrame*> idleRightAnimFrames(PLAYER_ANIM_IDLE_NUM_OF_FRAMES);
	Vector<SpriteFrame*> runLeftAnimFrames(PLAYER_ANIM_RUN_NUM_OF_FRAMES);
	Vector<SpriteFrame*> runRightAnimFrames(PLAYER_ANIM_RUN_NUM_OF_FRAMES);
	
	for(int i = 1; i <= PLAYER_ANIM_IDLE_NUM_OF_FRAMES; i++) //Iterate for the number of images you have
	{
		sprintf(str, "character_unarmed_idle_left_test_%i.png", i);
		idleLeftAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));

		sprintf(str, "character_unarmed_idle_right_test_%i.png", i);
		idleRightAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
	}

	for (int i = 1; i <= PLAYER_ANIM_RUN_NUM_OF_FRAMES; i++)
	{
		sprintf(str, "character_unarmed_run_left_test_%i.png", i);
		runLeftAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));

		sprintf(str, "character_unarmed_run_right_test_%i.png", i);
		runRightAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
	}

	auto idleLeftAnimation = Animation::createWithSpriteFrames(idleLeftAnimFrames, PLAYER_ANIM_IDLE_SPEED);
	auto idleRightAnimation = Animation::createWithSpriteFrames(idleRightAnimFrames, PLAYER_ANIM_IDLE_SPEED);
	auto runLeftAnimation = Animation::createWithSpriteFrames(runLeftAnimFrames, PLAYER_ANIM_RUN_SPEED);
	auto runRightAnimation = Animation::createWithSpriteFrames(runRightAnimFrames, PLAYER_ANIM_RUN_SPEED);
	idleLeftAnimate = Animate::create(idleLeftAnimation);
	idleRightAnimate = Animate::create(idleRightAnimation);
	runLeftAnimate = Animate::create(runLeftAnimation);
	runRightAnimate = Animate::create(runRightAnimation);

	// Retain to use it later
	idleLeftAnimate->retain(); 	
	idleRightAnimate->retain();
	runLeftAnimate->retain();
	runRightAnimate->retain();

	this->runAction(RepeatForever::create(idleLeftAnimate)); //This will be the starting animation
}

void Player::dash()
{
	vertForce = 0;
	dashed = true;
}

void Player::jump()
{
	if (this->getPositionY() <= origin.y + LEVEL_FLOOR_HEIGHT*RESOLUTION_VARIABLE) vertForce = PLAYER_JUMP_FORCE;
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
	if (dashed) {
		auto newPosX = this->getPositionX();
		if (direction == 0) //check if going left
		{
			//this->setScaleX(1); //flip
			newPosX -= PLAYER_DASH_SPEED * RESOLUTION_VARIABLE;
		}
		else
		{
			//this->setScaleX(-1); //flip
			newPosX += PLAYER_DASH_SPEED * RESOLUTION_VARIABLE;
		}
		this->setPositionX(clampf(newPosX, origin.x + LEVEL_WALL_DISTANCE * RESOLUTION_VARIABLE, director->getVisibleSize().width + origin.x - LEVEL_WALL_DISTANCE * RESOLUTION_VARIABLE));
		dashed = false;
	}

	if(moving) //check if moving
	{
		auto newPosX = this->getPositionX();
		if(direction == DIRECTION_LEFT) //check if going left
		{
			//this->setScaleX(1); //flip
			newPosX -= PLAYER_SPEED * RESOLUTION_VARIABLE;
		}
		else
		{
			//this->setScaleX(-1); //flip
			newPosX += PLAYER_SPEED * RESOLUTION_VARIABLE;
		}
		this->setPositionX(clampf(newPosX, origin.x + LEVEL_WALL_DISTANCE*RESOLUTION_VARIABLE, director->getVisibleSize().width + origin.x - LEVEL_WALL_DISTANCE * RESOLUTION_VARIABLE));
	}

	vertForce = clampf(vertForce - PLAYER_GRAVITY, -100, 100);
	auto newPosY = this->getPositionY() + vertForce;
	this->setPositionY(clampf(newPosY, origin.y + LEVEL_FLOOR_HEIGHT * RESOLUTION_VARIABLE, origin.y + director->getVisibleSize().height));

}
cocos2d::PhysicsBody* Player::getBody()
{
	visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	auto physicsBody = PhysicsBody::createBox( Size(this->getContentSize().width/2, this->getContentSize().height/2), PHYSICSBODY_MATERIAL_DEFAULT);

	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask( 1 );
	physicsBody->setContactTestBitmask( true );

	return physicsBody;
}
int Player::getHP()
{
	return Player::hp;
}
void Player::updateHP(int dmg)
{
	Player::hp = Player::hp - dmg;
}