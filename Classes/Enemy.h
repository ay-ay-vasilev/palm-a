#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

class Enemy
{
public:
    Enemy();

    void SpawnEnemy(cocos2d::Scene *level);
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
};

#endif
