#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "EnemyProjectile.h"

class GameController
{
public:
    GameController();
	~GameController();

    static Vector<Enemy*> enemies;
    static Vector<EnemyProjectile*> enemyProjectiles;
    
    bool init();

    static Enemy* spawnEnemy(int type);
    static EnemyProjectile* spawnEnemyProjectile(Vec2 pos, Vec2 tar);

    static float enemyPosition();
private:
    

};

#endif
