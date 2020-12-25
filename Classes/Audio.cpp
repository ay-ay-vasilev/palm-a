#include "Audio.h"
#include "GameConstants.h"
#include "AudioEngine.h"
#include <string>
USING_NS_CC;

bool Audio::menuThemePlay = false;
float Audio::volMusic = 0.1;
float Audio::lvlMusicVol = 0.1;
int Audio::mainMenuThemeID = 0;
int Audio::bossMusicID = 0;
int Audio::lvlMusicID = 0;
std::string Audio::mainMenuMusicPath = "";
std::string Audio::cutsceneMusic = "";
std::string Audio::levelMusic = "";
std::string Audio::bossMusic = "";

void Audio::preloadLvlMusic() {
	AudioEngine::preload(levelMusic);
	AudioEngine::preload(bossMusic);
}
void Audio::uncacheLvlMusic() {
	AudioEngine::uncache(levelMusic);
	AudioEngine::uncache(bossMusic);
}

void Audio::setMenuThemePlay(bool status) {
	menuThemePlay = status;
}

void Audio::startMenuTheme() {
	if (!menuThemePlay) {
		mainMenuThemeID = AudioEngine::play2d(mainMenuMusicPath, true, volMusic);
		menuThemePlay = true;
	}
}
void Audio::startLvlMusic() {
	lvlMusicID = AudioEngine::play2d(levelMusic, false, lvlMusicVol);
}
void Audio::startBossMusic() {
	bossMusicID = AudioEngine::play2d(bossMusic, false, 0.03);
}
void Audio::setLvlMusicPaths(std::string lvl) {
	levelMusic = JsonInstance::GetInstance()->GetData("assetPaths")["levels"][lvl]["level"]["levelMusic"];
	bossMusic = JsonInstance::GetInstance()->GetData("assetPaths")["levels"][lvl]["level"]["bossMusic"];
	lvlMusicVol = JsonInstance::GetInstance()->GetData("balance")["levels"][lvl]["levelMusicVolume"];
}
void Audio::setMainMenuMusicPath() {
	mainMenuMusicPath = "audio/music/main_menu.mp3";
}
void Audio::setCutsceneMusicPath(std::string lvl) {
	cutsceneMusic = JsonInstance::GetInstance()->GetData("assetPaths")["levels"][lvl]["cutscene"]["cutsceneMusic"];
}
void Audio::setVolMusic(float val) {
	volMusic = val;
}
std::string Audio::getCutsceneMusic() {
	return cutsceneMusic;
}
std::string Audio::getLevelMusic() {
	return levelMusic;
}
std::string Audio::getBossMusic() {
	return bossMusic;
}