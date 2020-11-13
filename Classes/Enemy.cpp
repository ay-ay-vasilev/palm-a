#include "Definitions.h"
#include "Enemy.h"
#include "GameController.h"

USING_NS_CC;
Enemy::Enemy(){}
Enemy::~Enemy()
{
	CC_SAFE_RELEASE(idleAnimate);
}
Enemy * Enemy::create(){
    Enemy * enemy = new Enemy();
	if(enemy && enemy->initWithFile("res/enemies/variant/sprites/enemy_2_test_1.png"))
	{
		enemy->autorelease();
		enemy->initEnemy();
		return enemy;
	}

	CC_SAFE_DELETE(enemy);
	return NULL;
}

void Enemy::initEnemy(){
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    char str[200] = {0};
    Vector<SpriteFrame*> idleAnimFrames(ENEMY_ANIM_IDLE_NUM_OF_FRAMES);
	for(int i = 1; i <= ENEMY_ANIM_IDLE_NUM_OF_FRAMES; i++) //Iterate for the number of images you have
	{
		sprintf(str, "res/enemies/variant/sprites/enemy_2_test_%i.png",i);
		auto frame = SpriteFrame::create(str,Rect(0,0, ENEMY_SPRITE_SIZE, ENEMY_SPRITE_SIZE)); //The size of the images in an action should be the same
        frame->getTexture()->setAliasTexParameters();
		idleAnimFrames.pushBack(frame);
	}
    auto idleAnimation = Animation::createWithSpriteFrames(idleAnimFrames, ENEMY_ANIM_IDLE_SPEED);
	idleAnimate = Animate::create(idleAnimation);
	idleAnimate->retain(); //Retain to use it later
	this->runAction(RepeatForever::create(idleAnimate));

}
cocos2d::PhysicsBody* Enemy::getBody()
{
	visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	auto physicsBody = PhysicsBody::createBox( this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	
	physicsBody->setDynamic(false);

	return physicsBody;
}
/*
void Enemy::shoot(float dt)
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto tar = Vec2( origin.x, this->getPosition().y );

    GameController::spawnEnemyProjectile( Vec2( this->getPosition().x - this->getContentSize().width, this->getPosition().y), tar );
}
*/