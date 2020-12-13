#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__

#include <deque>
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyProjectile.h"
#include "GameController.h"
#include "MainMenuScene.h"
#include "LevelFinishScene.h"
#include "JsonInstance.h"
#include "GameConstants.h"
#include "Boss.h"

class Level : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void dashButtonCallback(cocos2d::Ref* pSender);
    void jumpButtonCallback(cocos2d::Ref* pSender);
    void pauseButtonCallback(cocos2d::Ref* pSender);
    void goToMainMenu(cocos2d::Ref* pSender);
    
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
private:
    cocos2d::PhysicsWorld *sceneWorld;
    void setPhysicsWorld (cocos2d::PhysicsWorld *world) { sceneWorld=world; };

    Player * player;

    void update(float dt);
    // MOVE LATER
    cocos2d::ParallaxNode* paraNodeClose;
    cocos2d::ParallaxNode* paraNodeMid;
    cocos2d::ParallaxNode* paraNodeFar;
    float closeSpeed;
    float midSpeed;
    float farSpeed;

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
    // MOVE LATER
    bool isPaused;
    int totalScore;
    void updateScore(float points);
    // MOVE LATER
    void levelFinished();
    void gameOver();
    // UI
    cocos2d::Menu *pauseMenu;
    cocos2d::Menu *gameUI;
    cocos2d::Sprite *pauseBackground;
    cocos2d::Sprite* progressBarOver;
    ui::LoadingBar* progressBar;

    cocos2d::Label *scoreLabel;
    cocos2d::Label *playerHPLabel;
    ui::LoadingBar *playerHPBar;
    ui::LoadingBar* bossHpBar;

    void audioUpdate(float dt);
    int currentTime;
    void initListeners();
    void initPlayer(Director* director);
    void initBackground(Director* director);
    void initGameUI(Director* director);
    void initPauseMenu(Director* director);
    void initHUD(Director* director);
    void initCollisionDetector();
    void initScedulers();
    void startCount();
    void initStart(float dt);
    void bossInit();
};

#endif