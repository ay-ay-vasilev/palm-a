#ifndef __GAMECONSTANTS_H__
#define __GAMECONSTANTS_H__
#include "JsonInstance.h"
#include "json.hpp"
#include <string>
#include <map>

class GameConstants {

private:
	static std::map<std::string, std::string> playerAssetPaths;
	static std::map<std::string, float> playerAnimationData;
	static std::map<std::string, float> playerStats;

	static std::map<std::string, std::string> enemyAssetPaths;
	static std::map<std::string, float> enemyAnimationData;
	static std::map<std::string, float> enemyStats;

	static std::map<std::string, std::string> projectileAssetPaths;
	static std::map<std::string, float> projectileAnimationData;
	static std::map<std::string, float> projectileStats;

	static std::map<std::string, std::string> GameConstants::levelAssetPaths;
	static std::map<std::string, float> GameConstants::levelAnimationData;
	static std::map<std::string, float> levelStats;

	static std::map<std::string, std::string> bossAssetPaths;
	static std::map<std::string, float> bossAnimationData;
	static std::map<std::string, float> bossStats;
	

public:
	static float resolution;
	static void initConstants(std::string level);
	
	static void setPlayerAssetPath(const std::string& key, const std::string& assetName, const std::string& playerType);
	static void setPlayerAnimationData(const std::string& key, const std::string& dataName, const std::string& playerType);
	static void setPlayerStats(const std::string& playerType, const std::string& key, const std::string& dataName, const bool multByResolution);
	static void setEnemyAssetPath(const std::string& key, const std::string& level, const std::string& type, const std::string& assetName);
	static void setEnemyAnimationData(const std::string& key, const std::string& level, const std::string& type, const std::string& dataName);
	static void setEnemyStats(const std::string& key, const std::string& level, const std::string& type, const std::string& dataName, const bool multByResolution);
	static void setProjectileAssetPath(const std::string& key, const std::string& type, const std::string& assetName);
	static void setProjectileAnimationData(const std::string& key, const std::string& type, const std::string& dataName);
	static void setProjectileStats(const std::string& key, const std::string& type, const std::string& dataName, const bool multByResolution);
	static void setBossAssetPath(const std::string& key, const std::string& level, const std::string& type, const std::string& assetName);
	static void setBossAnimationData(const std::string& key, const std::string& level, const std::string& type, const std::string& type2,const std::string& dataName);

	static void setLevelAssetPath(const std::string& key, const std::string& level, const std::string& assetName);
	static void setLevelAnimationData(const std::string& key, const std::string& level, const std::string& dataName);
	static void setLevelStats(const std::string& key, const std::string& level, const std::string& dataName, const bool multByResolution);

	static std::string getPlayerAssetPath(const std::string& key);
	static float getPlayerAnimationData(const std::string& key);
	static float getPlayerStats(const std::string& key);	
	static std::string getEnemyAssetPath(const std::string& key);
	static float getEnemyAnimationData(const std::string& key);
	static float getEnemyStats(const std::string& key);
	static std::string getProjectileAssetPath(const std::string& key);
	static float getProjectileAnimationData(const std::string& key);
	static float getProjectileStats(const std::string& key);

	static std::string getLevelAssetPath(const std::string& key);
	static float getLevelAnimationData(const std::string& key);
	static float getLevelStats(const std::string& key);

	static std::string getBossAssetPath(const std::string& key);
	static float getBossAnimationData(const std::string& key);
	
	static void loadPlayer(const std::string& type);
};
#endif
