#pragma once

#include "cocos2d.h"
#include "EnemyProjectile.h"

class Level1Boss : public cocos2d::Node
{
public:
	static Level1Boss* create();

	cocos2d::Sprite* model;
	cocos2d::Animate* idleAnimation;
	cocos2d::PhysicsBody* getBody();

	int getState();
	void setState(int _state);

	LaserRay* getRay();
	void setRay(LaserRay* _ray);

private:
	int state;
	LaserRay* ray;
	Level1Boss();
	~Level1Boss();
};