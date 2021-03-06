#include "Definitions.h"
#include "Enemy.h"
#include "GameController.h"
#include "GameConstants.h"
#include "Util.h"
USING_NS_CC;

void Enemy::setSpawnPoint(float _spawnPoint)
{
	Enemy::spawnPoint = _spawnPoint;
}
float Enemy::getSpawnPoint()
{
	return Enemy::spawnPoint;
}
PhysicsBody* Enemy::getBody()
{
	auto physicsBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);

	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(REGULAR_ENEMY_MASK);
	physicsBody->setContactTestBitmask(true);
	return physicsBody;
}

EnemyType1::EnemyType1() {}
EnemyType1::~EnemyType1()
{
}
EnemyType1* EnemyType1::create() {
	EnemyType1* enemy = new EnemyType1();
	if (enemy)
	{
		enemy->autorelease();
		enemy->model = Sprite::create();
		if (enemy->model) {
			enemy->model->setAnchorPoint(Vec2::ZERO);
			enemy->model->setPosition(Vec2::ZERO);

			EnemyType1::loadAnimations(enemy);

			enemy->setContentSize(Size(GameConstants::getEnemyAnimationData("REGULAR_SPRITE_SIZE"), GameConstants::getEnemyAnimationData("REGULAR_SPRITE_SIZE")));
			enemy->addChild(enemy->model);
		}
		enemy->init();
		return enemy;
	}
	CC_SAFE_RELEASE(enemy->idleAnimateLeft);
	CC_SAFE_RELEASE(enemy->idleAnimateRight);
	CC_SAFE_DELETE(enemy);
	return NULL;
}
void EnemyType1::facePlayer(int dir)
{
	if (dir != direction) {
		model->stopAllActions();
		direction = dir;
		if (dir == DIRECTION_LEFT) {
			model->runAction(RepeatForever::create(idleAnimateLeft));
		}
		else if (dir == DIRECTION_RIGHT) {
			model->runAction(RepeatForever::create(idleAnimateRight));
		}
	}
}

//=======================================
EnemyType2::EnemyType2() {}
EnemyType2::~EnemyType2()
{
}
EnemyType2* EnemyType2::create()
{
	EnemyType2* enemy = new EnemyType2();
	if (enemy)
	{
		enemy->autorelease();
		enemy->model = Sprite::create();
		if (enemy->model) {
			enemy->model->setAnchorPoint(Vec2::ZERO);
			enemy->model->setPosition(Vec2::ZERO);

			EnemyType2::loadAnimations(enemy);

			enemy->setContentSize(Size(GameConstants::getEnemyAnimationData("LASER_SPRITE_SIZE"), GameConstants::getEnemyAnimationData("LASER_SPRITE_SIZE")));
			enemy->addChild(enemy->model);
		}
		enemy->init();
		return enemy;
	}
	CC_SAFE_RELEASE(enemy->idleAnimateLeft);
	CC_SAFE_RELEASE(enemy->idleAnimateRight);
	CC_SAFE_DELETE(enemy);
	return NULL;
}
void EnemyType2::facePlayer(int dir)
{
	if (dir != direction) {
		model->stopAllActions();
		direction = dir;
		if (dir == DIRECTION_LEFT) {
			model->runAction(RepeatForever::create(idleAnimateLeft));
		}
		else if (dir == DIRECTION_RIGHT) {
			model->runAction(RepeatForever::create(idleAnimateRight));
		}
	}
}

//==========================================
EnemyType3::EnemyType3()
{
}
EnemyType3::~EnemyType3()
{
}
EnemyType3* EnemyType3::create()
{
	EnemyType3* enemy = new EnemyType3();
	if (enemy)
	{
		enemy->setContentSize(Size(GameConstants::getEnemyAnimationData("SPRITE_SIZE"), GameConstants::getEnemyAnimationData("SPRITE_SIZE")));
		enemy->autorelease();

		enemy->model = Sprite::create();
		if (enemy->model) {
			enemy->model->setPosition(Vec2::ZERO);

			char str[200] = { 0 };

			EnemyType3::loadAnimations(enemy);

			enemy->addChild(enemy->model);
			enemy->setContentSize(enemy->model->getContentSize());
		}
		Vec2 anchor = Vec2(1, 0.5);
		enemy->setAnchorPoint(anchor);
		enemy->setBoolRotate(true);
		enemy->init();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	CC_SAFE_RELEASE(enemy->idleAnimate);
	return NULL;
}
void EnemyType3::setBoolRotate(bool b)
{
	rotation = b;
}
bool EnemyType3::canRotate()
{
	return rotation;
}
float EnemyType3::getRotationAngle()
{
	return angle;
}
void EnemyType3::setRotationAngle(float _angle)
{
	angle = _angle;
}



//============================================= ANIMATIONS =============================================

void EnemyType1::loadAnimations(EnemyType1* enemy)
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile(GameConstants::getEnemyAssetPath("REGULAR_SPRITE_SHEET"));

	enemy->idleAnimateLeft = Util::createEnemyAnimation(spriteCache, "REGULAR_IDLE_NUM_OF_FRAMES", "REGULAR_IDLE_SPEED", "REGULAR_IDLE_LEFT");
	enemy->idleAnimateRight = Util::createEnemyAnimation(spriteCache, "REGULAR_IDLE_NUM_OF_FRAMES", "REGULAR_IDLE_SPEED", "REGULAR_IDLE_RIGHT");
	enemy->idleAnimateLeft->retain();
	enemy->idleAnimateRight->retain();
	enemy->model->runAction(RepeatForever::create(enemy->idleAnimateLeft));
}

void EnemyType2::loadAnimations(EnemyType2* enemy)
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile(GameConstants::getEnemyAssetPath("LASER_SPRITE_SHEET"));

	enemy->idleAnimateLeft = Util::createEnemyAnimation(spriteCache, "LASER_IDLE_NUM_OF_FRAMES", "LASER_IDLE_SPEED", "LASER_IDLE_LEFT");
	enemy->idleAnimateRight = Util::createEnemyAnimation(spriteCache, "LASER_IDLE_NUM_OF_FRAMES", "LASER_IDLE_SPEED", "LASER_IDLE_RIGHT");
	enemy->idleAnimateLeft->retain();
	enemy->idleAnimateRight->retain();
	enemy->model->runAction(RepeatForever::create(enemy->idleAnimateLeft));
}

void EnemyType3::loadAnimations(EnemyType3* enemy)
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile(GameConstants::getEnemyAssetPath("TURRET_SPRITE_SHEET"));

	enemy->idleAnimate = Util::createEnemyAnimation(spriteCache, "TURRET_IDLE_NUM_OF_FRAMES", "TURRET_IDLE_SPEED", "TURRET_IDLE");
	enemy->idleAnimate->retain();
	enemy->model->runAction(RepeatForever::create(enemy->idleAnimate));
}