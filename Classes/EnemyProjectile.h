#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "cocos2d.h"

USING_NS_CC;

class EnemyProjectile : public cocos2d::Node
{
public:
    EnemyProjectile();
	~EnemyProjectile();
	static EnemyProjectile * create(void);
	virtual bool init();

	Vec2 getTarget();
	void setTarget( Vec2 target );
	
	Vec2 getSpeed();
	void setSpeed( Vec2 speed );
	
	cocos2d::PhysicsBody* getBody();
private:
	Vec2 target;
	Vec2 speed;
    
};
class Laser : public cocos2d::Node
{
public:
	Laser();
	~Laser();
	static Laser* create(void);
	virtual bool init();

	Vec2 getTarget();
	void setTarget(Vec2 target);

	Vec2 getSpeed();
	void setSpeed(Vec2 speed);

	cocos2d::PhysicsBody* getBody();
private:
	Vec2 target;
	Vec2 speed;
};
class LaserRay : public cocos2d::Node
{
public:
	LaserRay();
	~LaserRay();
	static LaserRay* create(void);
	virtual bool init();

	Vec2 getTarget();
	void setTarget(Vec2 target);

	cocos2d::PhysicsBody* getBody();
private:
	Vec2 target;
};
#endif
