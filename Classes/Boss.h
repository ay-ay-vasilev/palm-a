#pragma once

#include "cocos2d.h"
#include "Projectiles.h"

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

	void getDamage(int _dmg);
	int getHp();
	void setHp(int _hp);
	int getInitialHp();

private:
	int phase;
	int state;
	int hp;
	int initialHP;
	RayProjectile* ray;
	Level1Boss();
	~Level1Boss();
};