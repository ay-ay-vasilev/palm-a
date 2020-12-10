#pragma once
#include "json.hpp"
#include <string>

class JsonInstance {

private:
	nlohmann::json level_1_Data;
	nlohmann::json balance_Data;
	nlohmann::json animations_Data;
	nlohmann::json asset_Data;

	nlohmann::json OpenFile(std::string path);

	static JsonInstance* singleton;
public:
	static JsonInstance* GetInstance();
	JsonInstance();
	nlohmann::json GetData(std::string nameOfData);

};