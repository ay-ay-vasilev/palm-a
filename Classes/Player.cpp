#include "Player.h"
#include "Definitions.h"
#include "GameConstants.h"
#include "SFXController.h"
#include "Util.h"
#include <algorithm>

auto director = cocos2d::Director::getInstance();
Vec2 origin = director->getVisibleOrigin();

Player::~Player()
{
	//CC_SAFE_RELEASE(idleLeftAnimate);
	//CC_SAFE_RELEASE(idleRightAnimate);
	//
	//CC_SAFE_RELEASE(runLeftAnimate);
	//CC_SAFE_RELEASE(runRightAnimate);

	//CC_SAFE_RELEASE(jumpLeftAnimate);
	//CC_SAFE_RELEASE(jumpRightAnimate);

	//CC_SAFE_RELEASE(fallLeftAnimate);
	//CC_SAFE_RELEASE(fallRightAnimate);

	//CC_SAFE_RELEASE(flyLeftAnimate);
	//CC_SAFE_RELEASE(flyRightAnimate);
}

Player * Player::create(std::string playerType)
{
	Player * player = new Player();
	if(player->init())
	{
		player->autorelease();
		player->initPlayer(playerType);
		return player;
	}

	CC_SAFE_DELETE(player);
	return NULL;
}

void Player::initPlayer(std::string playerType)
{
	GameConstants::loadPlayer(playerType);
	Player::loadAnimations();
	Player::hp = GameConstants::getPlayerStats("START_HP");
	Player::shoots = GameConstants::getPlayerStats("SHOOTS");
	Player::additionalJumps = GameConstants::getPlayerStats("ADDITIONAL_JUMPS");
	Player::dashIFrames = GameConstants::getPlayerStats("DASH_I_FRAMES");
	Player::damageIFrames = GameConstants::getPlayerStats("DMG_I_FRAMES");
	Player::dashes = GameConstants::getPlayerStats("DASHES");
	Player::dashCooldown = GameConstants::getPlayerStats("DASH_COOLDOWN");

	dashInvincibility = false;
	dmgInvincibility = false;

	isOnGround = true;
	moving = false;
	vertForce = 0;
	direction = DIRECTION_LEFT;

	jetpackParticles = ParticleSystemQuad::create(GameConstants::getProjectileAssetPath("PLAYER_PARTICLES"));
	jetpackParticles->setAnchorPoint(Vec2(0.5, 0.5));
	jetpackParticles->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
	
	jetpackParticles->setTotalParticles(100);
	jetpackParticles->setLifeVar(0.1f);
	
	jetpackParticles->setGravity(Vec2(0, -1000));
	this->addChild(jetpackParticles, PARTICLES_LAYER);
	jetpackParticles->stopSystem();
}

void Player::removeDmgInvincibility(float dt)
{
	dmgInvincibility = false;
}

void Player::removeDashInvincibility(float dt)
{
	dashInvincibility = false;
}

void Player::replenishDash(float dt)
{
	dashes = GameConstants::getPlayerStats("DASHES");
}

void Player::giveIFrames(float duration, int type)
{
	if (type == DMG_IFRAMES)
	{
		dmgInvincibility = true;
		this->scheduleOnce(static_cast<cocos2d::SEL_SCHEDULE>(&Player::removeDmgInvincibility), duration);
	}
	if (type == DASH_IFRAMES)
	{
		dashInvincibility = true;
		this->scheduleOnce(static_cast<cocos2d::SEL_SCHEDULE>(&Player::removeDashInvincibility), duration);
	}
}

void Player::dash()
{
	if (dashes > 0)
	{
		auto particles = ParticleSystemQuad::create(GameConstants::getProjectileAssetPath("PLAYER_PARTICLES"));
		particles->setAnchorPoint(Vec2(0.5, 0.5));
		particles->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
		particles->setEmitterMode(ParticleSystem::Mode::RADIUS);
		particles->setTotalParticles(10);
		particles->setLife(0.05);
		//particles->setLifeVar(0.2);
		particles->setDuration(0.1);
		particles->setAngleVar(180);
		particles->setStartRadius(20);
		particles->setEndRadius(60);
		particles->setStartColor(Color4F::WHITE);
		particles->setEndColor(Color4F(0, 180, 180, 255));
		particles->setStartSize(15);
		particles->setEndSize(5);
		this->addChild(particles);

		dashes--;
		SFXController::playerDash();
		vertForce = std::max(0.0f, vertForce);

		auto fadeIn = FadeIn::create(dashIFrames / 2);
		auto fadeOut = FadeOut::create(dashIFrames / 2);
		auto dashSeq = Sequence::create(fadeOut, fadeIn, nullptr);
		giveIFrames(dashIFrames, DASH_IFRAMES);

		this->runAction(dashSeq);
		
		dashed = true;
		this->scheduleOnce(static_cast<cocos2d::SEL_SCHEDULE>(&Player::replenishDash), dashCooldown);
	}
}

void Player::jump()
{
	if (isOnGround) {
		isOnGround = false;
		vertForce = GameConstants::getPlayerStats("JUMP_FORCE");
		playAnimation(jumpLeftAnimate, jumpRightAnimate);
		SFXController::playerJump();
	}
	else if (additionalJumps > 0 && !isOnGround) {
		additionalJumps--;
		vertForce = GameConstants::getPlayerStats("ADDITIONAL_JUMP_FORCE");
		playAnimation(flyLeftAnimate, flyRightAnimate);
		SFXController::playerJetpack();

		jetpackParticles->start();
	}
}

bool Player::jumpKill(float enemyPosY)
{
	if (enemyPosY <= this->getPositionY() && !isOnGround && vertForce < 0) {
		isOnGround = false;
		vertForce = GameConstants::getPlayerStats("JUMP_KILL_FORCE");
		additionalJumps = GameConstants::getPlayerStats("ADDITIONAL_JUMPS");
		replenishDash(0.0);
		playAnimation(jumpLeftAnimate, jumpRightAnimate);
		return true;
	}
	return false;
}

void Player::fall()
{
	playAnimation(fallLeftAnimate, fallRightAnimate);
	jetpackParticles->stopSystem();
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
		if (additionalJumps == GameConstants::getPlayerStats("ADDITIONAL_JUMPS"))
		{
			playAnimation(jumpLeftAnimate, jumpRightAnimate);
		}
		else
		{
			playAnimation(flyLeftAnimate, flyRightAnimate);
		}
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
	auto visibleSize = director->getVisibleSize();

	float speed = GameConstants::getPlayerStats("SPEED");
	float dashSpeed = GameConstants::getPlayerStats("DASH_SPEED");
	float maxAdditionalJumps = GameConstants::getPlayerStats("ADDITIONAL_JUMPS");
	float gravity = GameConstants::getPlayerStats("GRAVITY");
	float maxFallSpeed = GameConstants::getPlayerStats("MAX_FALL_SPEED");
	float maxJumpSpeed = GameConstants::getPlayerStats("MAX_JUMP_SPEED");
	
	float wallDistance = GameConstants::getLevelStats("WALL_DISTANCE");
	float floorHeight = GameConstants::getLevelStats("FLOOR_HEIGHT");


	if (dashed)
	{
		auto newPosX = this->getPositionX();
		if (direction == DIRECTION_LEFT)
		{
			newPosX -= dashSpeed;
		}
		else
		{
			newPosX += dashSpeed;
		}
		this->setPositionX(clampf(newPosX, origin.x + wallDistance, visibleSize.width + origin.x - wallDistance));
		dashed = false;
	}

	if(moving)
	{
		auto newPosX = this->getPositionX();
		if(direction == DIRECTION_LEFT)
		{
			newPosX -= speed;
		}
		else
		{
			newPosX += speed;
		}
		this->setPositionX(clampf(newPosX, origin.x + wallDistance, visibleSize.width + origin.x - wallDistance));
	}
	// remove vertical force if hit ceiling
	if (this->getPositionY() >= visibleSize.height) vertForce = 0;
	// check if player on ground
	if (this->getPositionY() <= origin.y + floorHeight && vertForce <= 0 && !isOnGround)
	{
		isOnGround = true;
		// refill jumps on ground
		additionalJumps = maxAdditionalJumps;

		if (moving) {
			playAnimation(runLeftAnimate, runRightAnimate);
		}
		else {
			playAnimation(idleLeftAnimate, idleRightAnimate);
		}
	}
	// check if player started falling to change animation
	if (vertForce > 0 && vertForce - gravity <= 0 && !isOnGround) fall();
	// apply gravity to vertforce (also set min and max for vert force)
	vertForce = clampf(vertForce - gravity, maxFallSpeed, maxJumpSpeed);
	// change y position using vert force
	auto newPosY = this->getPositionY() + vertForce;
	// apply y position
	this->setPositionY(clampf(newPosY, origin.y + floorHeight, origin.y + visibleSize.height));

}
cocos2d::PhysicsBody* Player::getBody()
{
	auto visibleSize = director->getVisibleSize();
    origin = director->getVisibleOrigin();

	auto physicsBody = PhysicsBody::createBox( Size(this->getContentSize().width/2, this->getContentSize().height/2), PHYSICSBODY_MATERIAL_DEFAULT);

	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask( PLAYER_MASK );
	physicsBody->setContactTestBitmask( true );

	return physicsBody;
}
bool Player::canShoot()
{
	return Player::shoots;
}

int Player::getDirection()
{
	return Player::direction;
}

int Player::getHP()
{
	return Player::hp;
}
bool Player::damageHP(int dmg)
{
	if (dmg > 0 && !dmgInvincibility && !dashInvincibility)
	{
		SFXController::playerDmg();

		auto fadeIn = FadeIn::create(0.1f);
		auto fadeOut = FadeOut::create(0.1f);
		Vector<FiniteTimeAction*> fadeOutIn;
		
		auto redTint = TintTo::create(0.2f, 255, 0, 0);
		auto normalTint = TintTo::create(0.2f, 255, 255, 255);

		for (int i = 0; i < damageIFrames / 0.2f; i++)
		{
			fadeOutIn.pushBack(fadeOut);
			fadeOutIn.pushBack(fadeIn);
		}

		auto damageFade = Sequence::create(fadeOutIn);
		auto damageTint = Sequence::create(redTint, normalTint, nullptr);

		this->runAction(damageFade);
		this->runAction(damageTint);
		giveIFrames(damageIFrames, DMG_IFRAMES);

		Player::hp = Player::hp - dmg;

		return true;
	}	

	return false;
}

// ================================================================== ANIMATION STUFF ==================================================================

void Player::loadAnimations()
{
	auto spriteSize = GameConstants::getPlayerAnimationData("SPRITE_SIZE");
	auto playerSheet = GameConstants::getPlayerAssetPath("SPRITE_SHEET");

	auto spriteCache = SpriteFrameCache::getInstance();
	setContentSize(Size(spriteSize, spriteSize));
	spriteCache->addSpriteFramesWithFile(playerSheet);

	idleLeftAnimate = Util::createPlayerAnimation(spriteCache, "IDLE_NUM_OF_FRAMES", "IDLE_SPEED", "IDLE_LEFT");
	idleRightAnimate = Util::createPlayerAnimation(spriteCache, "IDLE_NUM_OF_FRAMES", "IDLE_SPEED", "IDLE_RIGHT");
	runLeftAnimate = Util::createPlayerAnimation(spriteCache, "RUN_NUM_OF_FRAMES", "RUN_SPEED", "RUN_LEFT");
	runRightAnimate = Util::createPlayerAnimation(spriteCache, "RUN_NUM_OF_FRAMES", "RUN_SPEED", "RUN_RIGHT");
	jumpLeftAnimate = Util::createPlayerAnimation(spriteCache, "JUMP_NUM_OF_FRAMES", "JUMP_SPEED", "JUMP_LEFT");
	jumpRightAnimate = Util::createPlayerAnimation(spriteCache, "JUMP_NUM_OF_FRAMES", "JUMP_SPEED", "JUMP_RIGHT");
	fallLeftAnimate = Util::createPlayerAnimation(spriteCache, "FALL_NUM_OF_FRAMES", "FALL_SPEED", "FALL_LEFT");
	fallRightAnimate = Util::createPlayerAnimation(spriteCache, "FALL_NUM_OF_FRAMES", "FALL_SPEED", "FALL_RIGHT");
	flyLeftAnimate = Util::createPlayerAnimation(spriteCache, "FLY_NUM_OF_FRAMES", "FLY_SPEED", "FLY_LEFT");
	flyRightAnimate = Util::createPlayerAnimation(spriteCache, "FLY_NUM_OF_FRAMES", "FLY_SPEED", "FLY_RIGHT");

	idleLeftAnimate->retain();
	idleRightAnimate->retain();
	runLeftAnimate->retain();
	runRightAnimate->retain();
	jumpLeftAnimate->retain();
	jumpRightAnimate->retain();
	fallLeftAnimate->retain();
	fallRightAnimate->retain();
	flyLeftAnimate->retain();
	flyRightAnimate->retain();
	
	RepeatForever * startAnimation = RepeatForever::create(idleLeftAnimate);
	startAnimation->setTag(ANIMATION_TAG);

	this->runAction(startAnimation);
}

void Player::playAnimation(Animate* leftAnimation, Animate* rightAnimation)
{
	RepeatForever * newAnimation;
	this->stopAllActionsByTag(ANIMATION_TAG);
	if (direction == DIRECTION_LEFT) {
		newAnimation = RepeatForever::create(leftAnimation);
	}
	else {
		newAnimation = RepeatForever::create(rightAnimation);
	}
	newAnimation->setTag(ANIMATION_TAG);
	this->runAction(newAnimation);

}