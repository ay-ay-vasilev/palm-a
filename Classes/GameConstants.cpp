#include "GameConstants.h"
#include "Definitions.h"

std::map<std::string, std::string> GameConstants::playerAssetPaths = {};
std::map<std::string, float> GameConstants::playerAnimationData = {};
std::map<std::string, float> GameConstants::playerStats = {};
std::map<std::string, std::string> GameConstants::enemyAssetPaths = {};
std::map<std::string, float> GameConstants::enemyAnimationData = {};
std::map<std::string, float> GameConstants::enemyStats = {};
std::map<std::string, std::string> GameConstants::projectileAssetPaths = {};
std::map<std::string, float> GameConstants::projectileAnimationData = {};
std::map<std::string, float> GameConstants::projectileStats = {};

std::map<std::string, float> GameConstants::levelStats = {};

float GameConstants::resolution = 2;

void GameConstants::initConstants(std::string levelName)
{
	resolution = JsonInstance::GetInstance()->GetData("balance")["debug"]["resolution"];

	if (levelName == "level1")
	{
		setPlayerAssetPath("SPRITE_SHEET", "spriteSheet");
		setPlayerAssetPath("UNARMED_IDLE_LEFT", "idleUnarmedLeft");
		setPlayerAssetPath("UNARMED_IDLE_RIGHT", "idleUnarmedRight");
		setPlayerAssetPath("UNARMED_RUN_LEFT", "runUnarmedLeft");
		setPlayerAssetPath("UNARMED_RUN_RIGHT", "runUnarmedRight");
		setPlayerAssetPath("UNARMED_JUMP_LEFT", "jumpUnarmedLeft");
		setPlayerAssetPath("UNARMED_JUMP_RIGHT", "jumpUnarmedRight");
		setPlayerAssetPath("UNARMED_FALL_LEFT", "fallUnarmedLeft");
		setPlayerAssetPath("UNARMED_FALL_RIGHT", "fallUnarmedRight");
		setPlayerAnimationData("IDLE_NUM_OF_FRAMES", "idleFrames");
		setPlayerAnimationData("RUN_NUM_OF_FRAMES", "runFrames");
		setPlayerAnimationData("JUMP_NUM_OF_FRAMES", "jumpFrames");
		setPlayerAnimationData("FALL_NUM_OF_FRAMES", "fallFrames");
		setPlayerAnimationData("IDLE_SPEED", "idleAnimSpeed");
		setPlayerAnimationData("RUN_SPEED", "runAnimSpeed");
		setPlayerAnimationData("JUMP_SPEED", "jumpAnimSpeed");
		setPlayerAnimationData("FALL_SPEED", "fallAnimSpeed");
		setPlayerAnimationData("SPRITE_SIZE", "spriteSize");
		setPlayerStats("SPEED", "speed", MULT_BY_RESOLUTION);
		setPlayerStats("DASH_SPEED", "dashSpeed", MULT_BY_RESOLUTION);
		setPlayerStats("JUMP_FORCE", "jumpForce", MULT_BY_RESOLUTION);
		setPlayerStats("GRAVITY", "gravity", MULT_BY_RESOLUTION);
		setPlayerStats("MAX_FALL_SPEED", "maxFallSpeed", MULT_BY_RESOLUTION);
		setPlayerStats("MAX_JUMP_SPEED", "maxJumpSpeed", MULT_BY_RESOLUTION);
		setPlayerStats("START_HP", "hp", NOT_MULT_BY_RESOLUTION);
		setPlayerStats("ADDITIONAL_JUMPS", "additionalJumps", NOT_MULT_BY_RESOLUTION);
		setPlayerStats("JUMP_KILL_FORCE", "jumpKillForce", MULT_BY_RESOLUTION);

		setEnemyAssetPath("REGULAR_SPRITE_SHEET", "regular", "spriteSheet");
		setEnemyAssetPath("REGULAR_IDLE_LEFT", "regular", "idleLeft");
		setEnemyAssetPath("REGULAR_IDLE_RIGHT", "regular", "idleRight");
		setEnemyAnimationData("REGULAR_IDLE_NUM_OF_FRAMES", "regular", "animationFramesNumber");
		setEnemyAnimationData("REGULAR_IDLE_SPEED", "regular", "animationSpeed");
		setEnemyAnimationData("REGULAR_SPRITE_SIZE", "regular", "spriteSize");
		setEnemyAssetPath("LASER_SPRITE_SHEET", "laser", "spriteSheet");
		setEnemyAssetPath("LASER_IDLE_LEFT", "laser", "idleLeft");
		setEnemyAssetPath("LASER_IDLE_RIGHT", "laser", "idleRight");
		setEnemyAnimationData("LASER_IDLE_NUM_OF_FRAMES", "laser", "animationFramesNumber");
		setEnemyAnimationData("LASER_IDLE_SPEED", "laser", "animationSpeed");
		setEnemyAnimationData("LASER_SPRITE_SIZE", "laser", "spriteSize");
		setEnemyAssetPath("TURRET_SPRITE_SHEET", "turret", "spriteSheet");
		setEnemyAssetPath("TURRET_IDLE", "turret", "idle");
		setEnemyAnimationData("TURRET_IDLE_NUM_OF_FRAMES", "turret", "animationFramesNumber");
		setEnemyAnimationData("TURRET_IDLE_SPEED", "turret", "animationSpeed");
		setEnemyAnimationData("TURRET_SPRITE_SIZE", "turret", "spriteSize");

		setProjectileAssetPath("DEFAULT_SPRITE_SHEET", "default", "spriteSheet");
		setProjectileAssetPath("DEFAULT_SPRITE", "default", "sprite");
		setProjectileAnimationData("DEFAULT_NUM_OF_FRAMES", "default", "animationFramesNumber");
		setProjectileAnimationData("DEFAULT_SPEED", "default", "animationSpeed");
		setProjectileAnimationData("DEFAULT_SPRITE_SIZE", "default", "spriteSize");
		setProjectileAssetPath("LASER_SPRITE_SHEET", "laser", "spriteSheet");
		setProjectileAssetPath("LASER_SPRITE", "laser", "sprite");
		setProjectileAnimationData("LASER_NUM_OF_FRAMES", "laser", "animationFramesNumber");
		setProjectileAnimationData("LASER_SPEED", "laser", "animationSpeed");
		setProjectileAnimationData("LASER_SPRITE_SIZE_X", "laser", "spriteSizeX");
		setProjectileAnimationData("LASER_SPRITE_SIZE_Y", "laser", "spriteSizeY");
		setProjectileAssetPath("RAY_SPRITE_SHEET", "ray", "spriteSheet");
		setProjectileAssetPath("RAY_SPRITE", "ray", "sprite");
		setProjectileAnimationData("RAY_NUM_OF_FRAMES", "ray", "animationFramesNumber");
		setProjectileAnimationData("RAY_SPEED", "ray", "animationSpeed");
		setProjectileAnimationData("RAY_SPRITE_SIZE_X", "ray", "spriteSizeX");
		setProjectileAnimationData("RAY_SPRITE_SIZE_Y", "ray", "spriteSizeY");



		setLevelStats("WALL_DISTANCE", "wallDistance", MULT_BY_RESOLUTION);
		setLevelStats("FLOOR_HEIGHT", "floorHeight", MULT_BY_RESOLUTION);
		setLevelStats("DURATION", "levelDuration", NOT_MULT_BY_RESOLUTION);

	}
}

// ============================================= GETTERS =============================================
std::string GameConstants::getPlayerAssetPath(const std::string& key)
{
	return playerAssetPaths[key];
}
float GameConstants::getPlayerAnimationData(const std::string& key)
{
	return playerAnimationData[key];
}
float GameConstants::getPlayerStats(const std::string& key)
{
	return playerStats[key];
}
std::string GameConstants::getEnemyAssetPath(const std::string& key)
{
	return enemyAssetPaths[key];
}
float GameConstants::getEnemyAnimationData(const std::string& key)
{
	return enemyAnimationData[key];
}
float GameConstants::getEnemyStats(const std::string& key)
{
	return enemyStats[key];
}
std::string GameConstants::getProjectileAssetPath(const std::string& key)
{
	return projectileAssetPaths[key];
}
float GameConstants::getProjectileAnimationData(const std::string& key)
{
	return projectileAnimationData[key];
}
float GameConstants::getProjectileStats(const std::string& key)
{
	return projectileStats[key];
}
float GameConstants::getLevelStats(const std::string& key)
{
	return levelStats[key];
}


// ============================================= SETTERS =============================================
void GameConstants::setPlayerAssetPath(const std::string& key, const std::string& assetName)
{
	playerAssetPaths[key] = JsonInstance::GetInstance()->GetData("assetPaths")["player"][assetName];
}
void GameConstants::setPlayerAnimationData(const std::string& key, const std::string& dataName)
{
	playerAnimationData[key] = JsonInstance::GetInstance()->GetData("animations")["playerAnim"][dataName];
}
void GameConstants::setPlayerStats(const std::string& key, const std::string& dataName, const bool multByResolution)
{
	playerStats[key] = JsonInstance::GetInstance()->GetData("balance")["player"][dataName];
	if (multByResolution)
	{
		playerStats[key] *= GameConstants::resolution;
	}
}
void GameConstants::setEnemyAssetPath(const std::string& key, const std::string& type, const std::string& assetName)
{
	enemyAssetPaths[key] = JsonInstance::GetInstance()->GetData("assetPaths")["enemy"][type][assetName];
}
void GameConstants::setEnemyAnimationData(const std::string& key, const std::string& type, const std::string& dataName)
{
	enemyAnimationData[key] = JsonInstance::GetInstance()->GetData("animations")["enemyAnim"][type][dataName];
}
void GameConstants::setEnemyStats(const std::string& key, const std::string& type, const std::string& dataName, const bool multByResolution)
{
	enemyStats[key] = JsonInstance::GetInstance()->GetData("balance")["enemy"][type][dataName];
	if (multByResolution)
	{
		enemyStats[key] *= GameConstants::resolution;
	}
}
void GameConstants::setProjectileAssetPath(const std::string& key, const std::string& type, const std::string& assetName)
{
	projectileAssetPaths[key] = JsonInstance::GetInstance()->GetData("assetPaths")["projectile"][type][assetName];
}
void GameConstants::setProjectileAnimationData(const std::string& key, const std::string& type, const std::string& dataName)
{
	projectileAnimationData[key] = JsonInstance::GetInstance()->GetData("animations")["projectileAnim"][type][dataName];
}
void GameConstants::setProjectileStats(const std::string& key, const std::string& type, const std::string& dataName, const bool multByResolution)
{
	projectileStats[key] = JsonInstance::GetInstance()->GetData("balance")["projectile"][type][dataName];
	if (multByResolution)
	{
		projectileStats[key] *= GameConstants::resolution;
	}
}

void GameConstants::setLevelStats(const std::string& key, const std::string& dataName, const bool multByResolution)
{
	levelStats[key] = JsonInstance::GetInstance()->GetData("balance")["level"][dataName];
	if (multByResolution)
	{
		levelStats[key] *= GameConstants::resolution;
	}
}
