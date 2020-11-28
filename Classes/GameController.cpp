#include "GameController.h"
#include "Definitions.h"

USING_NS_CC;

Vector<Enemy*> GameController::enemies;
Vector<EnemyProjectile*> GameController::enemyProjectiles;

GameController::GameController(void){}
GameController::~GameController(void){}

bool GameController::init()
{
    enemies.clear();
    enemyProjectiles.clear();
	return true;
};

Enemy* GameController::spawnEnemy(int type)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Enemy* enemy;
    enemy = Enemy::create();
    enemy->setPhysicsBody(enemy->getBody());

    float enemyPosX = GameController::enemyPosition(enemy);
    enemy->setPosition(Vec2(enemyPosX, visibleSize.height + ENEMY_SPRITE_SIZE + origin.y));
    
    if (enemy)
    {
        GameController::enemies.pushBack( enemy );
        return enemy;
    }
    return enemy;
}
EnemyProjectile* GameController::spawnEnemyProjectile(Vec2 pos, Vec2 tar)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    EnemyProjectile* projectile;
    projectile = EnemyProjectile::create();
    projectile->setPosition( pos );
    projectile->setTarget( tar );
    projectile->setPhysicsBody(projectile->getBody());
    if (projectile)
    {
        GameController::enemyProjectiles.pushBack(projectile);
        return projectile;
    }
    return projectile;
}

float GameController::enemyPosition(Enemy* enemy){
    int spawnPoints = 4;
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float position;
    auto random = CCRANDOM_0_1()*spawnPoints;
    random = ceil(random);
    enemy->setSpawnPoint(random);
    random = random /  ((spawnPoints+1)/spawnPoints) / spawnPoints;
    position = (random * visibleSize.width) - ENEMY_SPRITE_SIZE - origin.x;
    return position;
}