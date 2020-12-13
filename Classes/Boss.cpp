#include "Boss.h"
#include "GameController.h"
#include "Definitions.h"

Level1Boss::Level1Boss() {}
Level1Boss::~Level1Boss() {}

Level1Boss* Level1Boss::create()
{
	Level1Boss* boss = new Level1Boss();

	if (boss)
	{
		boss->autorelease();
		boss->model = cocos2d::Sprite::create("res/bosses/boss_test.png");
		if (boss->model)
		{
			boss->model->setAnchorPoint(Vec2(0, 0));
			boss->model->setPosition(Vec2(0, 0));

			boss->setContentSize(boss->model->getContentSize());
			boss->addChild(boss->model);
		}
		boss->setAnchorPoint(Vec2(0.5, 0));
		boss->init();
		return boss;
	}
	CC_SAFE_RELEASE(boss);
	return NULL;
}
cocos2d::PhysicsBody* Level1Boss::getBody()
{
	auto physicsBody = PhysicsBody::createBox(Size(this->getContentSize().width/3, this->getContentSize().height/6), PHYSICSBODY_MATERIAL_DEFAULT);

	physicsBody->setPositionOffset(Vec2(0, 0));

	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(BOSS_MASK);
	physicsBody->setContactTestBitmask(true);
	return physicsBody;
}
int Level1Boss::getState()
{
	return state;
}
void Level1Boss::setState(int _state)
{
	state = _state;
}
RayProjectile* Level1Boss::getRay()
{
	return ray;
}
void Level1Boss::setRay(RayProjectile* _ray)
{
	ray = _ray;
}
int Level1Boss::getPhase()
{
	return phase;
}
void Level1Boss::setPhase(int _phase)
{
	phase = _phase;
}