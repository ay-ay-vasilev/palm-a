#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__

#include "cocos2d.h"
#include "Enemy.h"
#include <EnemyProjectile.h>

class GameController
{
public:
    GameController();
	~GameController();

    static Vector<Enemy*> enemies;
    static Vector<EnemyType2*> type2Enemies;
    
    static Vector<Node*> enemyProjectiles;
    static Vector<Node*> laserArr;
    bool init();

    static Enemy* spawnEnemy();
    static EnemyType2* spawnEnemyType2();

    static EnemyProjectile* spawnEnemyProjectile(Vec2 pos, Vec2 tar);
    static Laser* spawnLaser(Vec2 pos, Vec2 tar);

    static float enemyPosition(Enemy* enemy);
    static float enemyPosition(EnemyType2* enemy);

    static int findClosestEnemy(Vec2 playerPos);

    static float findDistance(Vec2 enemyPos, Vec2 playerPos);

    static Vec2 calcTarget(Vec2 enemyPos,Vec2 playerPos);
    static float calcAngle(Vec2 enemyPos, Vec2 playerPos);

    static float movementFunc(int spawnPoint, int movementInt);
private:
    

};

#endif
