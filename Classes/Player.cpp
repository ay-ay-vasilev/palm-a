#include "Player.h"
#include "Definitions.h"

auto director = cocos2d::Director::getInstance();
auto visibleSize = director->getVisibleSize();
Vec2 origin = director->getVisibleOrigin();

Player::~Player()
{
	CC_SAFE_RELEASE(idleLeftAnimate);
	CC_SAFE_RELEASE(idleRightAnimate);
	
	CC_SAFE_RELEASE(runLeftAnimate);
	CC_SAFE_RELEASE(runRightAnimate);

	CC_SAFE_RELEASE(jumpLeftAnimate);
	CC_SAFE_RELEASE(jumpRightAnimate);
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
	Player::hp=(float)PLAYER_START_HP;
	moving = false;
	vertForce = 0;
	additionalJumps = (float)PLAYER_ADDITIONAL_JUMPS;
	direction = DIRECTION_LEFT;
	isOnGround = true;
	char str[200] = {0};

	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("res/character/character_sheet.plist");

	Vector<SpriteFrame*> idleLeftAnimFrames(PLAYER_ANIM_IDLE_NUM_OF_FRAMES);
	Vector<SpriteFrame*> idleRightAnimFrames(PLAYER_ANIM_IDLE_NUM_OF_FRAMES);
	Vector<SpriteFrame*> runLeftAnimFrames(PLAYER_ANIM_RUN_NUM_OF_FRAMES);
	Vector<SpriteFrame*> runRightAnimFrames(PLAYER_ANIM_RUN_NUM_OF_FRAMES);
	
	Vector<SpriteFrame*> jumpLeftAnimFrames(PLAYER_ANIM_JUMP_NUM_OF_FRAMES);
	Vector<SpriteFrame*> jumpRightAnimFrames(PLAYER_ANIM_JUMP_NUM_OF_FRAMES);
	Vector<SpriteFrame*> fallLeftAnimFrames(PLAYER_ANIM_FALL_NUM_OF_FRAMES);
	Vector<SpriteFrame*> fallRightAnimFrames(PLAYER_ANIM_FALL_NUM_OF_FRAMES);

	for(int i = 1; i <= PLAYER_ANIM_IDLE_NUM_OF_FRAMES; i++)
	{
		sprintf(str, "character_unarmed_idle_left_%i.png", i);
		idleLeftAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));

		sprintf(str, "character_unarmed_idle_right_%i.png", i);
		idleRightAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
	}

	for (int i = 1; i <= PLAYER_ANIM_RUN_NUM_OF_FRAMES; i++)
	{
		sprintf(str, "character_unarmed_run_left_%i.png", i);
		runLeftAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));

		sprintf(str, "character_unarmed_run_right_%i.png", i);
		runRightAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
	}

	for (int i = 1; i <= PLAYER_ANIM_JUMP_NUM_OF_FRAMES; i++)
	{
		sprintf(str, "character_unarmed_jump_left_%i.png", i);
		jumpLeftAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));

		sprintf(str, "character_unarmed_jump_right_%i.png", i);
		jumpRightAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
	}

	for (int i = 1; i <= PLAYER_ANIM_FALL_NUM_OF_FRAMES; i++)
	{
		sprintf(str, "character_unarmed_fall_left_%i.png", i);
		fallLeftAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));

		sprintf(str, "character_unarmed_fall_right_%i.png", i);
		fallRightAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
	}

	auto idleLeftAnimation = Animation::createWithSpriteFrames(idleLeftAnimFrames, PLAYER_ANIM_IDLE_SPEED);
	auto idleRightAnimation = Animation::createWithSpriteFrames(idleRightAnimFrames, PLAYER_ANIM_IDLE_SPEED);
	auto runLeftAnimation = Animation::createWithSpriteFrames(runLeftAnimFrames, PLAYER_ANIM_RUN_SPEED);
	auto runRightAnimation = Animation::createWithSpriteFrames(runRightAnimFrames, PLAYER_ANIM_RUN_SPEED);
	auto jumpLeftAnimation = Animation::createWithSpriteFrames(jumpLeftAnimFrames, PLAYER_ANIM_JUMP_SPEED);
	auto jumpRightAnimation = Animation::createWithSpriteFrames(jumpRightAnimFrames, PLAYER_ANIM_JUMP_SPEED);
	auto fallLeftAnimation = Animation::createWithSpriteFrames(fallLeftAnimFrames, PLAYER_ANIM_FALL_SPEED);
	auto fallRightAnimation = Animation::createWithSpriteFrames(fallRightAnimFrames, PLAYER_ANIM_FALL_SPEED);
	idleLeftAnimate = Animate::create(idleLeftAnimation);
	idleRightAnimate = Animate::create(idleRightAnimation);
	runLeftAnimate = Animate::create(runLeftAnimation);
	runRightAnimate = Animate::create(runRightAnimation);
	jumpLeftAnimate = Animate::create(jumpLeftAnimation);
	jumpRightAnimate = Animate::create(jumpRightAnimation);
	fallLeftAnimate = Animate::create(fallLeftAnimation);
	fallRightAnimate = Animate::create(fallRightAnimation);

	// Retain to use it later
	idleLeftAnimate->retain(); 	
	idleRightAnimate->retain();
	runLeftAnimate->retain();
	runRightAnimate->retain();
	jumpLeftAnimate->retain();
	jumpRightAnimate->retain();
	fallLeftAnimate->retain();
	fallRightAnimate->retain();

	this->runAction(RepeatForever::create(idleLeftAnimate)); //This will be the starting animation
}

void Player::dash()
{
	vertForce = 0;
	dashed = true;
}

void Player::jump()
{
	if (isOnGround) {
		isOnGround = false;
		vertForce = (float)PLAYER_JUMP_FORCE * RESOLUTION_VARIABLE;
		playAnimation(jumpLeftAnimate, jumpRightAnimate);
	}
	else if (additionalJumps > 0 && !isOnGround) {
		additionalJumps--;
		vertForce = (float)PLAYER_JUMP_FORCE * RESOLUTION_VARIABLE;
		playAnimation(jumpLeftAnimate, jumpRightAnimate);
	}
}

bool Player::jumpKill(float enemyPosY)
{
	if (enemyPosY <= this->getPositionY() && !isOnGround && vertForce < 0) {
		isOnGround = false;
		vertForce = (float)PLAYER_JUMP_FORCE * RESOLUTION_VARIABLE;
		if (PLAYER_REFILL_JUMPS_ON_KILL) additionalJumps = (float)PLAYER_ADDITIONAL_JUMPS;
		playAnimation(jumpLeftAnimate, jumpRightAnimate);
		return true;
	}
	return false;
}

void Player::fall()
{
	playAnimation(fallLeftAnimate, fallRightAnimate);
}

void Player::run(int directionParam)
{
	direction = directionParam;
	moving = true;

	// run animation if character on ground
	if (isOnGround && vertForce <= 0) {
		playAnimation(runLeftAnimate, runRightAnimate);
	}
	// update fall animation if character is in air and falling
	else if (!isOnGround && vertForce <= 0) {
		playAnimation(fallLeftAnimate, fallRightAnimate);
	}
	// update jump animation if character is in air and rising
	else {
		playAnimation(jumpLeftAnimate, jumpRightAnimate);
	}
}

void Player::idle()
{
	moving = false;
	if (isOnGround) playAnimation(idleLeftAnimate, idleRightAnimate);
	else playAnimation(fallLeftAnimate, fallRightAnimate);
}

void Player::update()
{
	if (dashed)
	{
		auto newPosX = this->getPositionX();
		if (direction == DIRECTION_LEFT)
		{
			newPosX -= (float)PLAYER_DASH_SPEED * RESOLUTION_VARIABLE;
		}
		else
		{
			newPosX += (float)PLAYER_DASH_SPEED * RESOLUTION_VARIABLE;
		}
		this->setPositionX(clampf(newPosX, origin.x + (float)LEVEL_WALL_DISTANCE * RESOLUTION_VARIABLE, director->getVisibleSize().width + origin.x - (float)LEVEL_WALL_DISTANCE * RESOLUTION_VARIABLE));
		dashed = false;
	}

	if(moving)
	{
		auto newPosX = this->getPositionX();
		if(direction == DIRECTION_LEFT)
		{
			newPosX -= (float)PLAYER_SPEED * RESOLUTION_VARIABLE;
		}
		else
		{
			newPosX += (float)PLAYER_SPEED * RESOLUTION_VARIABLE;
		}
		this->setPositionX(clampf(newPosX, origin.x + (float)LEVEL_WALL_DISTANCE*RESOLUTION_VARIABLE, director->getVisibleSize().width + origin.x - (float)LEVEL_WALL_DISTANCE * RESOLUTION_VARIABLE));
	}
	// remove vertical force if hit ceiling
	if (this->getPositionY() >= director->getVisibleSize().height) vertForce = 0;
	// check if player on ground
	if (this->getPositionY() <= origin.y + (float)LEVEL_FLOOR_HEIGHT * RESOLUTION_VARIABLE && vertForce <= 0 && !isOnGround)
	{
		isOnGround = true;
		// refill jumps on ground
		additionalJumps = (float)PLAYER_ADDITIONAL_JUMPS;

		if (moving) {
			playAnimation(runLeftAnimate, runRightAnimate);
		}
		else {
			playAnimation(idleLeftAnimate, idleRightAnimate);
		}
	}
	// check if player started falling to change animation
	if (vertForce > 0 && vertForce - (float)PLAYER_GRAVITY * RESOLUTION_VARIABLE <= 0 && !isOnGround) fall();
	// apply gravity to vertforce (also set min and max for vert force)
	vertForce = clampf(vertForce - (float)PLAYER_GRAVITY* RESOLUTION_VARIABLE, (float)PLAYER_MAX_FALL_SPEED * RESOLUTION_VARIABLE, (float)PLAYER_MAX_JUMP_SPEED * RESOLUTION_VARIABLE);
	// change y position using vert force
	auto newPosY = this->getPositionY() + vertForce;
	// apply y position
	this->setPositionY(clampf(newPosY, origin.y + (float)LEVEL_FLOOR_HEIGHT * RESOLUTION_VARIABLE, origin.y + director->getVisibleSize().height));

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

void Player::playAnimation(Animate* leftAnimation, Animate* rightAnimation)
{
	this->stopAllActions();
	if (direction == DIRECTION_LEFT) {
		this->runAction(RepeatForever::create(leftAnimation));
	}
	else {
		this->runAction(RepeatForever::create(rightAnimation));
	}
}