#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__

#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyProjectile.h"
#include "GameController.h"

class Level : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void dashButtonCallback(cocos2d::Ref* pSender);
    void pauseButtonCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Level);

	void removeProjectile( EnemyProjectile *enemyProjectile ) ;
    void removeEnemy(Enemy *enemy);

    bool onContactBegin ( cocos2d::PhysicsContact &contact );
private:
    cocos2d::PhysicsWorld *sceneWorld;
    void setPhysicsWorld (cocos2d::PhysicsWorld *world) { sceneWorld=world; };

    Player * player;

    void update(float dt);

    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

    void spawnEnemy( float dt );
    void spawnEnemyProjectiles(float dt);

    bool isPaused;
    int score;
    void updateScore(int points);

    cocos2d::Label *playerHPLabel;
    ui::LoadingBar *playerHPBar;
};

#endif
