#include "EnemyProjectile.h"
#include "Definitions.h"
#include "GameConstants.h"

USING_NS_CC;

DefaultProjectile::DefaultProjectile(void)
{
}
DefaultProjectile::~DefaultProjectile(void)
{
}
DefaultProjectile * DefaultProjectile::create(){
	DefaultProjectile * projectile = new DefaultProjectile();
	cocos2d::Animate* projectileAnimate;
	if(projectile)
	{
		projectile->autorelease();
		Sprite* model = Sprite::create();
		if (model)
		{
			model->setAnchorPoint(Vec2(0, 0));
			model->setPosition(0, 0);

			auto spriteCache = SpriteFrameCache::getInstance();
			spriteCache->addSpriteFramesWithFile(GameConstants::getProjectileAssetPath("DEFAULT_SPRITE_SHEET"));
			projectileAnimate = Projectile::createAnimation(spriteCache, "DEFAULT_NUM_OF_FRAMES", "DEFAULT_SPEED", "DEFAULT_SPRITE");
			projectileAnimate->retain(); //Retain to use it later

			model->runAction(RepeatForever::create(projectileAnimate));
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
bool DefaultProjectile::init()
{
	return false;
}
void DefaultProjectile::setTarget( Vec2 target )
{
	DefaultProjectile::target = target;
}
Vec2 DefaultProjectile::getTarget()
{
	return DefaultProjectile::target;
}
void DefaultProjectile::setSpeed( Vec2 speed )
{
	DefaultProjectile::speed = speed;
}
Vec2 DefaultProjectile::getSpeed()
{
	return DefaultProjectile::speed;
}
cocos2d::PhysicsBody* DefaultProjectile::getBody()
{
	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto physicsBody = PhysicsBody::createBox( this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	
	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask( 3 );
	physicsBody->setContactTestBitmask( true );

	return physicsBody;
}
//==================================================
//Laser
LaserProjectile::LaserProjectile(void)
{
}
LaserProjectile::~LaserProjectile(void)
{
}
LaserProjectile* LaserProjectile::create() {
	LaserProjectile* projectile = new LaserProjectile();
	cocos2d::Animate* projectileAnimate;
	if (projectile)
	{
		projectile->autorelease();
		
		Sprite* model = Sprite::create();
		if (model)
		{
			model->setAnchorPoint(Vec2(0, 0));
			model->setPosition(0, 0);

			auto spriteCache = SpriteFrameCache::getInstance();
			spriteCache->addSpriteFramesWithFile(GameConstants::getProjectileAssetPath("LASER_SPRITE_SHEET"));

			projectileAnimate = Projectile::createAnimation(spriteCache, "LASER_NUM_OF_FRAMES", "LASER_SPEED", "LASER_SPRITE");
			projectileAnimate->retain(); //Retain to use it later
			model->runAction(RepeatForever::create(projectileAnimate));
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
bool LaserProjectile::init()
{
	return false;
}
void LaserProjectile::setTarget(Vec2 target)
{
	LaserProjectile::target = target;
}
Vec2 LaserProjectile::getTarget()
{
	return LaserProjectile::target;
}
void LaserProjectile::setSpeed(Vec2 speed)
{
	LaserProjectile::speed = speed;
}
Vec2 LaserProjectile::getSpeed()
{
	return LaserProjectile::speed;
}
cocos2d::PhysicsBody* LaserProjectile::getBody()
{
	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto physicsBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);

	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(4);
	physicsBody->setContactTestBitmask(true);

	return physicsBody;
}
//=========================================
RayProjectile::RayProjectile(void)
{
}
RayProjectile::~RayProjectile(void)
{
}
RayProjectile* RayProjectile::create() {
	RayProjectile* projectile = new RayProjectile();
	cocos2d::Animate* projectileAnimate;
	if (projectile)
	{
		projectile->autorelease();

		Sprite* model = Sprite::create();
		if (model)
		{
			model->setAnchorPoint(Vec2(0, 0));
			model->setPosition(0, 0);

			auto spriteCache = SpriteFrameCache::getInstance();
			spriteCache->addSpriteFramesWithFile(GameConstants::getProjectileAssetPath("RAY_SPRITE_SHEET"));
			
			projectileAnimate = Projectile::createAnimation(spriteCache, "RAY_NUM_OF_FRAMES", "RAY_SPEED", "RAY_SPRITE");
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
bool RayProjectile::init()
{
	return false;
}
void RayProjectile::setTarget(Vec2 target)
{
	RayProjectile::target = target;
}
Vec2 RayProjectile::getTarget()
{
	return RayProjectile::target;
}
cocos2d::PhysicsBody* RayProjectile::getBody()
{
	auto physicsBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);

	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(7);
	physicsBody->setContactTestBitmask(true);

	return physicsBody;
}




cocos2d::Animate* Projectile::createAnimation(cocos2d::SpriteFrameCache* spriteCache, std::string numOfFrames, std::string animSpeed, std::string assetName)
{
	auto assetPath = GameConstants::getProjectileAssetPath(assetName);
	auto numberOfFrames = GameConstants::getProjectileAnimationData(numOfFrames);
	auto animationSpeed = GameConstants::getProjectileAnimationData(animSpeed);

	char str[200] = { 0 };
	Vector<SpriteFrame*> animFrames(numberOfFrames);

	for (int i = 1; i <= numberOfFrames; i++)
	{
		sprintf(str, assetPath.c_str(), i);
		animFrames.pushBack(spriteCache->getSpriteFrameByName(str));
	}
	auto animation = Animation::createWithSpriteFrames(animFrames, animationSpeed);

	return Animate::create(animation);
}