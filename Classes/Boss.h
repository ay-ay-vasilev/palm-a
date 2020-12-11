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

	RayProjectile* getRay();
	void setRay(RayProjectile* _ray);

	int getPhase();
	void setPhase(int _phase);

private:
	int phase;
	int state;
	RayProjectile* ray;
	Level1Boss();
	~Level1Boss();
};