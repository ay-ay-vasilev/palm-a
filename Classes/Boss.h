#pragma once

#include "cocos2d.h"
#include "Projectiles.h"

class Level1Boss : public cocos2d::Node
{
public:
	static Level1Boss* create();

	cocos2d::Sprite* model;
	cocos2d::Sprite* eye;
	cocos2d::Animate* bodyIdleAnimation;
	cocos2d::Animate* eyeIdleAnimation;
	cocos2d::Animate* firstAttack_start;
	cocos2d::Animate* firstAttack_attack;
	cocos2d::Animate* firstAttack_end;
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


	void startFirstAttack(Level1Boss* boss);
	void endFirstAttack(Level1Boss* boss);
private:
	int phase;
	int state;
	int hp;
	int initialHP;
	RayProjectile* ray;
	Level1Boss();
	~Level1Boss();

	static void loadAnimations(Level1Boss* boss);
	static cocos2d::Animate* createAnimation(cocos2d::SpriteFrameCache* spriteCache, std::string numOfFrames, std::string animSpeed, std::string assetName);
};