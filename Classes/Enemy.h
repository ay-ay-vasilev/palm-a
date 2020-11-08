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
private:
    ~Enemy();
    Enemy();

    int direction;
    int col;

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    void initEnemy();
};

#endif
