#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

class Enemy
{
public:
    static cocos2d::Animate* createAnimation(cocos2d::SpriteFrameCache* spriteCache, std::string numOfFrames, std::string animSpeed, std::string assetName);
};

class EnemyType1 : public cocos2d::Node
{
public:
    static EnemyType1* create(void);
    cocos2d::Sprite* model;
    cocos2d::Animate* idleAnimateLeft;
    cocos2d::Animate* idleAnimateRight;
    cocos2d::PhysicsBody* getBody();

    void setSpawnPoint(float _spawnPoint);
    float getSpawnPoint();
    void facePlayer(int dir);

private:
    ~EnemyType1();
    EnemyType1();

    int direction;
    float spawnPoint;
    static void loadAnimations(EnemyType1* enemy);
};

class EnemyType2 : public cocos2d::Node
{
public:
    static EnemyType2* create(void);
    cocos2d::Sprite* model;
    cocos2d::Animate* idleAnimateLeft;
    cocos2d::Animate* idleAnimateRight;
    cocos2d::PhysicsBody* getBody();

    void setSpawnPoint(float _spawnPoint);
    float getSpawnPoint();
    void facePlayer(int dir);
private:
    ~EnemyType2();
    EnemyType2();

    int direction;
    float spawnPoint;
    static void loadAnimations(EnemyType2* enemy);
};


class EnemyType3 : public cocos2d::Node
{
public:
    static EnemyType3* create(void);
    cocos2d::Sprite* model;
    cocos2d::Animate* idleAnimate;
    cocos2d::PhysicsBody* getBody();

    bool canRotate();
    void setBoolRotate(bool b);
    void setSpawnPoint(int _spawnPoint);
    int getSpawnPoint();

    float getRotationAngle();
    void setRotationAngle(float _angle);
private:
    ~EnemyType3();
    EnemyType3();
    int spawnPoint;
    bool rotation;

    float angle;
    static void loadAnimations(EnemyType3* enemy);
};
#endif