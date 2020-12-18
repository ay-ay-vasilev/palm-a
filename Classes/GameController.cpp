#include "GameController.h"
#include "GameConstants.h"
#include "Definitions.h"
#include "fstream"
USING_NS_CC;

Vector<EnemyType1*> GameController::type1Enemies;
Vector<Node*> GameController::enemyProjectiles;
Vector<EnemyType2*> GameController::type2Enemies;
Vector<Node*> GameController::laserArr;
Vector<EnemyType3*> GameController::type3Enemies;
Vector<RayProjectile*> GameController::laserRays;
Level1Boss* GameController::boss;
bool GameController::bossFightIsOn;

std::vector<int> GameController::shootingTimings;
std::vector<int> GameController::enemySpawnTimings;
std::vector<int> GameController::enemyTypeArr;
std::vector<int> GameController::spawnPointArr;

GameController::GameController(void){}
GameController::~GameController(void){}

bool GameController::init()
{
    type1Enemies.clear();
    enemyProjectiles.clear();
    return true;
};

EnemyType1* GameController::spawnEnemy(int pos)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    EnemyType1 * enemy;
    enemy = EnemyType1::create();
    enemy->setSpawnPoint(pos);
    enemy->setPhysicsBody(enemy->getBody());

    float enemyPosX = GameController::enemyPosition(enemy);
    enemy->setPosition(Vec2(enemyPosX, visibleSize.height + enemy->getContentSize().width + origin.y));

    if (enemy)
    {
        GameController::type1Enemies.pushBack(enemy);
        return enemy;
    }
    return enemy;
        
    
}
EnemyType2* GameController::spawnEnemyType2(int pos)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();

    EnemyType2* enemy;
    enemy = EnemyType2::create();
    enemy->setSpawnPoint(pos);
    enemy->setPhysicsBody(enemy->getBody());

    float enemyPosX = GameController::enemyPosition(enemy);
    enemy->setPosition(Vec2(enemyPosX, visibleSize.height + enemy->getContentSize().width + origin.y));

    if (enemy)
    {
        GameController::type2Enemies.pushBack(enemy);
        return enemy;
    }
    return enemy;
}
EnemyType3* GameController::spawnEnemyType3()
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();

    EnemyType3* enemy = EnemyType3::create();
    enemy->setPhysicsBody(enemy->getBody());

    float enemyPosX = GameController::enemyPosition(enemy);
    enemy->setPosition(Vec2(enemyPosX, -1* enemy->getContentSize().width));
    if (enemy) {
        GameController::type3Enemies.pushBack(enemy);
        return enemy;
    }
    return enemy;
}
PlayerProjectile* GameController::spawnPlayerProjectile(Vec2 pos)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    PlayerProjectile* projectile;
    projectile = PlayerProjectile::create();
    projectile->setPosition(pos);
    projectile->setPhysicsBody(projectile->getBody(PLAYER_PROJECTILE_MASK));

    if (projectile)
    {
        GameController::enemyProjectiles.pushBack(projectile);
        return projectile;
    }
    return projectile;
}
DefaultProjectile* GameController::spawnEnemyProjectile(Vec2 pos, Vec2 tar)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    DefaultProjectile* projectile;
    projectile = DefaultProjectile::create();
    projectile->setPosition( pos );
    projectile->setTarget( tar );
    projectile->setPhysicsBody(projectile->getBody(DEFAULT_PROJECTILE_MASK));

    if (projectile)
    {
        GameController::enemyProjectiles.pushBack(projectile);
        return projectile;
    }
    return projectile;
}
LaserProjectile* GameController::spawnLaser(Vec2 pos, Vec2 tar)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    LaserProjectile* projectile;
    projectile = LaserProjectile::create();
    projectile->setPosition(pos);
    projectile->setTarget(tar);
    projectile->setPhysicsBody(projectile->getBody(LASER_PROJECTILE_MASK));
    if (projectile)
    {
        GameController::laserArr.pushBack(projectile);
        return projectile;
    }
    return projectile;
}
RayProjectile* GameController::spawnLaserRay(Vec2 tar)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    RayProjectile* projectile;
    projectile = RayProjectile::create();
    projectile->setTarget(tar);
    projectile->setPhysicsBody(projectile->getBody(RAY_PROJECTILE_MASK));
    if (projectile)
    {
        GameController::laserRays.pushBack(projectile);
        return projectile;
    }
    return projectile;
}
float GameController::enemyPosition(EnemyType1* enemy){
    float spawnPoints = 4.0;
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float position;
    auto spawnPoint = enemy->getSpawnPoint();
    spawnPoint = spawnPoint*1.0 /  (spawnPoints+1);
    position = (spawnPoint * visibleSize.width) - enemy->getContentSize().width / 2;
    return position;
}
float GameController::enemyPosition(EnemyType2* enemy) {
    float spawnPoints = 4.0;
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float position;
    auto spawnPoint = enemy->getSpawnPoint();
    spawnPoint = spawnPoint / (spawnPoints + 1);
    position = (spawnPoint * visibleSize.width) - enemy->getContentSize().width / 2;
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
        position = GameConstants::getLevelStats("WALL_DISTANCE") / 2;
        return position;
    }
    else 
    {
        enemy->setScale(0.25 * RESOLUTION_VARIABLE);
        position = visibleSize.width - GameConstants::getLevelStats("WALL_DISTANCE") / 2;
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
    int enemyScatter = 20;
    Vec2 scatterVec = Vec2(RandomHelper::random_int(-enemyScatter, enemyScatter), RandomHelper::random_int(-enemyScatter, enemyScatter));
    Vec2 offset = playerPos - enemyPos + scatterVec;
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
    fin.close();
    //enemies timings 
    fin.open((std::string)ENEMIES_SPAWN_TIMINGS);
    if (fin.fail()) {
        fin.open("../" + (std::string)ENEMIES_SPAWN_TIMINGS);
    }

    s = 0;
    fin >> s;
    while (s != 0)
    {
        enemySpawnTimings.push_back(s);
        fin >> s;
    }
    fin.close();
    //enemies types
    fin.open((std::string)ENEMIES_SPAWN_TYPES);
    if (fin.fail()) {
        fin.open("../" + (std::string)ENEMIES_SPAWN_TYPES);
    }

    s = 0;
    fin >> s;
    while (s != 0)
    {
        enemyTypeArr.push_back(s);
        fin >> s;
    }
    fin.close();
    //enemies spawn points
    fin.open((std::string)ENEMIES_SPAWN_POINTS);
    if (fin.fail()) {
        fin.open("../" + (std::string)ENEMIES_SPAWN_POINTS);
    }

    s = 0;
    fin >> s;
    while (s != 0)
    {
        spawnPointArr.push_back(s);
        fin >> s;
    }
    fin.close();
    bossFightIsOn = false;
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
Level1Boss* GameController::createLevel1Boss()
{
    Level1Boss* _boss = Level1Boss::create();
    _boss->model->setPhysicsBody(_boss->getBody());
    _boss->setHp(20);

    if (_boss)
    {
        boss = _boss;
        return _boss;
    }
    return NULL;
}
void GameController::bossMovement()
{
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    //state 1 = dropping after creation
    //state 2 = moving left to right
    //state 3 = moving right to left
    if (bossFightIsOn)
    {


        auto bossSpeed = 1;
        if (boss->getState() == 2)
        {
            boss->setPosition(Vec2(boss->getPosition().x + bossSpeed * RESOLUTION_VARIABLE, boss->getPosition().y));
            if (boss->getPosition().x >= visibleSize.width - boss->getContentSize().width * 0.25 * RESOLUTION_VARIABLE)
            {
                boss->setState(3);
                boss->setPhase(boss->getPhase() + 1);
                if (boss->getPhase() == 2) boss->setState(4);
            }
            boss->getRay()->setPosition(Vec2(boss->getPosition().x, boss->getPosition().y + boss->getRay()->getContentSize().width / 5));
        }
        if (boss->getState() == 3)
        {
            boss->setPosition(Vec2(boss->getPosition().x - bossSpeed * RESOLUTION_VARIABLE, boss->getPosition().y));
            if (boss->getPosition().x <= boss->getContentSize().width * 0.25 * RESOLUTION_VARIABLE)
            {
                boss->setState(2);
                boss->setPhase(boss->getPhase() + 1);
                if (boss->getPhase() == 2) boss->setState(4);
            }
            boss->getRay()->setPosition(Vec2(boss->getPosition().x, boss->getPosition().y + boss->getRay()->getContentSize().width / 5));
        }
        if (boss->getState() == 4)
        {
            if (boss->getPosition().x < visibleSize.width / 2)
            {
                boss->setPosition(Vec2(boss->getPosition().x + bossSpeed * RESOLUTION_VARIABLE, boss->getPosition().y));
            }
            else
            {
                boss->getRay()->setRotation(boss->getRay()->getRotation() + 1);
                if (boss->getRay()->getRotation() > 180) boss->setState(5);
            }
            boss->getRay()->setPosition(Vec2(boss->getPosition().x, boss->getPosition().y + boss->getRay()->getContentSize().width / 5));
        }
        if (boss->getState() == 5)
        {
            boss->getRay()->setRotation(boss->getRay()->getRotation() - 1);
            if (boss->getRay()->getRotation() < 0) boss->setState(4);
        }
    }
}