#include "GameController.h"
#include "Definitions.h"

USING_NS_CC;

Vector<Enemy*> GameController::enemies;
Vector<EnemyProjectile*> GameController::enemyProjectiles;

GameController::GameController(void){}
GameController::~GameController(void){}

bool GameController::init()
{
	return true;
};

Enemy* spawnEnemy()
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    Enemy* enemySprite = nullptr;
    enemySprite = Enemy::create();
    enemySprite->setPhysicsBody(enemySprite->getBody());
    //enemySprite->schedule(schedule_selector( Enemy::shoot ), 1 );

    if (enemySprite)
    {
        GameController::enemies.pushBack( enemySprite );
        return enemySprite;
    }
    return enemySprite;
}
EnemyProjectile* spawnEnemyProjectile(Vec2 pos, Vec2 tar)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    EnemyProjectile* projectile = nullptr;
    projectile = EnemyProjectile::create();
    projectile->setPosition( pos );
    projectile->setTarget( tar );
    if (projectile)
    {
        GameController::enemyProjectiles.pushBack(projectile);
        return projectile;
    }
    return projectile;
}