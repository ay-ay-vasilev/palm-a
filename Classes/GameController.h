#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__

#include "cocos2d.h"
#include "Enemy.h"
#include <EnemyProjectile.h>
#include "LevelScene.h"
#include "AudioEngine.h"
#include "Player.h"
#include "Boss.h"

class GameController
{
public:
    GameController();
	~GameController();

    static Vector<EnemyType1*> type1Enemies;
    static Vector<EnemyType2*> type2Enemies;
    static Vector<EnemyType3*> type3Enemies;
    static Level1Boss* boss;

    static Vector<Node*> enemyProjectiles;
    static Vector<Node*> laserArr;
    static Vector<RayProjectile*> laserRays;
    bool init();

    static EnemyType1* spawnEnemy(int pos);
    static EnemyType2* spawnEnemyType2(int pos);
    static EnemyType3* spawnEnemyType3();

    static DefaultProjectile* spawnEnemyProjectile(Vec2 pos, Vec2 tar);
    static LaserProjectile* spawnLaser(Vec2 pos, Vec2 tar);
    static RayProjectile* spawnLaserRay(Vec2 pos, Vec2 tar);

    static float enemyPosition(EnemyType1* enemy);
    static float enemyPosition(EnemyType2* enemy);
    static float enemyPosition(EnemyType3* enemy);
    static void updateRotationType3(Vec2 playerPos);
    static void updateEnemyFacing(Vec2 playerPos);

    static float findDistance(Vec2 enemyPos, Vec2 playerPos);

    static Vec2 calcTarget(Vec2 enemyPos,Vec2 playerPos);
    static float calcAngle(Vec2 enemyPos, Vec2 playerPos);

    static float movementFunc(int spawnPoint, int movementInt);

    static void getJsonData();
    static std::vector<int> shootingTimings;
    static std::vector<int> enemySpawnTimings;
    static std::vector<int> enemyTypeArr;
    static std::vector<int> spawnPointArr;

    static Level1Boss* createLevel1Boss();
    static void bossMovement();
private:
    

};

#endif
