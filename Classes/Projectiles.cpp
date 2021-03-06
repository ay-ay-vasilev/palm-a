#include "Projectiles.h"
#include "Definitions.h"
#include "GameConstants.h"
#include "ParticleController.h"
#include "Util.h"

USING_NS_CC;

DefaultProjectile * DefaultProjectile::create(){
	DefaultProjectile * projectile = new DefaultProjectile();
	cocos2d::Animate* projectileAnimate;
	if(projectile)
	{
		projectile->autorelease();
		Sprite* model = Sprite::create();
		model->getTexture()->setAliasTexParameters();
		if (model)
		{
			model->setAnchorPoint(Vec2::ZERO);
			model->setPosition(Vec2::ZERO);

			auto spriteCache = SpriteFrameCache::getInstance();
			spriteCache->addSpriteFramesWithFile(GameConstants::getProjectileAssetPath("DEFAULT_SPRITE_SHEET"));
			projectileAnimate = Util::createProjectileAnimation(spriteCache, "DEFAULT_NUM_OF_FRAMES", "DEFAULT_SPEED", "DEFAULT_SPRITE");
			projectileAnimate->retain(); //Retain to use it later

			model->runAction(RepeatForever::create(projectileAnimate));
			model->addChild(ParticleController::projectileParticles(), BEHIND);

			projectile->addChild(model);
			projectile->setContentSize(Size(GameConstants::getProjectileAnimationData("DEFAULT_SPRITE_SIZE"), GameConstants::getProjectileAnimationData("DEFAULT_SPRITE_SIZE")));
		}

		projectile->init();
		return projectile;
	}	
	CC_SAFE_DELETE(projectile);
	CC_SAFE_RELEASE(projectileAnimate);
	return NULL;
}


//==================================================
//Laser
LaserProjectile* LaserProjectile::create() {
	LaserProjectile* projectile = new LaserProjectile();
	cocos2d::Animate* projectileAnimate;
	if (projectile)
	{
		projectile->autorelease();
		
		Sprite* model = Sprite::create();
		model->getTexture()->setAliasTexParameters();
		if (model)
		{
			model->setAnchorPoint(Vec2::ZERO);
			model->setPosition(Vec2::ZERO);

			auto spriteCache = SpriteFrameCache::getInstance();
			spriteCache->addSpriteFramesWithFile(GameConstants::getProjectileAssetPath("LASER_SPRITE_SHEET"));

			projectileAnimate = Util::createProjectileAnimation(spriteCache, "LASER_NUM_OF_FRAMES", "LASER_SPEED", "LASER_SPRITE");
			projectileAnimate->retain(); //Retain to use it later
			model->runAction(RepeatForever::create(projectileAnimate));

			model->addChild(ParticleController::laserParticles(), BEHIND);

			projectile->addChild(model);
			projectile->setContentSize(Size(GameConstants::getProjectileAnimationData("LASER_SPRITE_SIZE_X"), GameConstants::getProjectileAnimationData("LASER_SPRITE_SIZE_Y")));
		}

		projectile->init();
		return projectile;
	}
	CC_SAFE_DELETE(projectile);
	CC_SAFE_RELEASE(projectileAnimate);
	return NULL;
}

//================================================
PlayerProjectile* PlayerProjectile::create() {
	PlayerProjectile* projectile = new PlayerProjectile();
	cocos2d::Animate* projectileAnimate;
	if (projectile)
	{
		projectile->autorelease();
		Sprite* model = Sprite::create();
		model->getTexture()->setAliasTexParameters();
		if (model)
		{
			model->setAnchorPoint(Vec2::ZERO);
			model->setPosition(Vec2::ZERO);

			auto spriteCache = SpriteFrameCache::getInstance();
			spriteCache->addSpriteFramesWithFile(GameConstants::getProjectileAssetPath("PLAYER_SPRITE_SHEET"));
			projectileAnimate = Util::createProjectileAnimation(spriteCache, "PLAYER_NUM_OF_FRAMES", "PLAYER_SPEED", "PLAYER_SPRITE");
			projectileAnimate->retain(); //Retain to use it later

			model->runAction(RepeatForever::create(projectileAnimate));

			model->addChild(ParticleController::playerProjectileParticles(), BEHIND);

			projectile->addChild(model);
			projectile->setContentSize(Size(GameConstants::getProjectileAnimationData("PLAYER_SPRITE_SIZE"), GameConstants::getProjectileAnimationData("PLAYER_SPRITE_SIZE")));
		}

		projectile->init();
		return projectile;
	}
	CC_SAFE_DELETE(projectile);
	CC_SAFE_RELEASE(projectileAnimate);
	return NULL;
}
//=========================================
RayProjectile* RayProjectile::create() {
	RayProjectile* projectile = new RayProjectile();
	cocos2d::Animate* projectileAnimate;
	if (projectile)
	{
		projectile->autorelease();

		Sprite* model = Sprite::create();
		model->getTexture()->setAliasTexParameters();
		if (model)
		{
			model->setAnchorPoint(Vec2::ZERO);
			model->setPosition(Vec2::ZERO);

			auto spriteCache = SpriteFrameCache::getInstance();
			spriteCache->addSpriteFramesWithFile(GameConstants::getProjectileAssetPath("RAY_SPRITE_SHEET"));
			
			projectileAnimate = Util::createProjectileAnimation(spriteCache, "RAY_NUM_OF_FRAMES", "RAY_SPEED", "RAY_SPRITE");
			projectileAnimate->retain();
			model->runAction(RepeatForever::create(projectileAnimate));

			projectile->addChild(model);
			projectile->setContentSize(Size(GameConstants::getProjectileAnimationData("RAY_SPRITE_SIZE_X"), GameConstants::getProjectileAnimationData("RAY_SPRITE_SIZE_Y")));
		}
		projectile->setAnchorPoint(Vec2(0, 0.5));
		projectile->init();
		return projectile;
	}
	CC_SAFE_DELETE(projectile);
	CC_SAFE_RELEASE(projectileAnimate);
	return NULL;
}

void Projectile::setTarget(Vec2 target)
{
	Projectile::target = target;
}
Vec2 Projectile::getTarget()
{
	return Projectile::target;
}
void Projectile::setSpeed(Vec2 speed)
{
	Projectile::speed = speed;
}
Vec2 Projectile::getSpeed()
{
	return Projectile::speed;
}
cocos2d::PhysicsBody* Projectile::getBody(int maskID)
{
	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto physicsBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);

	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(maskID);
	physicsBody->setContactTestBitmask(true);

	return physicsBody;
}