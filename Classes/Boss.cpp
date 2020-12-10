#include "Boss.h"
#include "GameController.h"

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
	auto physicsBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);

	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(8);
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
LaserRay* Level1Boss::getRay()
{
	return ray;
}
void Level1Boss::setRay(LaserRay* _ray)
{
	ray = _ray;
}