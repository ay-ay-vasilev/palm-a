#ifndef __GAMECONSTANTS_H__
#define __GAMECONSTANTS_H__
#include "JsonInstance.h"
#include "json.hpp"
#include <string>
#include <map>

class GameConstants {

private:
	static std::map<std::string, std::string> assetPaths;
	static std::map<std::string, float> animationData;


public:
	static void initConstants(std::string levelName);
	static void setAssetPath(const std::string& key, const std::string& category, const std::string& assetName);
	static void setAnimationData(const std::string& key, const std::string& unit, const std::string& type, const std::string& dataName);

	static std::string getAssetPath(const std::string& key);
	static float getAnimationData(const std::string& key);

};
#endif
