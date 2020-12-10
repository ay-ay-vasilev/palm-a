#include "GameConstants.h"
#include "Definitions.h"

std::map<std::string, std::string> GameConstants::playerAssetPaths = {};
std::map<std::string, float> GameConstants::playerAnimationData = {};
std::map<std::string, float> GameConstants::playerStats = {};
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

		setLevelStats("WALL_DISTANCE", "wallDistance", MULT_BY_RESOLUTION);
		setLevelStats("FLOOR_HEIGHT", "floorHeight", MULT_BY_RESOLUTION);
		setLevelStats("DURATION", "levelDuration", NOT_MULT_BY_RESOLUTION);

	}
}

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
float GameConstants::getLevelStats(const std::string& key)
{
	return levelStats[key];
}



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
void GameConstants::setLevelStats(const std::string& key, const std::string& dataName, const bool multByResolution)
{
	levelStats[key] = JsonInstance::GetInstance()->GetData("balance")["level"][dataName];
	if (multByResolution)
	{
		levelStats[key] *= GameConstants::resolution;
	}
}
