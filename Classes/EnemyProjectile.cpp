#include "EnemyProjectile.h"

USING_NS_CC;

EnemyProjectile::EnemyProjectile(void)
{
}
EnemyProjectile::~EnemyProjectile(void)
{
}
EnemyProjectile * EnemyProjectile::create(){
    EnemyProjectile * projectile = new EnemyProjectile();
	if(projectile && projectile->initWithFile("res/projectiles/projectile.png"))
	{
		projectile->autorelease();
		projectile->init();
		return projectile;
	}	

	CC_SAFE_DELETE(projectile);
	return NULL;
}
bool EnemyProjectile::init()
{
	Sprite* model = Sprite::create( "res/projectiles/projectile.png" );
	if( model )
	{
		addChild( model );
		return true;
	}
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
	if (projectile && projectile->initWithFile("res/projectiles/laser.png"))
	{
		projectile->autorelease();
		projectile->init();
		return projectile;
	}

	CC_SAFE_DELETE(projectile);
	return NULL;
}
bool Laser::init()
{
	Sprite* model = Sprite::create("res/projectiles/laser.png");
	if (model)
	{
		addChild(model);
		return true;
	}
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