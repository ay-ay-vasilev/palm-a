#include "SFXController.h"
#include "GameConstants.h"

void SFXController::preloadSFX()
{	
	cocos2d::AudioEngine::preload(GameConstants::getSfxPath("PLAYER_DMG_SFX"));
	cocos2d::AudioEngine::preload(GameConstants::getSfxPath("PLAYER_DASH_SFX"));
	cocos2d::AudioEngine::preload(GameConstants::getSfxPath("PLAYER_JUMP_SFX"));
	cocos2d::AudioEngine::preload(GameConstants::getSfxPath("PLAYER_JETPACK_SFX"));
	cocos2d::AudioEngine::preload(GameConstants::getSfxPath("PLAYER_PROJECTILE_SFX"));

	cocos2d::AudioEngine::preload(GameConstants::getSfxPath("ENEMY_CRUSHED_SFX"));
	cocos2d::AudioEngine::preload(GameConstants::getSfxPath("ENEMY_SHOT_SFX"));
	cocos2d::AudioEngine::preload(GameConstants::getSfxPath("ENEMY_PROJECTILE_SFX"));
	cocos2d::AudioEngine::preload(GameConstants::getSfxPath("ENEMY_LASER_SFX"));
	cocos2d::AudioEngine::preload(GameConstants::getSfxPath("ENEMY_RAY_SFX"));
}

void SFXController::enemyJumpKilled()
{
	cocos2d::AudioEngine::play2d(GameConstants::getSfxPath("ENEMY_CRUSHED_SFX"), false, 0.4);
}
void SFXController::enemyShotKilled()
{
	cocos2d::AudioEngine::play2d(GameConstants::getSfxPath("ENEMY_SHOT_SFX"), false, 0.15);
}
void SFXController::enemyProjectile()
{
	cocos2d::AudioEngine::play2d(GameConstants::getSfxPath("ENEMY_PROJECTILE_SFX"), false, 0.1);
}
void SFXController::enemyLaser()
{
	cocos2d::AudioEngine::play2d(GameConstants::getSfxPath("ENEMY_LASER_SFX"), false, 0.02);
}
void SFXController::enemyRay()
{
	cocos2d::AudioEngine::play2d(GameConstants::getSfxPath("ENEMY_RAY_SFX"), false, 0.2);
}

void SFXController::playerDmg()
{
	cocos2d::AudioEngine::play2d(GameConstants::getSfxPath("PLAYER_DMG_SFX"), false, 0.1);
}
void SFXController::playerDash()
{
	cocos2d::AudioEngine::play2d(GameConstants::getSfxPath("PLAYER_DASH_SFX"), false, 0.3);
}
void SFXController::playerJump()
{
	cocos2d::AudioEngine::play2d(GameConstants::getSfxPath("PLAYER_JUMP_SFX"), false, 0.3);
}
void SFXController::playerJetpack()
{
	cocos2d::AudioEngine::play2d(GameConstants::getSfxPath("PLAYER_JETPACK_SFX"), false, 0.3);
}
void SFXController::playerProjectile()
{
	cocos2d::AudioEngine::play2d(GameConstants::getSfxPath("PLAYER_PROJECTILE_SFX"), false, 0.2);
}