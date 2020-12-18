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
std::map<std::string, std::string> GameConstants::bossAssetPaths = {};
std::map<std::string, float> GameConstants::bossAnimationData = {};
std::map<std::string, float> GameConstants::bossStats = {};

std::map<std::string, std::string> GameConstants::levelAssetPaths = {};
std::map<std::string, float> GameConstants::levelAnimationData = {};
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

		setProjectileAssetPath("PLAYER_SPRITE_SHEET", "player", "spriteSheet");
		setProjectileAssetPath("PLAYER_PARTICLES", "player", "particles");
		setProjectileAssetPath("PLAYER_SPRITE", "player", "sprite");
		setProjectileAnimationData("PLAYER_NUM_OF_FRAMES", "player", "animationFramesNumber");
		setProjectileAnimationData("PLAYER_SPEED", "player", "animationSpeed");
		setProjectileAnimationData("PLAYER_SPRITE_SIZE", "player", "spriteSize");

		setProjectileStats("DEFAULT_DAMAGE", "default", "damage", NOT_MULT_BY_RESOLUTION);
		setProjectileStats("DEFAULT_SPEED", "default", "speed", MULT_BY_RESOLUTION);
		setProjectileStats("LASER_DAMAGE", "laser", "damage", NOT_MULT_BY_RESOLUTION);
		setProjectileStats("LASER_SPEED", "laser", "speed", MULT_BY_RESOLUTION);
		setProjectileStats("RAY_DAMAGE", "ray", "damage", MULT_BY_RESOLUTION);
		setProjectileStats("PLAYER_DAMAGE", "player", "damage", NOT_MULT_BY_RESOLUTION);
		setProjectileStats("PLAYER_SPEED", "player", "speed", MULT_BY_RESOLUTION);

		setBossAssetPath("SPRITE_SHEET","spriteSheet","link");
		setBossAssetPath("SPRITE_MODEL","sprite","link");
		setBossAssetPath("FIRST_ATTACK_START", "attackFirst", "start");
		setBossAssetPath("FIRST_ATTACK_ATTACK", "attackFirst", "attack");
		setBossAssetPath("FIRST_ATTACK_END", "attackFirst", "end");
		setBossAssetPath("SECOND_ATTACK_START", "attackSecond", "start");
		setBossAssetPath("SECOND_ATTACK_ATTACK", "attackSecond", "attack");
		setBossAssetPath("SECOND_ATTACK_END", "attackSecond", "end");
		setBossAssetPath("IDLE_BODY","idleBody","sprite");
		setBossAssetPath("IDLE_EYE", "idleEye", "sprite");

		setBossAnimationData("IDLE_BODY_NUM_OF_FRAMES", "idle", "body", "animationFramesNumber");
		setBossAnimationData("IDLE_BODY_SPEED", "idle", "body" , "animationSpeed");
		setBossAnimationData("IDLE_EYE_NUM_OF_FRAMES", "idle", "eye", "animationFramesNumber");
		setBossAnimationData("IDLE_EYE_SPEED", "idle", "eye", "animationSpeed");

		setBossAnimationData("FIRST_ATTACK_START_NUM_OF_FRAMES",	"attackFirst", "start", "animationFramesNumber");
		setBossAnimationData("FIRST_ATTACK_START_SPEED",			"attackFirst", "start", "animationSpeed");
		setBossAnimationData("FIRST_ATTACK_ATTACK_NUM_OF_FRAMES",	"attackFirst", "attack", "animationFramesNumber");
		setBossAnimationData("FIRST_ATTACK_ATTACK_SPEED",			"attackFirst", "attack", "animationSpeed");
		setBossAnimationData("FIRST_ATTACK_END_NUM_OF_FRAMES",		"attackFirst", "end", "animationFramesNumber");
		setBossAnimationData("FIRST_ATTACK_END_SPEED",				"attackFirst", "end", "animationSpeed");

		setBossAnimationData("SECOND_ATTACK_START_NUM_OF_FRAMES",			"attackSecond", "start", "animationFramesNumber");
		setBossAnimationData("SECOND_ATTACK_START_SPEED",					"attackSecond", "start", "animationSpeed");
		setBossAnimationData("SECOND_ATTACK_LEFT_TO_RIGHT_NUM_OF_FRAMES",	"attackSecond", "leftRight", "animationFramesNumber");
		setBossAnimationData("SECOND_ATTACK_LEFT_TO_RIGHT_SPEED",			"attackSecond", "leftRight", "animationSpeed");
		setBossAnimationData("SECOND_ATTACK_RIGHT_TO_LEFT_NUM_OF_FRAMES",	"attackSecond", "rightLeft", "animationFramesNumber");
		setBossAnimationData("SECOND_ATTACK_RIGHT_TO_LEFT_SPEED",			"attackSecond", "rightLeft", "animationSpeed");
		setBossAnimationData("SECOND_ATTACK_END_NUM_OF_FRAMES",				"attackSecond", "end", "animationFramesNumber");
		setBossAnimationData("SECOND_ATTACK_END_SPEED",						"attackSecond", "end", "animationSpeed");

		setLevelAssetPath("SPRITE_SHEET", "spriteSheet");
		setLevelAssetPath("FLOOR_SPRITE", "floorSprite");
		setLevelAssetPath("CLOSE_SPRITE", "closeSprite");
		setLevelAssetPath("MID_SPRITE", "midSprite");
		setLevelAssetPath("FAR_SPRITE", "farSprite");

		setLevelAnimationData("FLOOR_NUM_OF_FRAMES", "floorAnimationFramesNumber");
		setLevelAnimationData("FLOOR_SPEED", "floorAnimationSpeed");
		setLevelAnimationData("CLOSE_NUM_OF_FRAMES", "closeAnimationFramesNumber");
		setLevelAnimationData("CLOSE_SPEED", "closeAnimationSpeed");
		setLevelAnimationData("MID_NUM_OF_FRAMES", "midAnimationFramesNumber");
		setLevelAnimationData("MID_SPEED", "midAnimationSpeed");
		setLevelAnimationData("FAR_NUM_OF_FRAMES", "farAnimationFramesNumber");
		setLevelAnimationData("FAR_SPEED", "farAnimationSpeed");

		setLevelStats("WALL_DISTANCE", "wallDistance", MULT_BY_RESOLUTION);
		setLevelStats("FLOOR_HEIGHT", "floorHeight", MULT_BY_RESOLUTION);
		setLevelStats("DURATION", "levelDuration", NOT_MULT_BY_RESOLUTION);
		setLevelStats("ELEVATION_SPEED", "elevationSpeed", MULT_BY_RESOLUTION);
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
std::string GameConstants::getBossAssetPath(const std::string& key)
{
	return bossAssetPaths[key];
}
float GameConstants::getBossAnimationData(const std::string& key)
{
	return bossAnimationData[key];
}
std::string GameConstants::getLevelAssetPath(const std::string& key)
{
	return levelAssetPaths[key];
}
float GameConstants::getLevelAnimationData(const std::string& key)
{
	return levelAnimationData[key];
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
	playerAnimationData[key] = JsonInstance::GetInstance()->GetData("animations")["player"][playerType][dataName];
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
	enemyAssetPaths[key] = JsonInstance::GetInstance()->GetData("assetPaths")["levels"]["1"]["enemy"][type][assetName];
}
void GameConstants::setEnemyAnimationData(const std::string& key, const std::string& type, const std::string& dataName)
{
	enemyAnimationData[key] = JsonInstance::GetInstance()->GetData("animations")["levels"]["1"]["enemy"][type][dataName];
}
void GameConstants::setEnemyStats(const std::string& key, const std::string& type, const std::string& dataName, const bool multByResolution)
{
	enemyStats[key] = JsonInstance::GetInstance()->GetData("balance")["levels"]["1"]["enemy"][type][dataName];
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
	projectileAnimationData[key] = JsonInstance::GetInstance()->GetData("animations")["projectile"][type][dataName];
}
void GameConstants::setProjectileStats(const std::string& key, const std::string& type, const std::string& dataName, const bool multByResolution)
{
	projectileStats[key] = JsonInstance::GetInstance()->GetData("balance")["projectile"][type][dataName];
	if (multByResolution)
	{
		projectileStats[key] *= GameConstants::resolution;
	}
}

void GameConstants::setLevelAssetPath(const std::string& key, const std::string& assetName)
{
	levelAssetPaths[key] = JsonInstance::GetInstance()->GetData("assetPaths")["levels"]["1"]["background"][assetName];
}
void GameConstants::setLevelAnimationData(const std::string& key, const std::string& dataName)
{
	levelAnimationData[key] = JsonInstance::GetInstance()->GetData("animations")["levels"]["1"]["background"][dataName];
}
void GameConstants::setLevelStats(const std::string& key, const std::string& dataName, const bool multByResolution)
{
	levelStats[key] = JsonInstance::GetInstance()->GetData("balance")["levels"]["1"][dataName];
	if (multByResolution)
	{
		levelStats[key] *= GameConstants::resolution;
	}
}


void GameConstants::setBossAssetPath(const std::string& key, const std::string& type, const std::string& assetName)
{
	bossAssetPaths[key] = JsonInstance::GetInstance()->GetData("assetPaths")["levels"]["1"]["boss"][type][assetName];
}
void GameConstants::setBossAnimationData(const std::string& key, const std::string& type, const std::string& type2, const std::string& dataName)
{
	bossAnimationData[key] = JsonInstance::GetInstance()->GetData("animations")["bossAnim"][type][type2][dataName];
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

	setPlayerStats(playerType, "SHOOTS", "shoots", NOT_MULT_BY_RESOLUTION);
	setPlayerStats(playerType, "DASHES", "dashes", NOT_MULT_BY_RESOLUTION);
	setPlayerStats(playerType, "DASH_COOLDOWN", "dashCooldown", NOT_MULT_BY_RESOLUTION);
	setPlayerStats(playerType, "DASH_I_FRAMES", "dashIFrames", NOT_MULT_BY_RESOLUTION);
	setPlayerStats(playerType, "DMG_I_FRAMES", "dmgIFrames", NOT_MULT_BY_RESOLUTION);

}