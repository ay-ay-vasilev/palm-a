#include "JsonInstance.h"
#include <fstream>

JsonInstance* JsonInstance::singleton = 0;

JsonInstance::JsonInstance() {
	
	level_1_Data = OpenFile("Resources/data/levels/level1Data.json");
	balance_Data = OpenFile("Resources/data/balance.json");
	animations_Data = OpenFile("Resources/data/animations.json");
	asset_Data = OpenFile("Resources/data/assetPaths.json");
}

nlohmann::json JsonInstance::OpenFile(std::string path) {
	std::ifstream fin;
	fin.open(path);
	if (fin.fail()) {
		fin.open("../" + path);
	}
	auto result = nlohmann::json::parse(fin);
	fin.close();
	return result;
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
	if (nameOfData._Equal("balance")) {
		return balance_Data;
	}else
	if (nameOfData._Equal("animations")) {
		return animations_Data;
	}
	if (nameOfData._Equal("assetPaths")) {
		return asset_Data;
	}

	else return nullptr;
}
