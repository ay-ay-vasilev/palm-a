#include "Boss.h"
#include "GameController.h"
#include "Definitions.h"

Level1Boss::Level1Boss() {}
Level1Boss::~Level1Boss() {}

Level1Boss* Level1Boss::create()
{
	Level1Boss* boss = new Level1Boss();

	if (boss)
	{
		boss->autorelease();
		boss->model = cocos2d::Sprite::create();
		boss->setAnchorPoint(Vec2(0.5, 0));
		boss->setContentSize(Size(124, 192));
		if (boss->model)
		{
			boss->model->setPosition(Vec2(0, 0));
			boss->model->setAnchorPoint(Vec2(0, 0));
		}
		boss->eye = cocos2d::Sprite::create();
		if (boss->eye)
		{
			boss->eye->setPosition(Vec2(0,0));
			boss->eye->setAnchorPoint(Vec2(0, 0));
		}
		Level1Boss::loadAnimations(boss);
		boss->addChild(boss->model);
		boss->addChild(boss->eye);
		boss->init();
		return boss;
	}
	CC_SAFE_RELEASE(boss->bodyIdleAnimation);
	CC_SAFE_RELEASE(boss->eyeIdleAnimation);
	CC_SAFE_RELEASE(boss);
	return NULL;
}
cocos2d::PhysicsBody* Level1Boss::getBody()
{
	auto physicsBody = PhysicsBody::createBox(Size(this->model->getContentSize().width/3, this->getContentSize().height/6), PHYSICSBODY_MATERIAL_DEFAULT);

	physicsBody->setPositionOffset(Vec2(0, 0));

	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(BOSS_MASK);
	physicsBody->setContactTestBitmask(true);
	return physicsBody;
}
int Level1Boss::getState()
{
	return state;
}
void Level1Boss::setState(int _state)
{
	state = _state;
}
RayProjectile* Level1Boss::getRay()
{
	return ray;
}
void Level1Boss::setRay(RayProjectile* _ray)
{
	ray = _ray;
}
int Level1Boss::getPhase()
{
	return phase;
}
void Level1Boss::setPhase(int _phase)
{
	phase = _phase;
}
void Level1Boss::getDamage(int _dmg)
{
	hp = hp - _dmg;
}
int Level1Boss::getHp() {
	return hp;
}
void Level1Boss::setHp(int _hp)
{
	hp =_hp;
	initialHP = _hp;
}
int Level1Boss::getInitialHp()
{
	return initialHP;

}
void Level1Boss::loadAnimations(Level1Boss* boss)
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile(GameConstants::getBossAssetPath("SPRITE_SHEET"));

	boss->bodyIdleAnimation = Level1Boss::createAnimation(spriteCache, "IDLE_BODY_NUM_OF_FRAMES", "IDLE_BODY_SPEED", "IDLE_BODY");
	boss->bodyIdleAnimation->retain();
	boss->eyeIdleAnimation = Level1Boss::createAnimation(spriteCache, "IDLE_EYE_NUM_OF_FRAMES","IDLE_EYE_SPEED","IDLE_EYE");
	boss->eyeIdleAnimation->retain();

	boss->model->runAction(RepeatForever::create(boss->bodyIdleAnimation));
	boss->eye->runAction(RepeatForever::create(boss->eyeIdleAnimation));
}
cocos2d::Animate* Level1Boss::createAnimation(cocos2d::SpriteFrameCache* spriteCache, std::string numOfFrames, std::string animSpeed, std::string assetName)
{
	auto assetPath = GameConstants::getBossAssetPath(assetName);
	auto numberOfFrames = GameConstants::getBossAnimationData(numOfFrames);
	auto animationSpeed = GameConstants::getBossAnimationData(animSpeed);

	char str[200] = { 0 };
	Vector<SpriteFrame*> animFrames(numberOfFrames);

	for (int i = 1; i <= numberOfFrames; i++)
	{
		sprintf(str, assetPath.c_str(), i);
		auto frame = spriteCache->getSpriteFrameByName(str);
		frame->getTexture()->setAliasTexParameters();
		animFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animFrames, animationSpeed);

	return Animate::create(animation);
}