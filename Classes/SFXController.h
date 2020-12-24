#include "cocos2d.h"
#include "AudioEngine.h"

class SFXController
{
public:
	static void preloadSFX();

	static void enemyJumpKilled();
	static void enemyShotKilled();
	static void enemyProjectile();
	static void enemyLaser();
	static void enemyRay();

	static void playerDmg();
	static void playerDash();
	static void playerJump();
	static void playerJetpack();
	static void playerProjectile();

};