#include "Player.h"
#include "Definitions.h"
#include "GameConstants.h"

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
		player->autorelease();
		player->initPlayer();
		return player;
	}

	CC_SAFE_DELETE(player);
	return NULL;
}

void Player::initPlayer()
{
	Player::loadAnimations();


	Player::hp=(float)PLAYER_START_HP;
	moving = false;
	vertForce = 0;
	additionalJumps = (float)PLAYER_ADDITIONAL_JUMPS;
	direction = DIRECTION_LEFT;
	isOnGround = true;
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

// ================================================================== ANIMATION STUFF ==================================================================
Animate* Player::createAnimation(SpriteFrameCache* spriteCache, std::string numOfFrames, std::string animSpeed, std::string assetName)
{
	char str[200] = { 0 };

	auto assetPath = GameConstants::getAssetPath(assetName);
	auto numberOfFrames = GameConstants::getAnimationData(numOfFrames);
	auto animationSpeed = GameConstants::getAnimationData(animSpeed);

	Vector<SpriteFrame*> animFrames(numberOfFrames);


	for (int i = 1; i <= numberOfFrames; i++)
	{
		sprintf(str, assetPath.c_str(), i);
		animFrames.pushBack(spriteCache->getSpriteFrameByName(str));
	}
	auto animation = Animation::createWithSpriteFrames(animFrames, animationSpeed);

	return Animate::create(animation);
}


void Player::loadAnimations()
{
	auto spriteSize = GameConstants::getAnimationData("PLAYER_SPRITE_SIZE");
	auto playerSheet = GameConstants::getAssetPath("PLAYER_SHEET");
	auto spriteCache = SpriteFrameCache::getInstance();

	setContentSize(Size(spriteSize, spriteSize));
	spriteCache->addSpriteFramesWithFile(playerSheet);

	idleLeftAnimate = Player::createAnimation(spriteCache, "PLAYER_ANIM_IDLE_NUM_OF_FRAMES", "PLAYER_ANIM_IDLE_SPEED", "PLAYER_UNARMED_IDLE_LEFT");
	idleRightAnimate = Player::createAnimation(spriteCache, "PLAYER_ANIM_IDLE_NUM_OF_FRAMES", "PLAYER_ANIM_IDLE_SPEED", "PLAYER_UNARMED_IDLE_RIGHT");
	runLeftAnimate = Player::createAnimation(spriteCache, "PLAYER_ANIM_RUN_NUM_OF_FRAMES", "PLAYER_ANIM_RUN_SPEED", "PLAYER_UNARMED_RUN_LEFT");
	runRightAnimate = Player::createAnimation(spriteCache, "PLAYER_ANIM_RUN_NUM_OF_FRAMES", "PLAYER_ANIM_RUN_SPEED", "PLAYER_UNARMED_RUN_RIGHT");
	jumpLeftAnimate = Player::createAnimation(spriteCache, "PLAYER_ANIM_JUMP_NUM_OF_FRAMES", "PLAYER_ANIM_JUMP_SPEED", "PLAYER_UNARMED_JUMP_LEFT");
	jumpRightAnimate = Player::createAnimation(spriteCache, "PLAYER_ANIM_JUMP_NUM_OF_FRAMES", "PLAYER_ANIM_JUMP_SPEED", "PLAYER_UNARMED_JUMP_RIGHT");
	fallLeftAnimate = Player::createAnimation(spriteCache, "PLAYER_ANIM_FALL_NUM_OF_FRAMES", "PLAYER_ANIM_FALL_SPEED", "PLAYER_UNARMED_FALL_LEFT");
	fallRightAnimate = Player::createAnimation(spriteCache, "PLAYER_ANIM_FALL_NUM_OF_FRAMES", "PLAYER_ANIM_FALL_SPEED", "PLAYER_UNARMED_FALL_RIGHT");
	// Retain to use it later
	idleLeftAnimate->retain();
	idleRightAnimate->retain();
	runLeftAnimate->retain();
	runRightAnimate->retain();
	jumpLeftAnimate->retain();
	jumpRightAnimate->retain();
	fallLeftAnimate->retain();
	fallRightAnimate->retain();

	this->runAction(RepeatForever::create(idleLeftAnimate));
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