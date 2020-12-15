#include "Projectiles.h"
#include "Definitions.h"
#include "GameConstants.h"

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
			projectileAnimate = Projectile::createAnimation(spriteCache, "DEFAULT_NUM_OF_FRAMES", "DEFAULT_SPEED", "DEFAULT_SPRITE");
			projectileAnimate->retain(); //Retain to use it later

			model->runAction(RepeatForever::create(projectileAnimate));
			
			auto particles = ParticleSystemQuad::create(GameConstants::getProjectileAssetPath("DEFAULT_PARTICLES"));
			particles->setAnchorPoint(Vec2::ZERO);
			particles->setPosition(Size(GameConstants::getProjectileAnimationData("DEFAULT_SPRITE_SIZE")/2, GameConstants::getProjectileAnimationData("DEFAULT_SPRITE_SIZE")/2));
			particles->setScale(0.3);
			model->addChild(particles, BEHIND);

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

cocos2d::ParticleSystemQuad* DefaultProjectile::onDestroyParticles(Vec2 position)
{
	auto particles = ParticleSystemQuad::create(GameConstants::getProjectileAssetPath("DEFAULT_PARTICLES"));
	particles->setAnchorPoint(Vec2::ZERO);
	particles->setPosition(position);
	particles->setLife(0.5);
	particles->setDuration(0.1);
	particles->setSpeed(100);
	particles->setAngleVar(360);
	return particles;
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

			projectileAnimate = Projectile::createAnimation(spriteCache, "LASER_NUM_OF_FRAMES", "LASER_SPEED", "LASER_SPRITE");
			projectileAnimate->retain(); //Retain to use it later
			model->runAction(RepeatForever::create(projectileAnimate));

			auto particles = ParticleSystemQuad::create(GameConstants::getProjectileAssetPath("LASER_PARTICLES"));
			particles->setAnchorPoint(Vec2::ZERO);
			particles->setPosition(Size(GameConstants::getProjectileAnimationData("LASER_SPRITE_SIZE_X") / 3, GameConstants::getProjectileAnimationData("LASER_SPRITE_SIZE_Y") / 2));
			particles->setScale(0.3);
			model->addChild(particles, BEHIND);

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

cocos2d::ParticleSystemQuad* LaserProjectile::onDestroyParticles(Vec2 position)
{
	auto particles = ParticleSystemQuad::create(GameConstants::getProjectileAssetPath("LASER_PARTICLES"));
	particles->setAnchorPoint(Vec2::ZERO);
	particles->setPosition(position);
	particles->setLife(0.2);
	particles->setDuration(0.1);
	particles->setSpeed(200);
	particles->setAngleVar(360);
	particles->setStartColor(Color4F::WHITE);
	return particles;
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
			spriteCache->addSpriteFramesWithFile("res/projectiles/default_projectile.plist");
			projectileAnimate = Projectile::createAnimation(spriteCache, "DEFAULT_NUM_OF_FRAMES", "DEFAULT_SPEED", "DEFAULT_SPRITE");
			projectileAnimate->retain(); //Retain to use it later

			model->runAction(RepeatForever::create(projectileAnimate));

			auto particles = ParticleSystemQuad::create(GameConstants::getProjectileAssetPath("DEFAULT_PARTICLES"));
			particles->setAnchorPoint(Vec2::ZERO);
			particles->setPosition(Size(GameConstants::getProjectileAnimationData("DEFAULT_SPRITE_SIZE") / 2, GameConstants::getProjectileAnimationData("DEFAULT_SPRITE_SIZE") / 2));
			particles->setScale(0.3);
			model->addChild(particles, BEHIND);

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
cocos2d::ParticleSystemQuad* PlayerProjectile::onDestroyParticles(Vec2 position)
{
	auto particles = ParticleSystemQuad::create(GameConstants::getProjectileAssetPath("DEFAULT_PARTICLES"));
	particles->setAnchorPoint(Vec2::ZERO);
	particles->setPosition(position);
	particles->setLife(0.5);
	particles->setDuration(0.1);
	particles->setSpeed(100);
	particles->setAngleVar(360);
	return particles;
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