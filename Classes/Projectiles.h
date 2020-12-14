#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "cocos2d.h"

USING_NS_CC;
class Projectile
{
public:
	static cocos2d::Animate* createAnimation(cocos2d::SpriteFrameCache* spriteCache, std::string numOfFrames, std::string animSpeed, std::string assetName);
private:

};
class DefaultProjectile : public cocos2d::Node
{
public:
    DefaultProjectile();
	~DefaultProjectile();
	static DefaultProjectile * create(void);
	virtual bool init();

	Vec2 getTarget();
	void setTarget( Vec2 target );
	
	Vec2 getSpeed();
	void setSpeed( Vec2 speed );
	
	cocos2d::PhysicsBody* getBody();
	cocos2d::PhysicsBody* getBodyPlayer();

	static ParticleSystemQuad* onDestroyParticles(Vec2 position);

private:
	Vec2 target;
	Vec2 speed;

};
class LaserProjectile : public cocos2d::Node
{
public:
	LaserProjectile();
	~LaserProjectile();
	static LaserProjectile* create(void);
	virtual bool init();

	Vec2 getTarget();
	void setTarget(Vec2 target);

	Vec2 getSpeed();
	void setSpeed(Vec2 speed);

	cocos2d::PhysicsBody* getBody();

	static ParticleSystemQuad* onDestroyParticles(Vec2 position);

private:
	Vec2 target;
	Vec2 speed;
};
class RayProjectile : public cocos2d::Node
{
public:
	RayProjectile();
	~RayProjectile();
	static RayProjectile* create(void);
	virtual bool init();


	Vec2 getTarget();
	void setTarget(Vec2 target);


	cocos2d::PhysicsBody* getBody();
private:
	Vec2 target;
};
#endif
