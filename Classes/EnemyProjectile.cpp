#include "EnemyProjectile.h"
#include "Definitions.h"

USING_NS_CC;

EnemyProjectile::EnemyProjectile(void)
{
}
EnemyProjectile::~EnemyProjectile(void)
{
}
EnemyProjectile * EnemyProjectile::create(){
	EnemyProjectile * projectile = new EnemyProjectile();
	cocos2d::Animate* projectileAnimate;
	if(projectile)
	{
		projectile->setContentSize(Size(ENEMY_DEFAULT_PROJECTILE_ANIM_SPRITE_SIZE, ENEMY_DEFAULT_PROJECTILE_ANIM_SPRITE_SIZE));
		projectile->autorelease();
		char str[200] = { 0 };

		auto spriteCache = SpriteFrameCache::getInstance();
		spriteCache->addSpriteFramesWithFile("res/projectiles/default_projectile.plist");
		Vector<SpriteFrame*> projectileAnimFrames(ENEMY_DEFAULT_PROJECTILE_ANIM_NUM_OF_FRAMES);
		
		for (int i = 1; i <= ENEMY_DEFAULT_PROJECTILE_ANIM_NUM_OF_FRAMES; i++) //Iterate for the number of images you have
		{
			sprintf(str, "default%i.png", i);
			projectileAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
		}

		Sprite* model = Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("default1.png"));
		if (model)
		{
			model->setAnchorPoint(Vec2(0, 0));
			model->setPosition(0, 0);

			auto projectileAnimation = Animation::createWithSpriteFrames(projectileAnimFrames, ENEMY_DEFAULT_PROJECTILE_ANIM_SPEED);
			projectileAnimate = Animate::create(projectileAnimation);
			projectileAnimate->retain(); //Retain to use it later
			model->runAction(RepeatForever::create(projectileAnimate));

			projectile->addChild(model);
			projectile->setContentSize(model->getContentSize());
		}

		projectile->init();
		return projectile;
	}	
	CC_SAFE_DELETE(projectile);
	CC_SAFE_RELEASE(projectileAnimate);
	return NULL;
}
bool EnemyProjectile::init()
{
	return false;
}
void EnemyProjectile::setTarget( Vec2 target )
{
	EnemyProjectile::target = target;
}
Vec2 EnemyProjectile::getTarget()
{
	return EnemyProjectile::target;
}
void EnemyProjectile::setSpeed( Vec2 speed )
{
	EnemyProjectile::speed = speed;
}
Vec2 EnemyProjectile::getSpeed()
{
	return EnemyProjectile::speed;
}
cocos2d::PhysicsBody* EnemyProjectile::getBody()
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
Laser::Laser(void)
{
}
Laser::~Laser(void)
{
}
Laser* Laser::create() {
	Laser* projectile = new Laser();
	cocos2d::Animate* projectileAnimate;
	if (projectile)
	{
		projectile->setContentSize(Size(ENEMY_LASER_PROJECTILE_ANIM_SPRITE_SIZE_X, ENEMY_LASER_PROJECTILE_ANIM_SPRITE_SIZE_Y));
		projectile->autorelease();
		char str[200] = { 0 };

		auto spriteCache = SpriteFrameCache::getInstance();
		spriteCache->addSpriteFramesWithFile("res/projectiles/laser_projectile.plist");
		Vector<SpriteFrame*> projectileAnimFrames(ENEMY_LASER_PROJECTILE_ANIM_NUM_OF_FRAMES);

		for (int i = 1; i <= ENEMY_LASER_PROJECTILE_ANIM_NUM_OF_FRAMES; i++) //Iterate for the number of images you have
		{
			sprintf(str, "laser%i.png", i);
			projectileAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
		}

		Sprite* model = Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("laser1.png"));
		if (model)
		{
			model->setAnchorPoint(Vec2(0, 0));
			model->setPosition(0, 0);

			auto projectileAnimation = Animation::createWithSpriteFrames(projectileAnimFrames, ENEMY_LASER_PROJECTILE_ANIM_SPEED);
			projectileAnimate = Animate::create(projectileAnimation);
			projectileAnimate->retain(); //Retain to use it later
			model->runAction(RepeatForever::create(projectileAnimate));

			projectile->addChild(model);
			projectile->setContentSize(model->getContentSize());
		}

		projectile->init();
		return projectile;
	}
	CC_SAFE_DELETE(projectile);
	CC_SAFE_RELEASE(projectileAnimate);
	return NULL;
}
bool Laser::init()
{
	// ANIMATION WILL BE HERE
	return false;
}
void Laser::setTarget(Vec2 target)
{
	Laser::target = target;
}
Vec2 Laser::getTarget()
{
	return Laser::target;
}
void Laser::setSpeed(Vec2 speed)
{
	Laser::speed = speed;
}
Vec2 Laser::getSpeed()
{
	return Laser::speed;
}
cocos2d::PhysicsBody* Laser::getBody()
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
LaserRay::LaserRay(void)
{
}
LaserRay::~LaserRay(void)
{
}
LaserRay* LaserRay::create() {
	LaserRay* projectile = new LaserRay();
	if (projectile)
	{
		projectile->setContentSize(Size(ENEMY_LASER_PROJECTILE_ANIM_SPRITE_SIZE_X, ENEMY_LASER_PROJECTILE_ANIM_SPRITE_SIZE_Y));
		projectile->autorelease();
		
		Sprite* model = Sprite::create("laser_ray.png");
		if (model)
		{
			model->setAnchorPoint(Vec2(0, 0));
			model->setPosition(0, 0);

			
			projectile->addChild(model);
			projectile->setContentSize(model->getContentSize());
		}

		projectile->init();
		return projectile;
	}
	CC_SAFE_DELETE(projectile);
	return NULL;
}
bool LaserRay::init()
{
	// ANIMATION WILL BE HERE
	return false;
}
void LaserRay::setTarget(Vec2 target)
{
	LaserRay::target = target;
}
Vec2 LaserRay::getTarget()
{
	return LaserRay::target;
}
cocos2d::PhysicsBody* LaserRay::getBody()
{
	auto physicsBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);

	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(7);
	physicsBody->setContactTestBitmask(true);

	return physicsBody;
}