#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__

#include <deque>
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Projectiles.h"
#include "GameController.h"
#include "LevelFinishScene.h"
#include "JsonInstance.h"
#include "GameConstants.h"
#include "Boss.h"
#include "GameUI.h"

class Level : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Level);
    // MOVE LATER
	void removeProjectile(Node *projectile);
    void removeEnemy(EnemyType1 *enemy);
    void removeLaser(Node *laser);
    void removeLaserRay(RayProjectile *ray);
    void removeEnemyType2(EnemyType2 *enemy);
    void removeEnemyType3(EnemyType3* enemy);

    bool onContactBegin ( cocos2d::PhysicsContact &contact );

    // MOVE LATER
    int currentTiming;
    int currentEnemy = 0;
    int musicID;
    int bossMusicID;

    cocos2d::SEL_SCHEDULE enemyType3SpawnPointer;
    cocos2d::SEL_SCHEDULE playerProjectilesPointer;
private:
    cocos2d::PhysicsWorld *sceneWorld;
    void setPhysicsWorld (cocos2d::PhysicsWorld *world) { sceneWorld=world; };

    Player * player;
    Background* background;
    GameUI* gameUI;
    Level1Boss* boss;

    void update(float dt);

    std::deque<int> movementInputDeck;
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    // MOVE LATER
    void spawnEnemy( float dt , int enemyPos);
    void spawnEnemyType2(float dt, int enemyPos);
    void spawnEnemyType3(float dt);
    void spawnEnemyProjectiles(float dt);
    void spawnEnemyOnTiming(float dt);
    void spawnLaser(Level1Boss* boss);
    void spawnLaserRay(float dt, EnemyType3* ray);
    void spawnLaserRay(Level1Boss* boss);
    void spawnBoss();
    void spawnDefaultProjectile(int n);
    void spawnLaserProjectile(int n);
    void spawnPlayerProjectile(float dt);
    // MOVE LATER
    void levelFinished();
    void gameOver();

    void audioUpdate(float dt);
    int currentTime;
    void initListeners();
    void initPlayer(std::string playerType);
    void initBackground(Director* director);
    void initGameUI(Director* director);
    void initCollisionDetector();
    void initScedulers();
    void startCount();
    void initStart(float dt);
    void bossInit();
};

#endif