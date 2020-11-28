#include <deque>
#include "Definitions.h"
#include "LevelScene.h"
#include "GameController.h"
#include <CCScheduler.h>
#include "AudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* Level::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics( );
    scene->getPhysicsWorld( )->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    
    // 'layer' is an autorelease object
    auto layer = Level::create();
    layer->setPhysicsWorld( scene->getPhysicsWorld( ) );

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool Level::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    isPaused = false;
    score = 100;
    movementInputDeck.clear();
    GameController::enemies.clear();
    GameController::enemyProjectiles.clear();

    //init the music
    auto music = AudioEngine::play2d("res/music/audio.mp3", true);
    AudioEngine::setVolume(music, 0.1);
    // important variables
    auto director = cocos2d::Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    // makes the game 2d
    director->setProjection(Director::Projection::_2D);

    auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(Level::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Level::onTouchEnded, this);
    
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Level::keyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Level::keyReleased, this);
    
    director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    player = Player::create();
    player->setPhysicsBody(player->getBody());
	player->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + FLOOR_HEIGHT*RESOLUTION_VARIABLE));
    player->setScale(0.25*RESOLUTION_VARIABLE);
	this->addChild(player, 5);

	this->scheduleUpdate();

    auto floor = Sprite::create("res/level/test_floor.png");
    floor->getTexture()->setAliasTexParameters();
    floor->setScale(0.9*RESOLUTION_VARIABLE); // FIX BACKGROUND
    floor->setAnchorPoint(Vec2(0.5, 0.5));
    floor->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 75*RESOLUTION_VARIABLE)); // FIX BACKGROUND
    this->addChild(floor, 0);

    auto dashButton = MenuItemImage::create(
        "res/ui/dash_button.png",
        "res/ui/dash_button.png",
        CC_CALLBACK_1(Level::dashButtonCallback, this));
    dashButton->setScale(RESOLUTION_VARIABLE);
    dashButton->setOpacity(70);
    dashButton->setAnchorPoint(Vec2(1, 0));
    dashButton->setPosition(Vec2(origin.x + visibleSize.width - dashButton->getContentSize().width / 2 * RESOLUTION_VARIABLE, origin.y + dashButton->getContentSize().height / 2 * RESOLUTION_VARIABLE));

    auto pauseButton = MenuItemImage::create(
        "res/ui/pause_button.png",
        "res/ui/pause_button.png",
        CC_CALLBACK_1(Level::pauseButtonCallback, this));
    pauseButton->setScale(RESOLUTION_VARIABLE);
    pauseButton->setOpacity(70);
    pauseButton->setAnchorPoint(Vec2(1, 1));
    pauseButton->setPosition(Vec2(origin.x + visibleSize.width - pauseButton->getContentSize().width / 2 * RESOLUTION_VARIABLE, origin.y + visibleSize.height - pauseButton->getContentSize().height / 2 * RESOLUTION_VARIABLE));
    
    gameUI = Menu::create(pauseButton, dashButton, NULL);
    gameUI->setPosition(Vec2::ZERO);
    this->addChild(gameUI, 10);

    pauseBackground = Sprite::create("res/ui/black.png");
    pauseBackground->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    pauseBackground->setOpacity(0);
    pauseBackground->setAnchorPoint(Vec2(0.5, 0.5));
    pauseBackground->setContentSize(this->getContentSize());
    this->addChild(pauseBackground, 12);

    auto resumeLabel = Label::createWithTTF("RESUME", "fonts/PixelForce.ttf", 18 * RESOLUTION_VARIABLE);
    MenuItemLabel *resumeItem = MenuItemLabel::create(resumeLabel, CC_CALLBACK_1(Level::pauseButtonCallback, this));
    resumeItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3 * 2));

    auto mainMenuLabel = Label::createWithTTF("MAIN MENU", "fonts/PixelForce.ttf", 18 * RESOLUTION_VARIABLE);
    MenuItemLabel *mainMenuItem = MenuItemLabel::create(mainMenuLabel, CC_CALLBACK_1(Level::goToMainMenu, this));
    mainMenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3));

    pauseMenu = Menu::create(resumeItem, mainMenuItem, NULL);
    pauseMenu->setEnabled(false);
    pauseMenu->setVisible(false);
    pauseMenu->setContentSize(this->getContentSize());
    pauseMenu->setPosition(Vec2::ZERO);
    this->addChild(pauseMenu, 13);

    // player score
    char playerScore[100];
    sprintf(playerScore, "Score: %i", score);
    scoreLabel = Label::createWithTTF(playerScore, "fonts/PixelForce.ttf", 12*RESOLUTION_VARIABLE);
    scoreLabel->setAnchorPoint(Vec2(0, 1));
    scoreLabel->setPosition(Vec2(origin.x + scoreLabel->getContentSize().width / 4 * RESOLUTION_VARIABLE, origin.y + visibleSize.height - scoreLabel->getContentSize().height / 2 * RESOLUTION_VARIABLE));
    Color3B color(255, 255, 255);
    scoreLabel->setColor(color);
    this->addChild(scoreLabel, 1);


    auto progressBarOver = Sprite::create("res/ui/status_bar_over.png");
    progressBarOver->getTexture()->setAliasTexParameters();
    progressBarOver->setScale(RESOLUTION_VARIABLE);
    progressBarOver->setAnchorPoint(Vec2(0.5, 0.5));
    progressBarOver->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - progressBarOver->getContentSize().height / 2 * RESOLUTION_VARIABLE));
    this->addChild(progressBarOver, 11);

    // progress bar
    progressBar = ui::LoadingBar::create("res/ui/status_bar.png");
    progressBar->setScale(RESOLUTION_VARIABLE);
    progressBar->setAnchorPoint(Vec2(0.5, 0.5));
    progressBar->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - progressBarOver->getContentSize().height / 2 * RESOLUTION_VARIABLE));
    progressBar->setPercent(0);
    progressBar->setDirection(ui::LoadingBar::Direction::LEFT);
    this->addChild(progressBar, 10);

    //===================================
    //player hp bar
    playerHPBar = ui::LoadingBar::create("res/ui/hp_bar_2.png");
    playerHPBar->setAnchorPoint(Vec2(0, 0));
    playerHPBar->setPosition(Vec2(origin.x, origin.y));
    playerHPBar->setScale(0.5*RESOLUTION_VARIABLE);
    playerHPBar->setPercent(100);
    playerHPBar->setDirection(ui::LoadingBar::Direction::LEFT);
    this->addChild(playerHPBar,11);

    cocos2d::Sprite* playerHPBarUnder = cocos2d::Sprite::create( "res/ui/hp_bar_1.png" );
    playerHPBarUnder->setAnchorPoint(Vec2(0, 0));
    playerHPBarUnder->setPosition(Vec2(origin.x, origin.y));
    playerHPBarUnder->setScale(0.5*RESOLUTION_VARIABLE);
    this->addChild(playerHPBarUnder,10);
    //===================================
    
    //====================================
    //enemy spawn
    auto enemySpawnPointer = static_cast<cocos2d::SEL_SCHEDULE>(&Level::spawnEnemy);
    
    this->schedule(enemySpawnPointer, ENEMY_SPAWN_FREQUENCY);
    
    //====================================
    //enemy shooting
    auto enemyProjectileSpawnPointer = static_cast<cocos2d::SEL_SCHEDULE>(&Level::spawnEnemyProjectiles);
    
    this->schedule(enemyProjectileSpawnPointer, ENEMY_PROJECTILE_FREQUENCY);
    //====================================

    //====================================
    //collision detector
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1( Level::onContactBegin, this );
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority( contactListener, this );
    //====================================

    auto updateScorePointer = static_cast<cocos2d::SEL_SCHEDULE>(&Level::updateScore);
    this->schedule(updateScorePointer, 1.0f);

    return true;
}

bool Level::onContactBegin ( cocos2d::PhysicsContact &contact )
{
    //collision bit masks
    //player = 1
    //enemy = 2
    //enemy projectile = 3
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();

    //if player collided with enemy
    if ( ( 1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask() ) 
		|| ( 2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask() ) )
    {   
        player->updateHP(ENEMY_COLLIDE_DMG);
        playerHPBar->setPercent(player->getHP());
    }
    if ( ( 1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask() ) 
		|| ( 3 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask() ) )
    {   
        player->updateHP(ENEMY_PROJECTILE_DMG);

        playerHPBar->setPercent(player->getHP());
    }
    return true;
}

void Level::update(float dt)
{
	player->update();

    char playerScore[100];
    sprintf(playerScore, "Score: %i", score);
    scoreLabel->setString(playerScore);
    progressBar->setPercent(100 - score);

    if (score <= 0) levelFinished();
    if (player->getHP() <= 0) gameOver();
}

void Level::updateScore(float dt)
{
    score = score - 1;
}

void Level::levelFinished()
{
    Scene* scene = LevelFinish::createScene();
    TransitionFade* transition = TransitionFade::create(TRANSITION_TIME, scene);
    
    AudioEngine::stopAll();
    AudioEngine::end();
    Director::getInstance()->replaceScene(scene);
}

void Level::gameOver()
{
    Scene* scene = MainMenu::createScene();
    TransitionFade* transition = TransitionFade::create(TRANSITION_TIME, scene);

    AudioEngine::stopAll();
    AudioEngine::end();
    Director::getInstance()->replaceScene(scene);
}


void Level::goToMainMenu(Ref* pSender)
{
    Scene* scene = MainMenu::createScene();
    TransitionFade* transition = TransitionFade::create(TRANSITION_TIME, scene);

    AudioEngine::stopAll();
    AudioEngine::end();
    Director::getInstance()->startAnimation();

    Director::getInstance()->replaceScene(scene);
}


bool Level::onTouchBegan(Touch *touch, Event *event)
{
	if(touch->getLocation().x < Director::getInstance()->getVisibleSize().width/2)
	{
        movementInputDeck.push_front(DIRECTION_LEFT);
	}
	if(touch->getLocation().x > Director::getInstance()->getVisibleSize().width/2)
	{
        movementInputDeck.push_front(DIRECTION_RIGHT);
	}
    if (!movementInputDeck.empty()) player->run(movementInputDeck.front());
	return true;
}

void Level::onTouchEnded(Touch *touch, Event *event)
{
    movementInputDeck.pop_front();
    if (movementInputDeck.empty()) player->idle();
    else player->run(movementInputDeck.front());
}

void Level::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_A:
            movementInputDeck.push_front(DIRECTION_LEFT);
            //player->run(DIRECTION_LEFT);
            break;
        case EventKeyboard::KeyCode::KEY_D:
            movementInputDeck.push_front(DIRECTION_RIGHT);
            //player->run(DIRECTION_RIGHT);
            break;
        case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
            player->dash();
            break;
        case EventKeyboard::KeyCode:: KEY_SPACE:
            player->jump();
            break;
    }
    if (!movementInputDeck.empty()) player->run(movementInputDeck.front());
}
void Level::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    //player->idle();
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_A:
        if (movementInputDeck.front() == DIRECTION_LEFT) movementInputDeck.pop_front();
        else movementInputDeck.pop_back();
        break;
    case EventKeyboard::KeyCode::KEY_D:
        if (movementInputDeck.front() == DIRECTION_RIGHT) movementInputDeck.pop_front();
        else movementInputDeck.pop_back();
        break;
    }
    if (movementInputDeck.empty()) player->idle();
    else player->run(movementInputDeck.front());
}


void Level::dashButtonCallback(Ref* pSender)
{
    player->dash();
}

void Level::pauseButtonCallback(Ref* pSender)
{
    if (!isPaused) {
        Director::getInstance()->stopAnimation();
        AudioEngine::pauseAll();

        pauseBackground->setOpacity(200);
        pauseMenu->setEnabled(true);
        pauseMenu->setVisible(true);
        gameUI->setEnabled(false);
    }
    else {
        Director::getInstance()->startAnimation();
        AudioEngine::resumeAll();

        pauseBackground->setOpacity(0);
        pauseMenu->setEnabled(false);
        pauseMenu->setVisible(false);
        gameUI->setEnabled(true);
    }
    isPaused = !isPaused;
}

void Level::spawnEnemy(float dt)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Enemy* enemy;
    enemy = GameController::spawnEnemy(1);
    enemy->setScale(0.25*RESOLUTION_VARIABLE);
	this->addChild(enemy, 4);
    float distance = visibleSize.height+ ENEMY_SPRITE_SIZE * 2;

    auto enemySpeed = ENEMY_SPEED * RESOLUTION_VARIABLE;

    switch(enemy->getSpawnPoint())
    {
        
        case 1:
        {
            auto enemyAction1 = MoveBy::create(distance*0.5 / enemySpeed, Vec2(visibleSize.width * -0.1, -0.5*visibleSize.height - ENEMY_SPRITE_SIZE));
            auto enemyAction2 = MoveBy::create(distance*0.5 / enemySpeed, Vec2(visibleSize.width * 0.1, -0.5*visibleSize.height - ENEMY_SPRITE_SIZE));
            auto callBack = CallFunc::create([this,enemy](){this->removeEnemy(enemy);});
            auto sequence = Sequence::create(enemyAction1,enemyAction2, callBack, NULL);
            enemy->runAction(sequence);
            break;
        }
        case 2:
        {
            auto enemyAction1 = MoveBy::create(distance*0.5 / enemySpeed, Vec2(visibleSize.width * 0.2, -0.5*visibleSize.height - ENEMY_SPRITE_SIZE));
            auto enemyAction2 = MoveBy::create(distance*0.5 / enemySpeed, Vec2(visibleSize.width * -0.2, -0.5*visibleSize.height - ENEMY_SPRITE_SIZE));
            auto callBack = CallFunc::create([this,enemy](){this->removeEnemy(enemy);});
            auto sequence = Sequence::create(enemyAction1,enemyAction2, callBack, NULL);
            enemy->runAction(sequence);
            break;
        }
        case 3:
        {
            auto enemyAction1 = MoveBy::create(distance*0.5 / enemySpeed, Vec2(visibleSize.width * -0.2, -0.5*visibleSize.height - ENEMY_SPRITE_SIZE));
            auto enemyAction2 = MoveBy::create(distance*0.5 / enemySpeed, Vec2(visibleSize.width * 0.2, -0.5*visibleSize.height - ENEMY_SPRITE_SIZE));
            auto callBack = CallFunc::create([this,enemy](){this->removeEnemy(enemy);});
            auto sequence = Sequence::create(enemyAction1,enemyAction2, callBack, NULL);
            enemy->runAction(sequence);
            break;
        }
        case 4:
        {
            auto enemyAction1 = MoveBy::create(distance*0.5 / enemySpeed, Vec2(visibleSize.width * 0.1, -0.5*visibleSize.height - ENEMY_SPRITE_SIZE));
            auto enemyAction2 = MoveBy::create(distance*0.5 / enemySpeed, Vec2(visibleSize.width * -0.1, -0.5*visibleSize.height - ENEMY_SPRITE_SIZE));
            auto callBack = CallFunc::create([this,enemy](){this->removeEnemy(enemy);});
            auto sequence = Sequence::create(enemyAction1,enemyAction2, callBack, NULL);
            enemy->runAction(sequence);
            break;
        }
    }

    //auto enemyAction = MoveBy::create(distance / ENEMY_SPEED, Vec2(0, -1*visibleSize.height- ENEMY_SPRITE_SIZE * 2));
    //auto callBack = CallFunc::create([this,enemy](){this->removeEnemy(enemy);});
    //auto sequence = Sequence::create(enemyAction, callBack, NULL);
    //enemy->runAction(sequence);
    
}

void Level::spawnEnemyProjectiles(float dt)
{   
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    for(int i = GameController::enemies.size()-1; i>=0; i--)
    {
        //creating
        EnemyProjectile* projectile;
        projectile = GameController::spawnEnemyProjectile(GameController::enemies.at(i)->getPosition(),player->getPosition());
        projectile->setScale(0.5*RESOLUTION_VARIABLE);
        this->addChild(projectile,5);
        //moving and deleting
        Vec2 tar = projectile->getTarget();
        float distanceX = projectile->getPosition().x - origin.x - tar.x;
        float distanceY = projectile->getPosition().y - origin.y - tar.y;
        float distance = sqrt(distanceX*distanceX + distanceY*distanceY);
        auto moveAction = MoveTo::create(distance / ENEMY_PROJECTILE_SPEED / RESOLUTION_VARIABLE, tar);
        auto callBack = CallFunc::create([this,projectile](){this->removeProjectile(projectile);});
        auto sequence = Sequence::create(moveAction, callBack, NULL);
        projectile->runAction(sequence);
    }
}

void Level::removeProjectile(EnemyProjectile *projectile)
{
    GameController::enemyProjectiles.eraseObject(projectile);
    projectile->cleanup();
    removeChild(projectile,true);
}

void Level::removeEnemy(Enemy *enemy)
{
    GameController::enemies.eraseObject(enemy);
    enemy->cleanup();
    removeChild(enemy,true);
}