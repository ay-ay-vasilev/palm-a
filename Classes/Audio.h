#ifndef __AUDIO_H__
#define __AUDIO_H__
#include "cocos2d.h"
#include "JsonInstance.h"
#include "json.hpp"
#include <string>

class Audio {	
private:
	static std::string mainMenuMusicPath;
	static std::string cutsceneMusic;
	static std::string levelMusic;
	static std::string bossMusic;
public:
	static bool menuThemePlay;
	static int mainMenuThemeID;
	static void startMenuTheme();
	static void startLvlMusic();
	static void startBossMusic();
	static void setMenuThemePlay(bool status);
	static float volMusic;
	static float lvlMusicVol;
	static int lvlMusicID;
	static int bossMusicID;

	static void setVolMusic(float val);
	static void setLvlMusicPaths(std::string lvl);
	static void setCutsceneMusicPath(std::string lvl);
	static void setMainMenuMusicPath();
	static void preloadLvlMusic();
	static void uncacheLvlMusic();

	static std::string getCutsceneMusic();
	static std::string getLevelMusic();
	static std::string getBossMusic();
};
#endif