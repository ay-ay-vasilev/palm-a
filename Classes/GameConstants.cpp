#include "GameConstants.h"

std::map<std::string, std::string> GameConstants::assetPaths = {};
std::map<std::string, float> GameConstants::animationData = {};

void GameConstants::initConstants(std::string levelName)
{
	if (levelName == "level1")
	{
		setAssetPath("PLAYER_SHEET", "player", "spriteSheet");
		setAssetPath("PLAYER_UNARMED_IDLE_LEFT", "player", "idleUnarmedLeft");
		setAssetPath("PLAYER_UNARMED_IDLE_RIGHT", "player", "idleUnarmedRight");
		setAssetPath("PLAYER_UNARMED_RUN_LEFT", "player", "runUnarmedLeft");
		setAssetPath("PLAYER_UNARMED_RUN_RIGHT", "player", "runUnarmedRight");
		setAssetPath("PLAYER_UNARMED_JUMP_LEFT", "player", "jumpUnarmedLeft");
		setAssetPath("PLAYER_UNARMED_JUMP_RIGHT", "player", "jumpUnarmedRight");
		setAssetPath("PLAYER_UNARMED_FALL_LEFT", "player", "fallUnarmedLeft");
		setAssetPath("PLAYER_UNARMED_FALL_RIGHT", "player", "fallUnarmedRight");
		setAnimationData("PLAYER_ANIM_IDLE_NUM_OF_FRAMES", "playerAnim", "regular", "idleFrames");
		setAnimationData("PLAYER_ANIM_RUN_NUM_OF_FRAMES", "playerAnim", "regular", "runFrames");
		setAnimationData("PLAYER_ANIM_JUMP_NUM_OF_FRAMES", "playerAnim", "regular", "jumpFrames");
		setAnimationData("PLAYER_ANIM_FALL_NUM_OF_FRAMES", "playerAnim", "regular", "fallFrames");
		setAnimationData("PLAYER_ANIM_IDLE_SPEED", "playerAnim", "regular", "idleAnimSpeed");
		setAnimationData("PLAYER_ANIM_RUN_SPEED", "playerAnim", "regular", "runAnimSpeed");
		setAnimationData("PLAYER_ANIM_JUMP_SPEED", "playerAnim", "regular", "jumpAnimSpeed");
		setAnimationData("PLAYER_ANIM_FALL_SPEED", "playerAnim", "regular", "fallAnimSpeed");
		setAnimationData("PLAYER_SPRITE_SIZE", "playerAnim", "regular", "spriteSize");
	}
}

std::string GameConstants::getAssetPath(const std::string& key)
{
	return assetPaths[key];
}
float GameConstants::getAnimationData(const std::string& key)
{
	return animationData[key];
}

void GameConstants::setAssetPath(const std::string& key, const std::string& category, const std::string& assetName)
{
	assetPaths[key] = JsonInstance::GetInstance()->GetData("assetPaths")[category][assetName];
}

void GameConstants::setAnimationData(const std::string& key, const std::string& unit, const std::string& type, const std::string& dataName)
{
	animationData[key] = JsonInstance::GetInstance()->GetData("animations")[unit][type][dataName];
}
