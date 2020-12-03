#include "JsonInstance.h"
#include <fstream>

JsonInstance* JsonInstance::singleton = 0;

JsonInstance::JsonInstance() {
	std::ifstream fin("../Resources/levels/level1Data.json");
	level_1_Data = nlohmann::json::parse(fin);
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
	}

	else return nullptr;
}
