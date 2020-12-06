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
		enemy->setContentSize(Size(ENEMY_SPRITE_SIZE, ENEMY_SPRITE_SIZE));
		enemy->autorelease();
		char str[200] = { 0 };
		auto spriteCache = SpriteFrameCache::getInstance();
		spriteCache->addSpriteFramesWithFile("res/enemies/enemy_regular.plist");

		Vector<SpriteFrame*> idleAnimFrames(ENEMY_ANIM_IDLE_NUM_OF_FRAMES);
		for (int i = 1; i <= ENEMY_ANIM_IDLE_NUM_OF_FRAMES; i++) //Iterate for the number of images you have
		{
			sprintf(str, "enemy_1_test_%i.png", i);
			idleAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
		}
		Sprite* model = Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("enemy_1_test_1.png"));
		if (model) {
			model->setAnchorPoint(Vec2(0, 0));
			model->setPosition(0, 0);

			auto idleAnimation = Animation::createWithSpriteFrames(idleAnimFrames, ENEMY_ANIM_IDLE_SPEED);
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
		enemy->setContentSize(Size(ENEMY_SPRITE_SIZE, ENEMY_SPRITE_SIZE));
		enemy->autorelease();

		char str[200] = { 0 };

		auto spriteCache = SpriteFrameCache::getInstance();
		spriteCache->addSpriteFramesWithFile("res/enemies/enemy_variant.plist");
		Vector<SpriteFrame*> idleAnimFrames(ENEMY_ANIM_IDLE_NUM_OF_FRAMES);
		for (int i = 1; i <= ENEMY_ANIM_IDLE_NUM_OF_FRAMES; i++) //Iterate for the number of images you have
		{
			sprintf(str, "enemy_2_test_%i.png", i);
			idleAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
		}
		Sprite* model = Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("enemy_2_test_1.png"));
		if (model) {
			model->setAnchorPoint(Vec2(0, 0));
			model->setPosition(0, 0);

			auto idleAnimation = Animation::createWithSpriteFrames(idleAnimFrames, ENEMY_ANIM_IDLE_SPEED);
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
	if (enemy)
	{
		enemy->setContentSize(Size(ENEMY_SPRITE_SIZE, ENEMY_SPRITE_SIZE));
		enemy->autorelease();

		Sprite* model = Sprite::create("res/enemies/enemy_turret.png");
		if (model) {
			model->setAnchorPoint(Vec2(0, 0));
			model->setPosition(0, 0);

			enemy->addChild(model);
			enemy->setContentSize(model->getContentSize());
		}
		enemy->init();
		return enemy;
	}

	CC_SAFE_DELETE(enemy);
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