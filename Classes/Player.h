#ifndef PLAYER_H_
#define PLAYER_H_

#include "cocos2d.h"
#include "Projectiles.h"

USING_NS_CC;

class Player : public cocos2d::Sprite {
public:
	static Player* create(std::string playerType);
	void initPlayer(std::string playerType);

	Animate* idleLeftAnimate;
	Animate* idleRightAnimate;
	Animate* runLeftAnimate;
	Animate* runRightAnimate;
	Animate* jumpLeftAnimate;
	Animate* jumpRightAnimate;
	Animate* fallLeftAnimate;
	Animate* fallRightAnimate;
	Animate* flyLeftAnimate;
	Animate* flyRightAnimate;

	ParticleSystemQuad* jetpackParticles;

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
	bool canShoot();
	bool damageHP(int dmg);
private:
	~Player();

	bool moving;
	bool dashed;
	int direction;
	float vertForce;
	bool isOnGround;
	int additionalJumps;
	bool shoots;

	float dashIFrames;
	float damageIFrames;

	float dashCooldown;
	int dashes;

	bool invincible;
	void removeInvincibility(float dt);
	void replenishDash(float dt);

	void playAnimation(Animate* leftAnimation, Animate* rightAnimation);

	void loadAnimations();
};

#endif /* PLAYER_H_ */