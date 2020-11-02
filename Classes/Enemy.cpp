#include "Definitions.h"
#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy(){
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
}

void Enemy::SpawnEnemy(cocos2d::Scene *level){

    auto enemy = Sprite::create("res/enemy/enemy_test_sprite.png");

    enemy->setScale(4.0);

    enemy->getTexture()->setAliasTexParameters();

    //auto enemyBody = PhysicsBody::createBox( enemy->getContentSize());

    //enemyBody->setDynamic(false);

    //enemy->setPhysicsBody(enemyBody);

    auto random = CCRANDOM_0_1();
    if (random<0.33){
        random=0.25;
    } else if (random<0.66) {
        random=0.5;
    }else{
        random=0.75;
    }
    auto enemyPosition= (random * visibleSize.width) + (enemy->getContentSize().width / 2); 
    
    enemy->setPosition(Vec2(enemyPosition, visibleSize.height + enemy->getContentSize().height + origin.y));

    level->addChild(enemy);
    
    auto enemyAction = MoveBy::create(ENEMY_SPEED, Vec2(0, -1*visibleSize.height*1.5));

    enemy->runAction(enemyAction);
    
}