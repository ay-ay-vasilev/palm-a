#include "GameUI.h"
#include "Definitions.h"
#include "AudioEngine.h"
#include "MainMenuScene.h"
#include "GameConstants.h"
USING_NS_CC;

GameUI* GameUI::create(Player* player)
{
	GameUI* gameUI = new GameUI();

	if (gameUI->init())
	{
		gameUI->autorelease();
		gameUI->initGameUI(player);
        gameUI->initHUD();
        gameUI->initPauseMenu();
		return gameUI;
	}
	CC_SAFE_RELEASE(gameUI);
	return NULL;
}

void GameUI::update()
{
    char playerScore[100];
    sprintf(playerScore, "Score: %i", totalScore);
    scoreLabel->setString(playerScore);
    progressBar->setPercent(totalScore / GameConstants::getLevelStats("DURATION") * 100.0);
    updateHPBar();
}

void GameUI::updateScore(float dt)
{
    totalScore += 1;
}

void GameUI::updateHPBar()
{
    playerHPBar->setPercent(player->getHP() / GameConstants::getPlayerStats("START_HP") * 100.0);
}

void GameUI::initGameUI(Player* player)
{
    this->player = player;
    isPaused = false;
    totalScore = 0;

    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    auto dashButton = MenuItemImage::create(
        "res/ui/dash_button.png",
        "res/ui/dash_button.png",
        CC_CALLBACK_1(GameUI::dashButtonCallback, this));
    dashButton->setScale(RESOLUTION_VARIABLE);
    dashButton->setOpacity(180);
    dashButton->setAnchorPoint(Vec2(1, 0));
    dashButton->setPosition(Vec2(origin.x + visibleSize.width - dashButton->getContentSize().width / 2 * RESOLUTION_VARIABLE, origin.y + dashButton->getContentSize().height / 2 * RESOLUTION_VARIABLE));

    auto jumpButton = MenuItemImage::create(
        "res/ui/jump_button.png",
        "res/ui/jump_button.png",
        CC_CALLBACK_1(GameUI::jumpButtonCallback, this));
    jumpButton->setScale(RESOLUTION_VARIABLE);
    jumpButton->setOpacity(180);
    jumpButton->setAnchorPoint(Vec2(1, 0));
    jumpButton->setPosition(Vec2(origin.x + visibleSize.width - jumpButton->getContentSize().width / 2 * RESOLUTION_VARIABLE, origin.y + jumpButton->getContentSize().height / 2 * RESOLUTION_VARIABLE + dashButton->getContentSize().height * RESOLUTION_VARIABLE + 5 * (float)RESOLUTION_VARIABLE));

    auto pauseButton = MenuItemImage::create(
        "res/ui/pause_button.png",
        "res/ui/pause_button.png",
        CC_CALLBACK_1(GameUI::pauseButtonCallback, this));
    pauseButton->setScale(RESOLUTION_VARIABLE);
    pauseButton->setOpacity(180);
    pauseButton->setAnchorPoint(Vec2(1, 1));
    pauseButton->setPosition(Vec2(origin.x + visibleSize.width - pauseButton->getContentSize().width / 2 * RESOLUTION_VARIABLE, origin.y + visibleSize.height - pauseButton->getContentSize().height / 2 * RESOLUTION_VARIABLE));

    gameUI = Menu::create(pauseButton, dashButton, jumpButton, NULL);
    gameUI->setPosition(Vec2::ZERO);

    bossHpBarOver = Sprite::create("res/ui/boss_hp_bar_under.png");
    bossHpBarOver->getTexture()->setAliasTexParameters();
    bossHpBarOver->setScale(RESOLUTION_VARIABLE);
    bossHpBarOver->setAnchorPoint(Vec2(0.5, 0.5));
    bossHpBarOver->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - GameConstants::getLevelStats("FLOOR_HEIGHT")));

    bossHpBar = ui::LoadingBar::create("res/ui/boss_hp_bar.png");
    bossHpBar->setScale(RESOLUTION_VARIABLE);
    bossHpBar->setAnchorPoint(Vec2(0.5, 0.5));
    bossHpBar->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - GameConstants::getLevelStats("FLOOR_HEIGHT")));
    bossHpBar->setPercent(100);
    bossHpBar->setDirection(ui::LoadingBar::Direction::LEFT);

    bossNameLabel = Label::createWithTTF("AMU", "fonts/PixelForce.ttf", 12 * (float)RESOLUTION_VARIABLE);
    bossNameLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - GameConstants::getLevelStats("FLOOR_HEIGHT") + bossHpBar->getContentSize().height * 2 * RESOLUTION_VARIABLE));

    this->addChild(bossHpBar, UI_LAYER);
    this->addChild(bossHpBarOver, UI_LAYER);
    this->addChild(bossNameLabel, UI_LAYER);

    bossHpBarOver->setVisible(false);
    bossHpBar->setVisible(false);
    bossNameLabel->setVisible(false);

    this->addChild(gameUI, UI_LAYER);
}

void GameUI::scheduleScoreUpdate()
{
    auto updateScorePointer = static_cast<cocos2d::SEL_SCHEDULE>(&GameUI::updateScore);
    this->schedule(updateScorePointer, 1.0f);
}

void GameUI::initPauseMenu()
{
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    pauseBackground = Sprite::create("res/ui/black.png");
    pauseBackground->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    pauseBackground->setOpacity(0);
    pauseBackground->setAnchorPoint(Vec2(0.5, 0.5));
    pauseBackground->setContentSize(this->getContentSize());

    auto resumeLabel = Label::createWithTTF("RESUME", "fonts/PixelForce.ttf", 18 * (float)RESOLUTION_VARIABLE);
    MenuItemLabel* resumeItem = MenuItemLabel::create(resumeLabel, CC_CALLBACK_1(GameUI::pauseButtonCallback, this));
    resumeItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3 * 2));

    auto mainMenuLabel = Label::createWithTTF("MAIN MENU", "fonts/PixelForce.ttf", 18 * (float)RESOLUTION_VARIABLE);
    MenuItemLabel* mainMenuItem = MenuItemLabel::create(mainMenuLabel, CC_CALLBACK_1(GameUI::goToMainMenu, this));
    mainMenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3));

    pauseMenu = Menu::create(resumeItem, mainMenuItem, NULL);
    pauseMenu->setEnabled(false);
    pauseMenu->setVisible(false);
    pauseMenu->setContentSize(this->getContentSize());
    pauseMenu->setPosition(Vec2::ZERO);

    this->addChild(pauseMenu, PAUSE_MENU_LAYER);
    this->addChild(pauseBackground, PAUSE_BACKGROUND_LAYER);
}

void GameUI::initHUD()
{
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    // player score
    char playerScore[100];
    sprintf(playerScore, "Time: %i", totalScore);
    scoreLabel = Label::createWithTTF(playerScore, "fonts/PixelForce.ttf", 12 * (float)RESOLUTION_VARIABLE);
    scoreLabel->setAnchorPoint(Vec2(0, 1));
    scoreLabel->setPosition(Vec2(origin.x + scoreLabel->getContentSize().width / 4 * RESOLUTION_VARIABLE, origin.y + visibleSize.height - scoreLabel->getContentSize().height / 2 * RESOLUTION_VARIABLE));
    Color3B color(255, 255, 255);
    scoreLabel->setColor(color);


    progressBarOver = Sprite::create("res/ui/status_bar_over.png");
    progressBarOver->getTexture()->setAliasTexParameters();
    progressBarOver->setScale(RESOLUTION_VARIABLE);
    progressBarOver->setAnchorPoint(Vec2(0.5, 0.5));
    progressBarOver->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - progressBarOver->getContentSize().height / 2 * RESOLUTION_VARIABLE));

    // progress bar
    progressBar = ui::LoadingBar::create("res/ui/status_bar.png");
    progressBar->setScale(RESOLUTION_VARIABLE);
    progressBar->setAnchorPoint(Vec2(0.5, 0.5));
    progressBar->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - progressBarOver->getContentSize().height / 2 * RESOLUTION_VARIABLE));
    progressBar->setPercent(0);
    progressBar->setDirection(ui::LoadingBar::Direction::LEFT);

    //===================================
    //player hp bar
    playerHPBar = ui::LoadingBar::create("res/ui/hp_bar_2.png");
    playerHPBar->setAnchorPoint(Vec2(0, 0));
    playerHPBar->setPosition(Vec2(origin.x, origin.y));
    playerHPBar->setScale(0.5 * RESOLUTION_VARIABLE);
    playerHPBar->setPercent(100);
    playerHPBar->setDirection(ui::LoadingBar::Direction::LEFT);

    cocos2d::Sprite* playerHPBarUnder = cocos2d::Sprite::create("res/ui/hp_bar_1.png");
    playerHPBarUnder->setAnchorPoint(Vec2(0, 0));
    playerHPBarUnder->setPosition(Vec2(origin.x, origin.y));
    playerHPBarUnder->setScale(0.5 * RESOLUTION_VARIABLE);

    this->addChild(playerHPBarUnder, BAR_UNDER_LAYER);
    this->addChild(playerHPBar, BAR_LAYER);
    this->addChild(progressBar, BAR_LAYER);
    this->addChild(progressBarOver, BAR_OVER_LAYER);
    this->addChild(scoreLabel, UI_LAYER);

}

void GameUI::dashButtonCallback(Ref* pSender)
{
    player->dash();
}

void GameUI::jumpButtonCallback(Ref* pSender)
{
    player->jump();
}

void GameUI::pauseButtonCallback(Ref* pSender)
{
    if (!isPaused) {
        pauseBackground->setOpacity(200);
        pauseMenu->setEnabled(true);
        pauseMenu->setVisible(true);
        gameUI->setEnabled(false);
        AudioEngine::pauseAll();
        Director::getInstance()->stopAnimation();
    }
    else {
        pauseBackground->setOpacity(0);
        pauseMenu->setEnabled(false);
        pauseMenu->setVisible(false);
        gameUI->setEnabled(true);
        AudioEngine::resumeAll();
        Director::getInstance()->startAnimation();
    }
    isPaused = !isPaused;
}

void GameUI::goToMainMenu(Ref* pSender)
{
    Scene* scene = MainMenu::createScene();
    TransitionFade* transition = TransitionFade::create(TRANSITION_TIME, scene);

    AudioEngine::stopAll();
    AudioEngine::end();

    auto menuMusicID = AudioEngine::play2d("audio/music/main_menu.mp3", false);
    AudioEngine::setVolume(menuMusicID, 0.1);

    Director::getInstance()->startAnimation();

    Director::getInstance()->replaceScene(scene);
}

int GameUI::getTotalScore()
{
    return totalScore;
}

void GameUI::removeProgressBar()
{
    removeChild(progressBar, true);
    removeChild(progressBarOver, true);
}

void GameUI::initBossUI()
{
    bossHpBarOver->setVisible(true);
    bossHpBar->setVisible(true);
    bossNameLabel->setVisible(true);
}

void GameUI::updateBossHPBar(float hp, float maxHp)
{
    bossHpBar->setPercent(hp / maxHp * 100);
}