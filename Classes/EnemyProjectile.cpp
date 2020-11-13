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
		auto enemyProjectileBody = PhysicsBody::createBox( model->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT );

		//enemyProjectileBody->setCollisionBitmask( 4 );
		//enemyProjectileBody->setContactTestBitmask( true );

		model->setPhysicsBody( enemyProjectileBody );
		EnemyProjectile::setSpeed( Vec2( 120, 0 ) );
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
	//physicsBody->setGravityEnable(false);
	//physicsBody->setDynamic(false);
	physicsBody->setEnabled(false);

	return physicsBody;
}