#include "JsonInstance.h"
#include <fstream>

JsonInstance* JsonInstance::singleton = 0;

JsonInstance::JsonInstance() {
	std::ifstream fin("../Resources/data/levels/level1Data.json");
	level_1_Data = nlohmann::json::parse(fin);
	fin.close();

	fin.open("../Resources/data/enemies/enemiesData.json");
	enemies_Data = nlohmann::json::parse(fin);
	fin.close();

	fin.open("../Resources/data/player/playerData.json");
	player_Data = nlohmann::json::parse(fin);
	fin.close();
}

JsonInstance* JsonInstance::GetInstance() {
	if (!singleton) {
		singleton = new JsonInstance();
	}
	return singleton;
}

nlohmann::json JsonInstance::GetData(std::string nameOfData) {
	if (nameOfData._Equal("level1")) {
		return level_1_Data;
	}else
	if (nameOfData._Equal("enemies")) {
		return enemies_Data;
	}else
	if (nameOfData._Equal("player")) {
		return player_Data;
	}

	else return nullptr;
}
