#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

class Enemy : public cocos2d::Node
{
public:
    cocos2d::Sprite* model;
    void setSpawnPoint(float _spawnPoint);
    float getSpawnPoint();
    cocos2d::PhysicsBody* getBody();
private:
    float spawnPoint;
};

class EnemyType1 : public Enemy
{
public:
    static EnemyType1* create(void);
    cocos2d::Sprite* model;
    cocos2d::Animate* idleAnimateLeft;
    cocos2d::Animate* idleAnimateRight;

    void facePlayer(int dir);

private:
    ~EnemyType1();
    EnemyType1();

    int direction;
    static void loadAnimations(EnemyType1* enemy);
};

class EnemyType2 : public Enemy
{
public:
    static EnemyType2* create(void);
    cocos2d::Sprite* model;
    cocos2d::Animate* idleAnimateLeft;
    cocos2d::Animate* idleAnimateRight;

    void facePlayer(int dir);
private:
    ~EnemyType2();
    EnemyType2();

    int direction;
    static void loadAnimations(EnemyType2* enemy);
};


class EnemyType3 : public Enemy
{
public:
    static EnemyType3* create(void);
    cocos2d::Sprite* model;
    cocos2d::Animate* idleAnimate;

    bool canRotate();
    void setBoolRotate(bool b);

    float getRotationAngle();
    void setRotationAngle(float _angle);
private:
    ~EnemyType3();
    EnemyType3();
    bool rotation;

    float angle;
    static void loadAnimations(EnemyType3* enemy);
};
#endif