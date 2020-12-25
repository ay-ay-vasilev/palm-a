#include "cocos2d.h"
#include "Player.h"
USING_NS_CC;

class ParticleController
{
public:
	
	static void initParticles();
	
	static cocos2d::ParticleSystemQuad* playerDashEnd(Player* player);
	static cocos2d::ParticleSystemQuad* playerDashStart(Player* player);

	static cocos2d::ParticleSystemQuad* onDestroyProjectile(Vec2 pos);
	static cocos2d::ParticleSystemQuad* onDestroyLaser(Vec2 pos);
	static cocos2d::ParticleSystemQuad* onDestroyPlayerProjectile(Vec2 pos);

	static cocos2d::ParticleSystemQuad* projectileParticles();
	static cocos2d::ParticleSystemQuad* laserParticles();
	static cocos2d::ParticleSystemQuad* playerProjectileParticles();




};