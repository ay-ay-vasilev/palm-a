#include "Definitions.h"
#include "Enemy.h"
#include "GameController.h"
#include "GameConstants.h"
USING_NS_CC;

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
cocos2d::PhysicsBody* EnemyType1::getBody()
{
	auto physicsBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);

	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(REGULAR_ENEMY_MASK);
	physicsBody->setContactTestBitmask(true);
	return physicsBody;
}
void EnemyType1::setSpawnPoint(float _spawnPoint)
{
	EnemyType1::spawnPoint = _spawnPoint;
}
float EnemyType1::getSpawnPoint()
{
	return EnemyType1::spawnPoint;
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
cocos2d::PhysicsBody* EnemyType2::getBody()
{
	auto physicsBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);

	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(LASER_ENEMY_MASK);
	physicsBody->setContactTestBitmask(true);
	return physicsBody;
}
void EnemyType2::setSpawnPoint(float _spawnPoint)
{
	EnemyType2::spawnPoint = _spawnPoint;
}
float EnemyType2::getSpawnPoint()
{
	return EnemyType2::spawnPoint;
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
cocos2d::PhysicsBody* EnemyType3::getBody()
{
	auto physicsBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);

	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(TURRET_ENEMY_MASK);
	physicsBody->setContactTestBitmask(true);
	return physicsBody;
}
void EnemyType3::setSpawnPoint(int _spawnPoint)
{
	EnemyType3::spawnPoint = _spawnPoint;
}
int EnemyType3::getSpawnPoint()
{
	return EnemyType3::spawnPoint;
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
cocos2d::Animate* Enemy::createAnimation(cocos2d::SpriteFrameCache* spriteCache, std::string numOfFrames, std::string animSpeed, std::string assetName)
{
	auto assetPath = GameConstants::getEnemyAssetPath(assetName);
	auto numberOfFrames = GameConstants::getEnemyAnimationData(numOfFrames);
	auto animationSpeed = GameConstants::getEnemyAnimationData(animSpeed);

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

void EnemyType1::loadAnimations(EnemyType1* enemy)
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile(GameConstants::getEnemyAssetPath("REGULAR_SPRITE_SHEET"));

	enemy->idleAnimateLeft = Enemy::createAnimation(spriteCache, "REGULAR_IDLE_NUM_OF_FRAMES", "REGULAR_IDLE_SPEED", "REGULAR_IDLE_LEFT");
	enemy->idleAnimateRight = Enemy::createAnimation(spriteCache, "REGULAR_IDLE_NUM_OF_FRAMES", "REGULAR_IDLE_SPEED", "REGULAR_IDLE_RIGHT");
	enemy->idleAnimateLeft->retain();
	enemy->idleAnimateRight->retain();
	enemy->model->runAction(RepeatForever::create(enemy->idleAnimateLeft));
}

void EnemyType2::loadAnimations(EnemyType2* enemy)
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile(GameConstants::getEnemyAssetPath("LASER_SPRITE_SHEET"));

	enemy->idleAnimateLeft = Enemy::createAnimation(spriteCache, "LASER_IDLE_NUM_OF_FRAMES", "LASER_IDLE_SPEED", "LASER_IDLE_LEFT");
	enemy->idleAnimateRight = Enemy::createAnimation(spriteCache, "LASER_IDLE_NUM_OF_FRAMES", "LASER_IDLE_SPEED", "LASER_IDLE_RIGHT");
	enemy->idleAnimateLeft->retain();
	enemy->idleAnimateRight->retain();
	enemy->model->runAction(RepeatForever::create(enemy->idleAnimateLeft));
}

void EnemyType3::loadAnimations(EnemyType3* enemy)
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile(GameConstants::getEnemyAssetPath("TURRET_SPRITE_SHEET"));

	enemy->idleAnimate = Enemy::createAnimation(spriteCache, "TURRET_IDLE_NUM_OF_FRAMES", "TURRET_IDLE_SPEED", "TURRET_IDLE");
	enemy->idleAnimate->retain();
	enemy->model->runAction(RepeatForever::create(enemy->idleAnimate));
}