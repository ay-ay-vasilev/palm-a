#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__

#include "cocos2d.h"
#include "Enemy.h"
#include <EnemyProjectile.h>
#include "LevelScene.h"
#include "AudioEngine.h"
#include "Player.h"

class GameController
{
public:
    GameController();
	~GameController();

    static Vector<Enemy*> enemies;
    static Vector<EnemyType2*> type2Enemies;
    static Vector<EnemyType3*> type3Enemies;

    static Vector<Node*> enemyProjectiles;
    static Vector<Node*> laserArr;
    static Vector<LaserRay*> laserRays;
    bool init();

    static Enemy* spawnEnemy();
    static EnemyType2* spawnEnemyType2();
    static EnemyType3* spawnEnemyType3();

    static EnemyProjectile* spawnEnemyProjectile(Vec2 pos, Vec2 tar);
    static Laser* spawnLaser(Vec2 pos, Vec2 tar);
    static LaserRay* spawnLaserRay(Vec2 pos, Vec2 tar);

    static float enemyPosition(Enemy* enemy);
    static float enemyPosition(EnemyType2* enemy);
    static float enemyPosition(EnemyType3* enemy);
    static void updateRotationType3(Vec2 playerPos);

    static float findDistance(Vec2 enemyPos, Vec2 playerPos);

    static Vec2 calcTarget(Vec2 enemyPos,Vec2 playerPos);
    static float calcAngle(Vec2 enemyPos, Vec2 playerPos);

    static float movementFunc(int spawnPoint, int movementInt);

    static void getJsonData();
    static std::vector<int> shootingTimings;

    static int randomTypeOfEnemy();
private:
    

};

#endif
