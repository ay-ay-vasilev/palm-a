#include "GameController.h"
#include "Definitions.h"

USING_NS_CC;

Vector<Enemy*> GameController::enemies;

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
        enemies.pushBack( enemySprite );
        return enemySprite;
    }
    return enemySprite;
}