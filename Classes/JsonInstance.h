#pragma once
#include "json.hpp"
#include <string>

class JsonInstance {

private:
	static nlohmann::json balance_Data;
	static nlohmann::json animations_Data;
	static nlohmann::json asset_Data;

	static nlohmann::json OpenFile(std::string path);

	static JsonInstance* singleton;
public:
	static JsonInstance* GetInstance();
	JsonInstance();
	static void ReloadFiles();
	nlohmann::json GetData(std::string nameOfData);

};