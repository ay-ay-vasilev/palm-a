#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__

#include "cocos2d.h"
#include "Enemy.h"

class GameController
{
public:
    GameController();
	~GameController();

    static Vector<Enemy*> enemies;
    
    bool init();

    static Enemy* spawnEnemy();
    
private:
    

};

#endif
