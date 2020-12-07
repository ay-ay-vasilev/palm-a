#include "GameController.h"
#include "Definitions.h"
#include "fstream"
USING_NS_CC;

Vector<Enemy*> GameController::type1Enemies;
Vector<Node*> GameController::enemyProjectiles;
Vector<EnemyType2*> GameController::type2Enemies;
Vector<Node*> GameController::laserArr;
Vector<EnemyType3*> GameController::type3Enemies;
Vector<LaserRay*> GameController::laserRays;

std::vector<int> GameController::shootingTimings;

GameController::GameController(void){}
GameController::~GameController(void){}

bool GameController::init()
{
    type1Enemies.clear();
    enemyProjectiles.clear();
    return true;
};

Enemy* GameController::spawnEnemy()
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Enemy * enemy;
    enemy = Enemy::create();
    enemy->setPhysicsBody(enemy->getBody());

    float enemyPosX = GameController::enemyPosition(enemy);
    enemy->setPosition(Vec2(enemyPosX, visibleSize.height + ENEMY_DEFAULT_SPRITE_SIZE + origin.y));

    if (enemy)
    {
        GameController::type1Enemies.pushBack(enemy);
        return enemy;
    }
    return enemy;
        
    
}
EnemyType2* GameController::spawnEnemyType2()
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();

    EnemyType2* enemy_type2;
    enemy_type2 = EnemyType2::create();
    enemy_type2->setPhysicsBody(enemy_type2->getBody());

    float enemyPosX = GameController::enemyPosition(enemy_type2);
    enemy_type2->setPosition(Vec2(enemyPosX, visibleSize.height + ENEMY_LASER_SPRITE_SIZE + origin.y));

    if (enemy_type2)
    {
        GameController::type2Enemies.pushBack(enemy_type2);
        return enemy_type2;
    }
    return enemy_type2;
}
EnemyType3* GameController::spawnEnemyType3()
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();

    EnemyType3* enemy = EnemyType3::create();
    enemy->setPhysicsBody(enemy->getBody());

    float enemyPosX = GameController::enemyPosition(enemy);
    enemy->setPosition(Vec2(enemyPosX, -1* ENEMY_TURRET_SPRITE_SIZE));
    if (enemy) {
        GameController::type3Enemies.pushBack(enemy);
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
Laser* GameController::spawnLaser(Vec2 pos, Vec2 tar)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    Laser* projectile;
    projectile = Laser::create();
    projectile->setPosition(pos);
    projectile->setTarget(tar);
    projectile->setPhysicsBody(projectile->getBody());
    if (projectile)
    {
        GameController::laserArr.pushBack(projectile);
        return projectile;
    }
    return projectile;
}
LaserRay* GameController::spawnLaserRay(Vec2 pos, Vec2 tar)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    LaserRay* projectile;
    projectile = LaserRay::create();
    projectile->setPosition(pos);
    projectile->setTarget(tar);
    projectile->setPhysicsBody(projectile->getBody());
    if (projectile)
    {
        GameController::laserRays.pushBack(projectile);
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
    position = (random * visibleSize.width) - (float)ENEMY_DEFAULT_SPRITE_SIZE - origin.x;
    return position;
}
float GameController::enemyPosition(EnemyType2* enemy) {
    int spawnPoints = 4;
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float position;
    auto random = CCRANDOM_0_1() * spawnPoints;
    random = ceil(random);
    enemy->setSpawnPoint(random);
    random = random / ((spawnPoints + 1) / spawnPoints) / spawnPoints;
    position = (random * visibleSize.width) - (float)ENEMY_LASER_SPRITE_SIZE - origin.x;
    return position;
}
float GameController::enemyPosition(EnemyType3* enemy) {
    int spawnPoints = 2;
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float position;
    auto random = RandomHelper::random_int(1,2);
    enemy->setSpawnPoint(random);
    if (random == 1)
    {
        enemy->setScale(-0.25 * RESOLUTION_VARIABLE);
        position = LEVEL_WALL_DISTANCE * (float)RESOLUTION_VARIABLE / 2;
        return position;
    }
    else 
    {
        enemy->setScale(0.25 * RESOLUTION_VARIABLE);
        position = visibleSize.width - LEVEL_WALL_DISTANCE * (float)RESOLUTION_VARIABLE / 2;
        return position;
    }
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
    //multiplied by 2 because sometimes it doesn't reach
    Vec2 shootAmount = offset * visibleSize.width * 2;
    Vec2 target = shootAmount + enemyPos;
    return target;
}
float GameController::movementFunc(int spawnPoint, int movementInt)
{
    float moveArr[4][2];
    moveArr[0][0] = -0.1;
    moveArr[0][1] = 0.1;
    moveArr[1][0] = 0.2;
    moveArr[1][1] = -0.2;
    moveArr[2][0] = -0.2;
    moveArr[2][1] = 0.2;
    moveArr[3][0] = 0.1;
    moveArr[3][1] = -0.1;

    return moveArr[spawnPoint][movementInt];
}
float GameController::calcAngle(Vec2 enemyPos, Vec2 playerPos)
{
    float distanceX = enemyPos.x - playerPos.x;
    float distance = findDistance(enemyPos, playerPos);

    auto angle = 90 + asin(distanceX / distance) * 180 / PI;
    return angle;
}
void GameController::getJsonData()
{
    //timings data
    std::ifstream fin;
    fin.open((std::string) LEVEL_1_DATA);
    if (fin.fail()) {
        fin.open("../" + (std::string) LEVEL_1_DATA);
    }
    
    auto s = 0;
    fin >> s;
    while (s!=0)
    {
        shootingTimings.push_back(s);
        fin >> s;
    }
}
int GameController::randomTypeOfEnemy()
{
    auto random = CCRANDOM_0_1();
    if (random < 0.2)
    {
        return 2;
    }
    else {
        return 1;
    }
}
void GameController::updateRotationType3(Vec2 playerPos)
{
    for (int i = type3Enemies.size() - 1; i >= 0; i--){
        if (type3Enemies.at(i)->canRotate())
        {
            auto angle = calcAngle(type3Enemies.at(i)->getPosition(), playerPos);
            if (type3Enemies.at(i)->getSpawnPoint() == 2)
            {
                angle += 180;

            }
            if (type3Enemies.at(i)->getPosition().y < playerPos.y)
            {
                angle = 360 - angle;
            }
            type3Enemies.at(i)->setRotationAngle(angle);
            type3Enemies.at(i)->setRotation(angle);
        }
    }
}

void GameController::updateEnemyFacing(Vec2 playerPos)
{
    for (int i = type1Enemies.size() - 1; i >= 0; i--) {
        if (type1Enemies.at(i)->getPosition().x < playerPos.x) {
            type1Enemies.at(i)->facePlayer(DIRECTION_RIGHT);
        }
        else if (type1Enemies.at(i)->getPosition().x > playerPos.x) {
            type1Enemies.at(i)->facePlayer(DIRECTION_LEFT);
        }
    }

    for (int i = type2Enemies.size() - 1; i >= 0; i--) {
        if (type2Enemies.at(i)->getPosition().x < playerPos.x) {
            type2Enemies.at(i)->facePlayer(DIRECTION_RIGHT);
        }
        else if (type2Enemies.at(i)->getPosition().x > playerPos.x) {
            type2Enemies.at(i)->facePlayer(DIRECTION_LEFT);
        }
    }
}