#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

class Enemy : public cocos2d::Node
{
public:
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

};
class EnemyType2 : public cocos2d::Node
{
public:


    static EnemyType2* create(void);

    cocos2d::PhysicsBody* getBody();

    void setSpawnPoint(int _spawnPoint);
    int getSpawnPoint();
private:
    ~EnemyType2();
    EnemyType2();
    int spawnPoint;
};
class EnemyType3 : public cocos2d::Node
{
public:
    static EnemyType3* create(void);

    cocos2d::PhysicsBody* getBody();

    void setSpawnPoint(int _spawnPoint);
    int getSpawnPoint();
private:
    ~EnemyType3();
    EnemyType3();
    int spawnPoint;
};
#endif