#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "Boss.h"

class GameUI : public cocos2d::Sprite
{
public:
	static GameUI* create(Player* player);
	void update();
    void updateScore(float points);
    void updateHPBar();

    void dashButtonCallback(cocos2d::Ref* pSender);
    void jumpButtonCallback(cocos2d::Ref* pSender);
    void pauseButtonCallback(cocos2d::Ref* pSender);
    void goToMainMenu(cocos2d::Ref* pSender);

    int getTotalScore();

    void removeProgressBar();

    void initBossUI();
    void updateBossHPBar(float hp, float maxHp);

    void scheduleScoreUpdate();

private:

    Player* player;

    bool isPaused;
    int totalScore;

    void initGameUI(Player* player);
    void initPauseMenu();
    void initHUD();

    cocos2d::Menu* pauseMenu;
    cocos2d::Menu* gameUI;
    cocos2d::Sprite* pauseBackground;
    cocos2d::Sprite* progressBarOver;
    cocos2d::ui::LoadingBar* progressBar;

    cocos2d::Label* scoreLabel;
    cocos2d::Label* playerHPLabel;
    cocos2d::ui::LoadingBar* playerHPBar;

    cocos2d::ui::LoadingBar* bossHpBar;
    cocos2d::Sprite* bossHpBarOver;
    cocos2d::Label* bossNameLabel;
};