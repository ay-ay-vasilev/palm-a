#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

class Enemy : public cocos2d::Sprite
{
public:
    cocos2d::Animate* idleAnimate;

    static Enemy* create(void);

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
class EnemyType2 : public cocos2d::Sprite
{
public:
    cocos2d::Animate* idleAnimate_2;

    static EnemyType2* create(void);

    cocos2d::PhysicsBody* getBody();

    void setSpawnPoint(int _spawnPoint);
    int getSpawnPoint();
private:
    ~EnemyType2();
    EnemyType2();
    int spawnPoint;
    void initEnemy();

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
};
#endif