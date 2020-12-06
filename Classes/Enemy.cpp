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
	cocos2d::Animate* idleAnimate;
	if (enemy)
	{
		enemy->setContentSize(Size(ENEMY_DEFAULT_SPRITE_SIZE, ENEMY_DEFAULT_SPRITE_SIZE));
		enemy->autorelease();
		char str[200] = { 0 };
		auto spriteCache = SpriteFrameCache::getInstance();
		spriteCache->addSpriteFramesWithFile("res/enemies/enemy_regular.plist");

		Vector<SpriteFrame*> idleAnimFrames(ENEMY_DEFAULT_ANIM_IDLE_NUM_OF_FRAMES);
		for (int i = 1; i <= ENEMY_DEFAULT_ANIM_IDLE_NUM_OF_FRAMES; i++) //Iterate for the number of images you have
		{
			sprintf(str, "enemy_1_test_%i.png", i);
			idleAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
		}
		Sprite* model = Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("enemy_1_test_1.png"));
		if (model) {
			model->setAnchorPoint(Vec2(0, 0));
			model->setPosition(0, 0);

			auto idleAnimation = Animation::createWithSpriteFrames(idleAnimFrames, ENEMY_DEFAULT_ANIM_IDLE_SPEED);
			idleAnimate = Animate::create(idleAnimation);
			idleAnimate->retain(); //Retain to use it later
			model->runAction(RepeatForever::create(idleAnimate));

			enemy->addChild(model);
			enemy->setContentSize(model->getContentSize());
		}
		enemy->init();
		return enemy;
	}
	CC_SAFE_RELEASE(idleAnimate);
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
		Vector<SpriteFrame*> idleAnimFrames(ENEMY_LASER_ANIM_IDLE_NUM_OF_FRAMES);
		for (int i = 1; i <= ENEMY_LASER_ANIM_IDLE_NUM_OF_FRAMES; i++) //Iterate for the number of images you have
		{
			sprintf(str, "enemy_2_test_%i.png", i);
			idleAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
		}
		Sprite* model = Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("enemy_2_test_1.png"));
		if (model) {
			model->setAnchorPoint(Vec2(0, 0));
			model->setPosition(0, 0);

			auto idleAnimation = Animation::createWithSpriteFrames(idleAnimFrames, ENEMY_LASER_ANIM_IDLE_SPEED);
			idleAnimate_2 = Animate::create(idleAnimation);
			idleAnimate_2->retain(); //Retain to use it later
			model->runAction(RepeatForever::create(idleAnimate_2));

			enemy->addChild(model);
			enemy->setContentSize(model->getContentSize());
		}
		enemy->init();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	CC_SAFE_RELEASE(idleAnimate_2);
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
void EnemyType2::setSpawnPoint(int _spawnPoint)
{
	EnemyType2::spawnPoint = _spawnPoint;
}
int EnemyType2::getSpawnPoint()
{
	return EnemyType2::spawnPoint;
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