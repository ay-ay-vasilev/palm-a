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
int GameController::findClosestEnemy(Vec2 playerPos){
    int n = GameController::enemies.size()-1;
    int closestEnemy = n;
    if (n>0){
        float s = findDistance(GameController::enemies.at(n)->getPosition(), playerPos);
        for (int i = n; i>=0; i--)
        {
            if (s > findDistance(GameController::enemies.at(i)->getPosition(), playerPos))
            {
                s = findDistance(GameController::enemies.at(i)->getPosition(), playerPos);
                closestEnemy = i;
            }
        }
    }
    return closestEnemy;
}
float GameController::findDistance(Vec2 enemyPos, Vec2 playerPos)
{
    float distanceX = enemyPos.x - playerPos.x;
    float distanceY = enemyPos.y - playerPos.y;
    float distance = sqrt(distanceX*distanceX + distanceY*distanceY);
    return distance;
}
Vec2 GameController::calcTarget(Vec2 enemyPos, Vec2 playerPos)
{
    // enemypos = 1
    // playerpos = 2
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 offset = playerPos - enemyPos;
    offset.normalize();
    //на 2 умножил, чтобы наверняка :)
    Vec2 shootAmount = offset * visibleSize.width * 2;
    Vec2 target = shootAmount + enemyPos;
    return target;
}