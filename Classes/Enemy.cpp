#include "Definitions.h"
#include "Enemy.h"
#include "GameController.h"
USING_NS_CC;

Enemy::Enemy() {}
Enemy::~Enemy()
{
}
Enemy* Enemy::create() {
	Enemy* enemy = new Enemy();
	if (enemy)
	{
		enemy->setContentSize(Size(ENEMY_DEFAULT_SPRITE_SIZE, ENEMY_DEFAULT_SPRITE_SIZE));
		enemy->autorelease();
		char str[200] = { 0 };
		auto spriteCache = SpriteFrameCache::getInstance();
		spriteCache->addSpriteFramesWithFile("res/enemies/enemy_regular.plist");

		Vector<SpriteFrame*> idleLeftAnimFrames(ENEMY_DEFAULT_ANIM_IDLE_NUM_OF_FRAMES);
		Vector<SpriteFrame*> idleRightAnimFrames(ENEMY_DEFAULT_ANIM_IDLE_NUM_OF_FRAMES);
		for (int i = 1; i <= ENEMY_DEFAULT_ANIM_IDLE_NUM_OF_FRAMES; i++)
		{
			sprintf(str, "enemy_1_left%i.png", i);
			idleLeftAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
			
			sprintf(str, "enemy_1_right%i.png", i);
			idleRightAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
		}

		enemy->model = Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("enemy_1_left1.png"));
		if (enemy->model) {
			enemy->model->setAnchorPoint(Vec2(0, 0));
			enemy->model->setPosition(0, 0);

			auto idleLeftAnimation = Animation::createWithSpriteFrames(idleLeftAnimFrames, ENEMY_DEFAULT_ANIM_IDLE_SPEED);
			auto idleRightAnimation = Animation::createWithSpriteFrames(idleRightAnimFrames, ENEMY_DEFAULT_ANIM_IDLE_SPEED);

			enemy->idleAnimateLeft = Animate::create(idleLeftAnimation);
			enemy->idleAnimateRight = Animate::create(idleRightAnimation);

			enemy->idleAnimateLeft->retain();
			enemy->idleAnimateRight->retain();

			enemy->model->runAction(RepeatForever::create(enemy->idleAnimateLeft));

			enemy->setContentSize(enemy->model->getContentSize());
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
cocos2d::PhysicsBody* Enemy::getBody()
{
	auto physicsBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);

	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(2);
	physicsBody->setContactTestBitmask(true);
	return physicsBody;
}
void Enemy::setSpawnPoint(float _spawnPoint)
{
	Enemy::spawnPoint = _spawnPoint;
}
float Enemy::getSpawnPoint()
{
	return Enemy::spawnPoint;
}
void Enemy::facePlayer(int dir)
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
	cocos2d::Animate* idleAnimate_2;
	if (enemy)
	{
		enemy->setContentSize(Size(ENEMY_LASER_SPRITE_SIZE, ENEMY_LASER_SPRITE_SIZE));
		enemy->autorelease();
		char str[200] = { 0 };
		auto spriteCache = SpriteFrameCache::getInstance();
		spriteCache->addSpriteFramesWithFile("res/enemies/enemy_variant.plist");

		Vector<SpriteFrame*> idleLeftAnimFrames(ENEMY_LASER_ANIM_IDLE_NUM_OF_FRAMES);
		Vector<SpriteFrame*> idleRightAnimFrames(ENEMY_LASER_ANIM_IDLE_NUM_OF_FRAMES);

		for (int i = 1; i <= ENEMY_LASER_ANIM_IDLE_NUM_OF_FRAMES; i++) //Iterate for the number of images you have
		{
			sprintf(str, "enemy_2_left%i.png", i);
			idleLeftAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));

			sprintf(str, "enemy_2_right%i.png", i);
			idleRightAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
		}

		enemy->model = Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("enemy_2_left1.png"));
		if (enemy->model) {
			enemy->model->setAnchorPoint(Vec2(0, 0));
			enemy->model->setPosition(0, 0);

			auto idleLeftAnimation = Animation::createWithSpriteFrames(idleLeftAnimFrames, ENEMY_LASER_ANIM_IDLE_SPEED);
			auto idleRightAnimation = Animation::createWithSpriteFrames(idleRightAnimFrames, ENEMY_LASER_ANIM_IDLE_SPEED);

			enemy->idleAnimateLeft = Animate::create(idleLeftAnimation);
			enemy->idleAnimateRight = Animate::create(idleRightAnimation);

			enemy->idleAnimateLeft->retain();
			enemy->idleAnimateRight->retain();

			enemy->model->runAction(RepeatForever::create(enemy->idleAnimateLeft));

			enemy->setContentSize(enemy->model->getContentSize());
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
	physicsBody->setCollisionBitmask(5);
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
	cocos2d::Animate* idleAnimate_3;
	if (enemy)
	{
		enemy->setContentSize(Size(ENEMY_TURRET_SPRITE_SIZE, ENEMY_TURRET_SPRITE_SIZE));
		enemy->autorelease();

		char str[200] = { 0 };

		auto spriteCache = SpriteFrameCache::getInstance();
		spriteCache->addSpriteFramesWithFile("res/enemies/enemy_turret.plist");
		Vector<SpriteFrame*> idleAnimFrames(ENEMY_TURRET_ANIM_IDLE_NUM_OF_FRAMES);
		for (int i = 1; i <= ENEMY_TURRET_ANIM_IDLE_NUM_OF_FRAMES; i++) //Iterate for the number of images you have
		{
			sprintf(str, "enemy_turret%i.png", i);
			idleAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
		}
		Sprite* model = Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("enemy_turret1.png"));
		if (model) {
			model->setAnchorPoint(Vec2(0, 0));
			model->setPosition(0, 0);

			auto idleAnimation = Animation::createWithSpriteFrames(idleAnimFrames, ENEMY_TURRET_ANIM_IDLE_SPEED);
			idleAnimate_3 = Animate::create(idleAnimation);
			idleAnimate_3->retain(); //Retain to use it later
			model->runAction(RepeatForever::create(idleAnimate_3));

			enemy->addChild(model);
			enemy->setContentSize(model->getContentSize());
		}
		Vec2 anchor = Vec2(1, 0.5);
		enemy->setAnchorPoint(anchor);
		enemy->setBoolRotate(true);
		enemy->init();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	CC_SAFE_RELEASE(idleAnimate_3);
	return NULL;
}
cocos2d::PhysicsBody* EnemyType3::getBody()
{
	auto physicsBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);

	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(6);
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