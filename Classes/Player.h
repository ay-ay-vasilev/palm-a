#ifndef PLAYER_H_
#define PLAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class Player : public cocos2d::Sprite {
public:
	Animate * idleAnimate;
	Animate * runAnimate;

	static Player * create(void);
	void run(int directionParam);
	void idle();

	void update();

private:
	~Player();

	bool moving;
	int direction;

	void initPlayer();
};

#endif /* PLAYER_H_ */