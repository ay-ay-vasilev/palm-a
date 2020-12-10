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
	static std::map<std::string, float> levelStats;


public:
	static float resolution;
	static void initConstants(std::string levelName);
	
	static void setPlayerAssetPath(const std::string& key, const std::string& assetName);
	static void setPlayerAnimationData(const std::string& key, const std::string& dataName);
	static void setPlayerStats(const std::string& key, const std::string& dataName, const bool multByResolution);
	static void setLevelStats(const std::string& key, const std::string& dataName, const bool multByResolution);


	static std::string getPlayerAssetPath(const std::string& key);
	static float getPlayerAnimationData(const std::string& key);
	static float getPlayerStats(const std::string& key);
	static float getLevelStats(const std::string& key);

};
#endif
