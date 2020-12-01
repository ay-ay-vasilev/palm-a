#include "Definitions.h"
#include "Enemy.h"
#include "GameController.h"
USING_NS_CC;

Enemy::Enemy(){}
Enemy::~Enemy()
{
	CC_SAFE_RELEASE(idleAnimate);
}
Enemy * Enemy::create(){
    Enemy * enemy = new Enemy();
	if(enemy->init())
	{
		enemy->setContentSize(Size(ENEMY_SPRITE_SIZE, ENEMY_SPRITE_SIZE));
		enemy->autorelease();
		enemy->initEnemy();
		return enemy;
	}

	CC_SAFE_DELETE(enemy);
	return NULL;
}

void Enemy::initEnemy(){
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    char str[200] = {0};

	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("res/enemies/enemy_regular.plist");

    Vector<SpriteFrame*> idleAnimFrames(ENEMY_ANIM_IDLE_NUM_OF_FRAMES);
	for(int i = 1; i <= ENEMY_ANIM_IDLE_NUM_OF_FRAMES; i++) //Iterate for the number of images you have
	{
		sprintf(str, "enemy_1_test_%i.png", i);
		idleAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
	}
    auto idleAnimation = Animation::createWithSpriteFrames(idleAnimFrames, ENEMY_ANIM_IDLE_SPEED);
	idleAnimate = Animate::create(idleAnimation);
	idleAnimate->retain(); //Retain to use it later
	this->runAction(RepeatForever::create(idleAnimate));
}
cocos2d::PhysicsBody* Enemy::getBody()
{
	visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	auto physicsBody = PhysicsBody::createBox( this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	
	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask( 2 );
	physicsBody->setContactTestBitmask( true );
	return physicsBody;
}
void Enemy::setSpawnPoint(int _spawnPoint)
{
	Enemy::spawnPoint = _spawnPoint;
}
int Enemy::getSpawnPoint()
{
	return Enemy::spawnPoint;
}
//=======================================
EnemyType2::EnemyType2() {}
EnemyType2::~EnemyType2()
{
	CC_SAFE_RELEASE(idleAnimate_2);
}
EnemyType2* EnemyType2::create()
{
	EnemyType2* enemy = new EnemyType2();
	if (enemy->init())
	{
		enemy->setContentSize(Size(ENEMY_SPRITE_SIZE, ENEMY_SPRITE_SIZE));
		enemy->autorelease();
		enemy->initEnemy();
		return enemy;
	}

	CC_SAFE_DELETE(enemy);
	return NULL;
}
void EnemyType2::initEnemy()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	char str[200] = { 0 };

	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("res/enemies/enemy_variant.plist");

	Vector<SpriteFrame*> idleAnimFrames(ENEMY_ANIM_IDLE_NUM_OF_FRAMES);
	for (int i = 1; i <= ENEMY_ANIM_IDLE_NUM_OF_FRAMES; i++) //Iterate for the number of images you have
	{
		sprintf(str, "enemy_2_test_%i.png", i);
		idleAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
	}
	auto idleAnimation = Animation::createWithSpriteFrames(idleAnimFrames, ENEMY_ANIM_IDLE_SPEED);
	idleAnimate_2 = Animate::create(idleAnimation);
	idleAnimate_2->retain(); //Retain to use it later
	this->runAction(RepeatForever::create(idleAnimate_2));
}
cocos2d::PhysicsBody* EnemyType2::getBody()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	auto physicsBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);

	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(5);
	physicsBody->setContactTestBitmask(true);
	return physicsBody;
}
void EnemyType2::setSpawnPoint(int _spawnPoint)
{
	EnemyType2::spawnPoint = _spawnPoint;
}
int EnemyType2::getSpawnPoint()
{
	return EnemyType2::spawnPoint;
}