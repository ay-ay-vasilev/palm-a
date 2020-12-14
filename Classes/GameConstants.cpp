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
	JsonInstance::ReloadFiles();

	resolution = JsonInstance::GetInstance()->GetData("balance")["debug"]["resolution"];

	if (levelName == "level1")
	{
		setEnemyAssetPath("REGULAR_SPRITE_SHEET", "regular", "spriteSheet");
		setEnemyAssetPath("REGULAR_IDLE_LEFT", "regular", "idleLeft");
		setEnemyAssetPath("REGULAR_IDLE_RIGHT", "regular", "idleRight");
		setEnemyAnimationData("REGULAR_IDLE_NUM_OF_FRAMES", "regular", "animationFramesNumber");
		setEnemyAnimationData("REGULAR_IDLE_SPEED", "regular", "animationSpeed");
		setEnemyAnimationData("REGULAR_SPRITE_SIZE", "regular", "spriteSize");
		setEnemyStats("REGULAR_SPEED", "regular", "speed", MULT_BY_RESOLUTION);
		setEnemyStats("REGULAR_COLLIDE_DAMAGE", "regular", "collideDamage", NOT_MULT_BY_RESOLUTION);
		setEnemyStats("REGULAR_SPAWN_FREQ", "regular", "spawnFrequency", NOT_MULT_BY_RESOLUTION);
			
		setEnemyAssetPath("LASER_SPRITE_SHEET", "laser", "spriteSheet");
		setEnemyAssetPath("LASER_IDLE_LEFT", "laser", "idleLeft");
		setEnemyAssetPath("LASER_IDLE_RIGHT", "laser", "idleRight");
		setEnemyAnimationData("LASER_IDLE_NUM_OF_FRAMES", "laser", "animationFramesNumber");
		setEnemyAnimationData("LASER_IDLE_SPEED", "laser", "animationSpeed");
		setEnemyAnimationData("LASER_SPRITE_SIZE", "laser", "spriteSize");
		setEnemyStats("LASER_SPEED", "laser", "speed", MULT_BY_RESOLUTION);
		setEnemyStats("LASER_COLLIDE_DAMAGE", "laser", "collideDamage", NOT_MULT_BY_RESOLUTION);
		setEnemyStats("LASER_SPAWN_FREQ", "laser", "spawnFrequency", NOT_MULT_BY_RESOLUTION);

		setEnemyAssetPath("TURRET_SPRITE_SHEET", "turret", "spriteSheet");
		setEnemyAssetPath("TURRET_IDLE", "turret", "idle");
		setEnemyAnimationData("TURRET_IDLE_NUM_OF_FRAMES", "turret", "animationFramesNumber");
		setEnemyAnimationData("TURRET_IDLE_SPEED", "turret", "animationSpeed");
		setEnemyAnimationData("TURRET_SPRITE_SIZE", "turret", "spriteSize");
		setEnemyStats("TURRET_SPEED", "turret", "speed", MULT_BY_RESOLUTION);
		setEnemyStats("TURRET_COLLIDE_DAMAGE", "turret", "collideDamage", NOT_MULT_BY_RESOLUTION);
		setEnemyStats("TURRET_SPAWN_FREQ", "turret", "spawnFrequency", NOT_MULT_BY_RESOLUTION);

		setProjectileAssetPath("DEFAULT_SPRITE_SHEET", "default", "spriteSheet");
		setProjectileAssetPath("DEFAULT_PARTICLES", "default", "particles");
		setProjectileAssetPath("DEFAULT_SPRITE", "default", "sprite");
		setProjectileAnimationData("DEFAULT_NUM_OF_FRAMES", "default", "animationFramesNumber");
		setProjectileAnimationData("DEFAULT_SPEED", "default", "animationSpeed");
		setProjectileAnimationData("DEFAULT_SPRITE_SIZE", "default", "spriteSize");

		setProjectileAssetPath("LASER_SPRITE_SHEET", "laser", "spriteSheet");
		setProjectileAssetPath("LASER_PARTICLES", "laser", "particles");
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

		setProjectileStats("DEFAULT_DAMAGE", "default", "damage", NOT_MULT_BY_RESOLUTION);
		setProjectileStats("DEFAULT_SPEED", "default", "speed", MULT_BY_RESOLUTION);
		setProjectileStats("LASER_DAMAGE", "laser", "damage", NOT_MULT_BY_RESOLUTION);
		setProjectileStats("LASER_SPEED", "laser", "speed", MULT_BY_RESOLUTION);
		setProjectileStats("RAY_DAMAGE", "ray", "damage", MULT_BY_RESOLUTION);
		setProjectileStats("PLAYER_DAMAGE", "player", "damage", NOT_MULT_BY_RESOLUTION);
		setProjectileStats("PLAYER_SPEED", "player", "speed", MULT_BY_RESOLUTION);

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
void GameConstants::setPlayerAssetPath(const std::string& key, const std::string& assetName, const std::string& playerType)
{
	playerAssetPaths[key] = JsonInstance::GetInstance()->GetData("assetPaths")["player"][playerType][assetName];
}
void GameConstants::setPlayerAnimationData(const std::string& key, const std::string& dataName, const std::string& playerType)
{
	playerAnimationData[key] = JsonInstance::GetInstance()->GetData("animations")["playerAnim"][playerType][dataName];
}
void GameConstants::setPlayerStats(const std::string& playerType, const std::string& key, const std::string& dataName, const bool multByResolution)
{
	playerStats[key] = JsonInstance::GetInstance()->GetData("balance")["player"][playerType][dataName];
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


// ============================================= LOAD OBJECT ==============================================
void GameConstants::loadPlayer(const std::string& playerType)
{
	setPlayerAssetPath("SPRITE_SHEET", "spriteSheet", playerType);

	setPlayerAssetPath("IDLE_LEFT", "idleLeft", playerType);
	setPlayerAssetPath("IDLE_RIGHT", "idleRight", playerType);
	setPlayerAssetPath("RUN_LEFT", "runLeft", playerType);
	setPlayerAssetPath("RUN_RIGHT", "runRight", playerType);
	setPlayerAssetPath("JUMP_LEFT", "jumpLeft", playerType);
	setPlayerAssetPath("JUMP_RIGHT", "jumpRight", playerType);
	setPlayerAssetPath("FALL_LEFT", "fallLeft", playerType);
	setPlayerAssetPath("FALL_RIGHT", "fallRight", playerType);
	setPlayerAssetPath("FLY_LEFT", "flyLeft", playerType);
	setPlayerAssetPath("FLY_RIGHT", "flyRight", playerType);

	setPlayerAnimationData("IDLE_NUM_OF_FRAMES", "idleFrames", playerType);
	setPlayerAnimationData("RUN_NUM_OF_FRAMES", "runFrames", playerType);
	setPlayerAnimationData("JUMP_NUM_OF_FRAMES", "jumpFrames", playerType);
	setPlayerAnimationData("FALL_NUM_OF_FRAMES", "fallFrames", playerType);
	setPlayerAnimationData("FLY_NUM_OF_FRAMES", "flyFrames", playerType);
	setPlayerAnimationData("IDLE_SPEED", "idleAnimSpeed", playerType);
	setPlayerAnimationData("RUN_SPEED", "runAnimSpeed", playerType);
	setPlayerAnimationData("JUMP_SPEED", "jumpAnimSpeed", playerType);
	setPlayerAnimationData("FALL_SPEED", "fallAnimSpeed", playerType);
	setPlayerAnimationData("FLY_SPEED", "flyAnimSpeed", playerType);
	setPlayerAnimationData("SPRITE_SIZE", "spriteSize", playerType);

	setPlayerStats(playerType, "SPEED", "speed", MULT_BY_RESOLUTION);
	setPlayerStats(playerType, "DASH_SPEED", "dashSpeed", MULT_BY_RESOLUTION);
	setPlayerStats(playerType, "JUMP_FORCE", "jumpForce", MULT_BY_RESOLUTION);
	setPlayerStats(playerType, "GRAVITY", "gravity", MULT_BY_RESOLUTION);
	setPlayerStats(playerType, "MAX_FALL_SPEED", "maxFallSpeed", MULT_BY_RESOLUTION);
	setPlayerStats(playerType, "MAX_JUMP_SPEED", "maxJumpSpeed", MULT_BY_RESOLUTION);
	setPlayerStats(playerType, "START_HP", "hp", NOT_MULT_BY_RESOLUTION);
	setPlayerStats(playerType, "ADDITIONAL_JUMPS", "additionalJumps", NOT_MULT_BY_RESOLUTION);
	setPlayerStats(playerType, "ADDITIONAL_JUMP_FORCE", "additionalJumpForce", MULT_BY_RESOLUTION);
	setPlayerStats(playerType, "JUMP_KILL_FORCE", "jumpKillForce", MULT_BY_RESOLUTION);

}