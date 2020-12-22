#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "cocos2d.h"

USING_NS_CC;
class Projectile : public cocos2d::Node
{
public:
	Vec2 getTarget();
	void setTarget(Vec2 target);

	Vec2 getSpeed();
	void setSpeed(Vec2 speed);

	cocos2d::PhysicsBody* getBody(int maskID);
	cocos2d::PhysicsBody* getBodyPlayer(int maskID);

private:
	Vec2 target;
	Vec2 speed;
};

class DefaultProjectile : public Projectile
{
public:
	static DefaultProjectile * create(void);
	static ParticleSystemQuad* onDestroyParticles(Vec2 position);
};
class LaserProjectile : public Projectile
{
public:
	static LaserProjectile* create(void);
	static ParticleSystemQuad* onDestroyParticles(Vec2 position);
};
class PlayerProjectile : public Projectile
{
public:
	static PlayerProjectile* create(void);
	static ParticleSystemQuad* onDestroyParticles(Vec2 position);
};


class RayProjectile : public Projectile
{
public:
	static RayProjectile* create(void);
};
#endif
