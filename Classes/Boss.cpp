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
		boss->playAnimation(boss->bodyIdleAnimation, boss->eyeIdleAnimation);
		boss->addChild(boss->model);
		boss->addChild(boss->eye);
		boss->init();
		boss->firstAttackStarted = false;
		boss->firstAttackEnded = false;
		boss->secondAttackStarted = false;
		boss->secondAttackEnded = false;
		boss->lookDirection = 1;
		boss->setState(0);
		boss->setPhase(1);
		return boss;
	}
	//CC_SAFE_RELEASE(boss->bodyIdleAnimation);
	//CC_SAFE_RELEASE(boss->eyeIdleAnimation);
	CC_SAFE_DELETE(boss);
	return NULL;
}
cocos2d::PhysicsBody* Level1Boss::getBody()
{
	auto physicsBody = PhysicsBody::createBox(Size(this->getContentSize().width/3, this->getContentSize().height/6), PHYSICSBODY_MATERIAL_DEFAULT);

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
void Level1Boss::moveLeft()
{
	this->setPosition(Vec2(this->getPosition().x - speed * RESOLUTION_VARIABLE, this->getPosition().y));
}
void Level1Boss::moveRight()
{
	this->setPosition(Vec2(this->getPosition().x + speed * RESOLUTION_VARIABLE, this->getPosition().y));
}
void Level1Boss::setSpeed(float _speed)
{
	speed = _speed;
}
float Level1Boss::getSpeed()
{
	return speed;
}
void Level1Boss::updateRay()
{
	//find correct position for ray later
	this->getRay()->setPosition(Vec2(this->getPosition().x, this->getPosition().y + this->getRay()->getContentSize().width / 5));
}
void Level1Boss::setRayTurningSpeed(float _speed)
{
	rayTurningSpeed = _speed;
}
float Level1Boss::getRayTurningSpeed()
{
	return rayTurningSpeed;
}
void Level1Boss::turnRayLeft()
{
	this->getRay()->setRotation(this->getRay()->getRotation() - rayTurningSpeed);
}
void Level1Boss::turnRayRight()
{
	this->getRay()->setRotation(this->getRay()->getRotation() + rayTurningSpeed);
}
void Level1Boss::removeRay()
{
	Level::getInstance()->removeLaserRay(this->getRay());
}
void Level1Boss::loadAnimations(Level1Boss* boss)
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile(GameConstants::getBossAssetPath("SPRITE_SHEET"));

	boss->bodyIdleAnimation = Level1Boss::createAnimation(spriteCache, "IDLE_BODY_NUM_OF_FRAMES", "IDLE_BODY_SPEED", "IDLE_BODY");
	boss->eyeIdleAnimation = Level1Boss::createAnimation(spriteCache, "IDLE_EYE_NUM_OF_FRAMES","IDLE_EYE_SPEED","IDLE_EYE");
	
	boss->firstAttack_start = Level1Boss::createAnimation(spriteCache, "FIRST_ATTACK_START_NUM_OF_FRAMES", "FIRST_ATTACK_START_SPEED", "FIRST_ATTACK_START");
	boss->firstAttack_attack = Level1Boss::createAnimation(spriteCache, "FIRST_ATTACK_ATTACK_NUM_OF_FRAMES", "FIRST_ATTACK_ATTACK_SPEED", "FIRST_ATTACK_ATTACK");
	boss->firstAttack_end = Level1Boss::createAnimation(spriteCache, "FIRST_ATTACK_END_NUM_OF_FRAMES", "FIRST_ATTACK_END_SPEED", "FIRST_ATTACK_END");
	
	boss->secondAttack_start = Level1Boss::createAnimation(spriteCache, "SECOND_ATTACK_START_NUM_OF_FRAMES", "SECOND_ATTACK_START_SPEED", "SECOND_ATTACK_START");
	boss->secondAttack_leftRight = Level1Boss::createAnimation(spriteCache, "SECOND_ATTACK_LEFT_TO_RIGHT_NUM_OF_FRAMES", "SECOND_ATTACK_LEFT_TO_RIGHT_SPEED", "SECOND_ATTACK_LEFT_RIGHT");
	boss->secondAttack_rightLeft = Level1Boss::createAnimation(spriteCache, "SECOND_ATTACK_RIGHT_TO_LEFT_NUM_OF_FRAMES", "SECOND_ATTACK_RIGHT_TO_LEFT_SPEED", "SECOND_ATTACK_RIGHT_LEFT");
	boss->secondAttack_end = Level1Boss::createAnimation(spriteCache, "SECOND_ATTACK_END_NUM_OF_FRAMES", "SECOND_ATTACK_END_SPEED", "SECOND_ATTACK_END");

	boss->bodyIdleAnimation->retain();
	boss->eyeIdleAnimation->retain();
	
	boss->firstAttack_start->retain();
	boss->firstAttack_attack->retain();
	boss->firstAttack_end->retain();

	boss->secondAttack_start->retain();
	boss->secondAttack_leftRight->retain();
	boss->secondAttack_rightLeft->retain();
	boss->secondAttack_end->retain();
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
void Level1Boss::playAnimation(Animate* animation)
{
	RepeatForever* newAnimation;
	this->model->stopActionByTag(ANIMATION_TAG);

	newAnimation = RepeatForever::create(animation);
	newAnimation->setTag(ANIMATION_TAG);
	this->model->runAction(newAnimation);
}
void Level1Boss::playAnimation(Animate* animation, Animate* eyeAnimation)
{
	RepeatForever* newAnimation;
	RepeatForever* newEyeAnimation;
	this->stopAllActionsByTag(ANIMATION_TAG);

	newAnimation = RepeatForever::create(animation);
	newEyeAnimation = RepeatForever::create(eyeAnimation);
	newAnimation->setTag(ANIMATION_TAG);
	newEyeAnimation->setTag(ANIMATION_TAG);

	this->model->runAction(newAnimation);
	this->eye->runAction(newEyeAnimation);
}
void Level1Boss::startFirstAttack()
{
	this->model->stopActionByTag(ANIMATION_TAG);
	this->eye->stopActionByTag(ANIMATION_TAG);
	this->eye->setOpacity(0);

	auto startAnimation = this->firstAttack_start;

	auto attackAnimation = RepeatForever::create(this->firstAttack_attack);

	auto sequence = Sequence::create(startAnimation, attackAnimation, NULL);
	sequence->setTag(ANIMATION_TAG);

	this->model->runAction(sequence);
}
void Level1Boss::endFirstAttack()
{
	this->model->stopActionByTag(ANIMATION_TAG);

	this->loadAnimations(this);

	auto endAnimation = this->firstAttack_end;
	auto bodyAnimation = RepeatForever::create(this->bodyIdleAnimation);

	auto eyeAnimation = RepeatForever::create(this->eyeIdleAnimation);
	auto delay = DelayTime::create(GameConstants::getBossAnimationData("FIRST_ATTACK_END_NUM_OF_FRAMES")*GameConstants::getBossAnimationData("FIRST_ATTACK_END_SPEED"));
	auto eyeOpacity = CallFunc::create([this]() {this->eye->setOpacity(100); });

	auto bodySequence = Sequence::create(endAnimation, bodyAnimation, NULL);
	auto eyeSequence = Sequence::create(delay,eyeOpacity, eyeAnimation, NULL);

	bodySequence->setTag(ANIMATION_TAG);
	eyeSequence->setTag(ANIMATION_TAG);

	this->model->runAction(bodySequence);
	this->eye->runAction(eyeSequence);
}
void Level1Boss::startSecondAttack()
{
	this->model->stopActionByTag(ANIMATION_TAG);
	this->eye->stopActionByTag(ANIMATION_TAG);
	this->eye->setOpacity(0);
	auto startAnimation = this->secondAttack_start;

	startAnimation->setTag(ANIMATION_TAG);

	this->model->runAction(startAnimation);
}
void Level1Boss::lookLeft()
{
	playAnimation(this->secondAttack_leftRight);
}
void Level1Boss::lookRight()
{
	playAnimation(this->secondAttack_rightLeft);
}
void Level1Boss::endSecondAttack()
{
	this->model->stopActionByTag(ANIMATION_TAG);

	this->loadAnimations(this);

	auto endAnimation = this->secondAttack_end;
	auto bodyAnimation = RepeatForever::create(this->bodyIdleAnimation);
	auto eyeOpacity = CallFunc::create([this]() {this->eye->setOpacity(100); });

	auto eyeAnimation = RepeatForever::create(this->eyeIdleAnimation);
	auto delay = DelayTime::create(GameConstants::getBossAnimationData("SECOND_ATTACK_END_NUM_OF_FRAMES") * GameConstants::getBossAnimationData("SECOND_ATTACK_END_SPEED"));

	auto bodySequence = Sequence::create(endAnimation, bodyAnimation, NULL);
	auto eyeSequence = Sequence::create(delay, eyeOpacity, eyeAnimation, NULL);

	bodySequence->setTag(ANIMATION_TAG);
	eyeSequence->setTag(ANIMATION_TAG);

	this->model->runAction(bodySequence);
	this->eye->runAction(eyeSequence);
}