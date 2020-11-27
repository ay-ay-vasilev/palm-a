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

class Level : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void dashButtonCallback(cocos2d::Ref* pSender);
    void pauseButtonCallback(cocos2d::Ref* pSender);
    void goToMainMenu(cocos2d::Ref* pSender);
    
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
    
    void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    std::deque<int> movementInputDeck;

    void spawnEnemy( float dt );
    void spawnEnemyProjectiles(float dt);

    bool isPaused;
    int score;
    void updateScore(float points);


    cocos2d::Menu *pauseMenu;
    cocos2d::Menu *gameUI;
    cocos2d::Sprite *pauseBackground;

    cocos2d::Label *scoreLabel;
    cocos2d::Label *playerHPLabel;
    ui::LoadingBar *playerHPBar;
};

#endif
