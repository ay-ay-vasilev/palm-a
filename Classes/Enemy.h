#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

class Enemy : public cocos2d::Sprite
{
public:
    cocos2d::Animate * idleAnimate;

	static Enemy * create(void);

    //virtual void shoot( float dt );

    cocos2d::PhysicsBody* getBody();

    void setSpawnPoint(int _spawnPoint);
    int getSpawnPoint();
private:
    ~Enemy();
    Enemy();

    int direction;
    int col;
    int spawnPoint;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    void initEnemy();
};

#endif
