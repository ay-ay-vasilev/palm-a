#ifndef PLAYER_H_
#define PLAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class Player : public cocos2d::Sprite {
public:
	Animate * idleLeftAnimate;
	Animate * idleRightAnimate;
	Animate * runLeftAnimate;
	Animate * runRightAnimate;
	Animate * jumpLeftAnimate;
	Animate * jumpRightAnimate;
	Animate * fallLeftAnimate;
	Animate * fallRightAnimate;
	Animate * flyLeftAnimate;
	Animate * flyRightAnimate;

	static Player * create(void);
	void dash();
	void jump();
	bool jumpKill(float enemyPosY);
	void fall();
	void run(int directionParam);
	void idle();
	void update();
	void giveIFrames(float duration);

	cocos2d::PhysicsBody* getBody();

	int hp;
	int getHP();
	bool damageHP(int dmg);
private:
	~Player();

	bool moving;
	bool dashed;
	int direction;
	float vertForce;
	bool isOnGround;
	int additionalJumps;
	
	bool invincible;
	void removeInvincibility(float dt);

	void playAnimation(Animate* leftAnimation, Animate* rightAnimation);

	void initPlayer();
	void loadAnimations();
	Animate* createAnimation(SpriteFrameCache* spriteCache, std::string numOfFrames, std::string animSpeed, std::string assetName);
};

#endif /* PLAYER_H_ */