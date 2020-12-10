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

	void removeProjectile(Node *projectile);
    void removeEnemy(EnemyType1 *enemy);
    void removeLaser(Node *laser);
    void removeLaserRay(RayProjectile *ray);
    void removeEnemyType2(EnemyType2 *enemy);
    void removeEnemyType3(EnemyType3* enemy);

    bool onContactBegin ( cocos2d::PhysicsContact &contact );

    int currentTiming;
    int currentEnemy = 0;
    int musicID;
private:
    cocos2d::PhysicsWorld *sceneWorld;
    void setPhysicsWorld (cocos2d::PhysicsWorld *world) { sceneWorld=world; };

    Player * player;

    void update(float dt);

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

    void spawnEnemy( float dt , int enemyPos);
    void spawnEnemyType2(float dt, int enemyPos);
    void spawnEnemyType3(float dt);
    void spawnEnemyProjectiles(float dt);
    void spawnEnemyOnTiming(float dt);
    void spawnLaserRay(float dt, EnemyType3* ray);
    void spawnLaserRay(Level1Boss* boss);
    void spawnBoss();

    bool isPaused;
    int remainingTime;
    void updateScore(float points);

    void levelFinished();
    void gameOver();

    cocos2d::Menu *pauseMenu;
    cocos2d::Menu *gameUI;
    cocos2d::Sprite *pauseBackground;
    ui::LoadingBar* progressBar;

    cocos2d::Label *scoreLabel;
    cocos2d::Label *playerHPLabel;
    ui::LoadingBar *playerHPBar;

    void audioUpdate(float dt);
    int currentTime;
};

#endif