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

	static Player * create(void);
	void dash();
	void jump();
	void jumpKill();
	void run(int directionParam);
	void idle();
	void update();

	cocos2d::PhysicsBody* getBody();

	int hp;
	int getHP();
	void updateHP(int dmg);
private:
	~Player();

	bool moving;
	bool dashed;
	int direction;
	float vertForce;
	int jumps;

	void initPlayer();
};

#endif /* PLAYER_H_ */