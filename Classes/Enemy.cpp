#include "Definitions.h"
#include "Enemy.h"

USING_NS_CC;

Enemy::~Enemy()
{
	CC_SAFE_RELEASE(idleAnimate);
}
Enemy * Enemy::create(){
    Enemy * enemy = new Enemy();
	if(enemy && enemy->initWithFile("res/character/idle/sprites/character_unarmed_idle_left_test_1.png"))
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
    Vector<SpriteFrame*> idleAnimFrames(5);
	for(int i = 1; i <= 5; i++) //Iterate for the number of images you have
	{
		sprintf(str, "res/enemies/variant/sprites/enemy_2_test_%i.png",i);
		auto frame = SpriteFrame::create(str,Rect(0,0,112,112)); //The size of the images in an action should be the same
        frame->getTexture()->setAliasTexParameters();
		idleAnimFrames.pushBack(frame);
	}
    auto idleAnimation = Animation::createWithSpriteFrames(idleAnimFrames, 0.1f);
	idleAnimate = Animate::create(idleAnimation);
	idleAnimate->retain(); //Retain to use it later
	this->runAction(RepeatForever::create(idleAnimate));
}