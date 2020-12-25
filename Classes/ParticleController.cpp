#include "ParticleController.h"
#include "GameConstants.h"

void ParticleController::initParticles()
{

}

ParticleSystemQuad* ParticleController::playerDashEnd(Player* player)
{
	auto particles = ParticleSystemQuad::create(GameConstants::getProjectileAssetPath("PLAYER_PARTICLES"));
	particles->setAnchorPoint(Vec2(0.5, 0.5));
	particles->setPosition(Vec2(player->getContentSize().width / 2, player->getContentSize().height / 2));
	particles->setEmitterMode(ParticleSystem::Mode::RADIUS);
	particles->setTotalParticles(10);
	particles->setLife(0.05);
	//particles->setLifeVar(0.2);
	particles->setDuration(0.1);
	particles->setAngleVar(180);
	particles->setStartRadius(20);
	particles->setEndRadius(60);
	particles->setStartColor(Color4F::WHITE);
	particles->setEndColor(Color4F(0, 180, 180, 255));
	particles->setStartSize(15);
	particles->setEndSize(5);

	return particles;
}

ParticleSystemQuad* ParticleController::playerDashStart(Player* player)
{
	auto particles = ParticleSystemQuad::create(GameConstants::getProjectileAssetPath("DEFAULT_PARTICLES"));
	particles->setAnchorPoint(Vec2(0.5, 0.5));
	particles->setPosition(player->getPosition());
	particles->setEmitterMode(ParticleSystem::Mode::RADIUS);
	particles->setTotalParticles(10);
	particles->setLife(0.05);
	//particles->setLifeVar(0.2);
	particles->setDuration(0.1);
	particles->setAngleVar(180);
	particles->setStartRadius(60);
	particles->setEndRadius(20);
	particles->setStartColor(Color4F::WHITE);
	particles->setEndColor(Color4F(0, 180, 180, 255));
	particles->setStartSize(15);
	particles->setEndSize(5);

	return particles;
}

ParticleSystemQuad* ParticleController::onDestroyProjectile(Vec2 pos)
{
	auto particles = ParticleSystemQuad::create(GameConstants::getProjectileAssetPath("DEFAULT_PARTICLES"));
	particles->setAnchorPoint(Vec2::ZERO);
	particles->setPosition(pos);
	particles->setLife(0.2);
	particles->setDuration(0.1);
	particles->setSpeed(100);
	particles->setAngleVar(360);
	return particles;
}

ParticleSystemQuad* ParticleController::onDestroyPlayerProjectile(Vec2 pos)
{
	auto particles = ParticleSystemQuad::create(GameConstants::getProjectileAssetPath("PLAYER_PARTICLES"));
	particles->setAnchorPoint(Vec2::ZERO);
	particles->setPosition(pos);
	particles->setLife(0.2);
	particles->setDuration(0.1);
	particles->setSpeed(100);
	particles->setAngleVar(360);
	return particles;
}

ParticleSystemQuad* ParticleController::onDestroyLaser(Vec2 pos)
{
	auto particles = ParticleSystemQuad::create(GameConstants::getProjectileAssetPath("LASER_PARTICLES"));
	particles->setAnchorPoint(Vec2::ZERO);
	particles->setPosition(pos);
	particles->setLife(0.2);
	particles->setDuration(0.1);
	particles->setSpeed(200);
	particles->setAngleVar(360);
	particles->setStartColor(Color4F::WHITE);
	return particles;
}

ParticleSystemQuad* ParticleController::projectileParticles()
{
	auto particles = ParticleSystemQuad::create(GameConstants::getProjectileAssetPath("DEFAULT_PARTICLES"));
	particles->setAnchorPoint(Vec2::ZERO);
	particles->setPosition(Size(GameConstants::getProjectileAnimationData("DEFAULT_SPRITE_SIZE") / 2, GameConstants::getProjectileAnimationData("DEFAULT_SPRITE_SIZE") / 2));
	particles->setScale(0.3);
	return particles;
}

ParticleSystemQuad* ParticleController::laserParticles()
{
	auto particles = ParticleSystemQuad::create(GameConstants::getProjectileAssetPath("LASER_PARTICLES"));
	particles->setAnchorPoint(Vec2::ZERO);
	particles->setPosition(Size(GameConstants::getProjectileAnimationData("LASER_SPRITE_SIZE_X") / 3, GameConstants::getProjectileAnimationData("LASER_SPRITE_SIZE_Y") / 2));
	particles->setScale(0.3);
	return particles;
}

ParticleSystemQuad* ParticleController::playerProjectileParticles()
{
	auto particles = ParticleSystemQuad::create(GameConstants::getProjectileAssetPath("DEFAULT_PARTICLES"));
	particles->setAnchorPoint(Vec2::ZERO);
	particles->setPosition(Size(GameConstants::getProjectileAnimationData("DEFAULT_SPRITE_SIZE") / 2, GameConstants::getProjectileAnimationData("DEFAULT_SPRITE_SIZE") / 2));
	particles->setScale(0.3);
	return particles;
}