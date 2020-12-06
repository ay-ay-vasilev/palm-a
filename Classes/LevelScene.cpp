#include <deque>
#include "Definitions.h"
#include "LevelScene.h"
#include "GameController.h"
#include <CCScheduler.h>
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include "json.hpp"
USING_NS_CC;

Scene* Level::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics( );

    if (DEBUG_MASK) {
        scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    }
    else {
        scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
    }

    
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
    remainingTime = 0;
    movementInputDeck.clear();
    GameController::enemies.clear();
    GameController::enemyProjectiles.clear();
    GameController::type2Enemies.clear();
    GameController::laserArr.clear();
    GameController::getJsonData();
    //init the music
    musicID = AudioEngine::play2d("audio/music/level1.mp3", false);
    AudioEngine::setVolume(musicID, 0.1);
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
	player->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + (float)LEVEL_FLOOR_HEIGHT*RESOLUTION_VARIABLE));
    player->setScale(0.25*RESOLUTION_VARIABLE);
	

	this->scheduleUpdate();

    auto floor = Sprite::create("res/level/test_full_background.png");
    floor->getTexture()->setAliasTexParameters();
    floor->setScale(RESOLUTION_VARIABLE);
    floor->setAnchorPoint(Vec2(0, 0));
    floor->setPosition(Vec2(origin.x, origin.y));
    
    auto dashButton = MenuItemImage::create(
        "res/ui/dash_button.png",
        "res/ui/dash_button.png",
        CC_CALLBACK_1(Level::dashButtonCallback, this));
    dashButton->setScale(RESOLUTION_VARIABLE);
    dashButton->setOpacity(180);
    dashButton->setAnchorPoint(Vec2(1, 0));
    dashButton->setPosition(Vec2(origin.x + visibleSize.width - dashButton->getContentSize().width / 2 * RESOLUTION_VARIABLE, origin.y + dashButton->getContentSize().height / 2 * RESOLUTION_VARIABLE));

    auto jumpButton = MenuItemImage::create(
        "res/ui/jump_button.png",
        "res/ui/jump_button.png",
        CC_CALLBACK_1(Level::jumpButtonCallback, this));
    jumpButton->setScale(RESOLUTION_VARIABLE);
    jumpButton->setOpacity(180);
    jumpButton->setAnchorPoint(Vec2(1, 0));
    jumpButton->setPosition(Vec2(origin.x + visibleSize.width - jumpButton->getContentSize().width / 2 * RESOLUTION_VARIABLE, origin.y + jumpButton->getContentSize().height / 2 * RESOLUTION_VARIABLE + dashButton->getContentSize().height * RESOLUTION_VARIABLE + 5 * RESOLUTION_VARIABLE));

    auto pauseButton = MenuItemImage::create(
        "res/ui/pause_button.png",
        "res/ui/pause_button.png",
        CC_CALLBACK_1(Level::pauseButtonCallback, this));
    pauseButton->setScale(RESOLUTION_VARIABLE);
    pauseButton->setOpacity(180);
    pauseButton->setAnchorPoint(Vec2(1, 1));
    pauseButton->setPosition(Vec2(origin.x + visibleSize.width - pauseButton->getContentSize().width / 2 * RESOLUTION_VARIABLE, origin.y + visibleSize.height - pauseButton->getContentSize().height / 2 * RESOLUTION_VARIABLE));
    
    gameUI = Menu::create(pauseButton, dashButton, jumpButton, NULL);
    gameUI->setPosition(Vec2::ZERO);

    pauseBackground = Sprite::create("res/ui/black.png");
    pauseBackground->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    pauseBackground->setOpacity(0);
    pauseBackground->setAnchorPoint(Vec2(0.5, 0.5));
    pauseBackground->setContentSize(this->getContentSize());

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

    // player score
    char playerScore[100];
    sprintf(playerScore, "Time: %i", remainingTime);
    scoreLabel = Label::createWithTTF(playerScore, "fonts/PixelForce.ttf", 12*RESOLUTION_VARIABLE);
    scoreLabel->setAnchorPoint(Vec2(0, 1));
    scoreLabel->setPosition(Vec2(origin.x + scoreLabel->getContentSize().width / 4 * RESOLUTION_VARIABLE, origin.y + visibleSize.height - scoreLabel->getContentSize().height / 2 * RESOLUTION_VARIABLE));
    Color3B color(255, 255, 255);
    scoreLabel->setColor(color);


    auto progressBarOver = Sprite::create("res/ui/status_bar_over.png");
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
    playerHPBar->setScale(0.5*RESOLUTION_VARIABLE);
    playerHPBar->setPercent(100);
    playerHPBar->setDirection(ui::LoadingBar::Direction::LEFT);

    cocos2d::Sprite* playerHPBarUnder = cocos2d::Sprite::create( "res/ui/hp_bar_1.png" );
    playerHPBarUnder->setAnchorPoint(Vec2(0, 0));
    playerHPBarUnder->setPosition(Vec2(origin.x, origin.y));
    playerHPBarUnder->setScale(0.5*RESOLUTION_VARIABLE);

    //===================================
    
    //====================================
    //enemy spawn
    //auto enemySpawnPointer = static_cast<cocos2d::SEL_SCHEDULE>(&Level::spawnRandomEnemy);
    
    //this->schedule(enemySpawnPointer, ENEMY_DEFAULT_SPAWN_FREQUENCY);
    
    //====================================
    //enemy type 3
    auto enemyProjectileSpawnPointer = static_cast<cocos2d::SEL_SCHEDULE>(&Level::spawnEnemyType3);
    
    this->schedule(enemyProjectileSpawnPointer, 1);
    //====================================

    //====================================
    //collision detector
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1( Level::onContactBegin, this );
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority( contactListener, this );
    //====================================
    currentTime = 0;
    //====================================
    auto audioUpdatePointer = static_cast<cocos2d::SEL_SCHEDULE>(&Level::audioUpdate);

    this->schedule(audioUpdatePointer, 0.005f);
    //====================================

    auto updateScorePointer = static_cast<cocos2d::SEL_SCHEDULE>(&Level::updateScore);
    this->schedule(updateScorePointer, 1.0f);

    this->addChild(playerHPBarUnder, 10);
    this->addChild(playerHPBar, 11);
    this->addChild(progressBar, 10);
    this->addChild(progressBarOver, 11);
    this->addChild(scoreLabel, 1);
    this->addChild(pauseMenu, 13);
    this->addChild(pauseBackground, 12);
    this->addChild(gameUI, 10);
    this->addChild(floor, 0);
    this->addChild(player, 5);


    return true;
}

void Level::update(float dt)
{

    player->update();

    char playerScore[100];
    sprintf(playerScore, "Score: %i", remainingTime);
    scoreLabel->setString(playerScore);
    progressBar->setPercent(remainingTime / (float)LEVEL_DURATION * 100.0);

    if (remainingTime > (float)LEVEL_DURATION) levelFinished();
    if (player->getHP() < 0) gameOver();

    GameController::updateRotationType3(player->getPosition());
}
bool Level::onContactBegin ( cocos2d::PhysicsContact &contact )
{
    //collision bit masks
    //player = 1
    //enemy = 2
    //enemy projectile = 3
    //laser = 4
    //enemy type 2 = 5
    //enemy type 3 = 6
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();

    //if player collided with enemy
    if ( ( 1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask() ) 
		|| ( 2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask() ) )
    {   
        player->updateHP((float)ENEMY_DEFAULT_COLLIDE_DMG);
        playerHPBar->setPercent(player->getHP()/(float)PLAYER_START_HP*100.0);
        
        //removeEnemy(GameController::enemies.at(closestEnemy));

        if (a->getCollisionBitmask() == 2) {
            this->removeEnemy(dynamic_cast<Enemy*>(a->getNode()));
            player->jumpKill();
        }
        if (b->getCollisionBitmask() == 2) {
            this->removeEnemy(dynamic_cast<Enemy*>(b->getNode()));
            player->jumpKill();
        }
    }

    //if player collided with projectile
    if ( ( 1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask() ) 
		|| ( 3 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask() ) )
    {   
        player->updateHP((float)ENEMY_DEFAULT_PROJECTILE_DMG);

        if (a->getCollisionBitmask() == 3) {
            this->removeProjectile(a->getNode());
        }
        if (b->getCollisionBitmask() == 3) {
            this->removeProjectile(b->getNode());
        }

        playerHPBar->setPercent(player->getHP()/ (float)PLAYER_START_HP*100.0);
    }
    //if player collided with laser
    if ((1 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask())
        || (4 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        player->updateHP((float)ENEMY_LASER_PROJECTILE_DMG);
        
        if (a->getCollisionBitmask() == 4) {
            this->removeLaser(a->getNode());
        }
        if (b->getCollisionBitmask() == 4) {
            this->removeLaser(b->getNode());
        }

        playerHPBar->setPercent(player->getHP() / (float)PLAYER_START_HP * 100.0);
    }
    //if player collided with enemy type 2
    if ((1 == a->getCollisionBitmask() && 5 == b->getCollisionBitmask())
        || (5 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        player->updateHP((float)ENEMY_LASER_COLLIDE_DMG);

        playerHPBar->setPercent(player->getHP() / (float)PLAYER_START_HP * 100.0);

        if (a->getCollisionBitmask() == 5) {
            this->removeEnemyType2(dynamic_cast<EnemyType2*>(a->getNode()));
            player->jumpKill();
        }
        if (b->getCollisionBitmask() == 5) {
            this->removeEnemyType2(dynamic_cast<EnemyType2*>(b->getNode()));
            player->jumpKill();
        }
    }

    return true;
}

void Level::updateScore(float dt)
{
    remainingTime = remainingTime + 1;
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

void Level::jumpButtonCallback(Ref* pSender)
{
    player->jump();
}

void Level::pauseButtonCallback(Ref* pSender)
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

void Level::spawnEnemy(float dt)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Enemy* enemy;
    enemy = GameController::spawnEnemy();
    enemy->setScale(0.25*RESOLUTION_VARIABLE);
	this->addChild(enemy, 4);

    //moving and deleting
    float distance = visibleSize.height + (float)ENEMY_SPRITE_SIZE * 2;

    auto enemySpeed = (float)ENEMY_DEFAULT_SPEED * RESOLUTION_VARIABLE;

    auto randA = GameController::movementFunc(enemy->getSpawnPoint()-1,0);
    auto randB = GameController::movementFunc(enemy->getSpawnPoint()-1,1);
    auto enemyAction1 = MoveBy::create(distance*0.5 / enemySpeed, Vec2(visibleSize.width * randA, -0.5*visibleSize.height - ENEMY_SPRITE_SIZE));
    auto enemyAction2 = MoveBy::create(distance*0.5 / enemySpeed, Vec2(visibleSize.width * randB, -0.5*visibleSize.height - ENEMY_SPRITE_SIZE));
    auto callBack = CallFunc::create([this,enemy](){this->removeEnemy(enemy);});
    auto sequence = Sequence::create(enemyAction1,enemyAction2, callBack, NULL);
    enemy->runAction(sequence);
}
void Level::spawnEnemyType2(float dt)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    EnemyType2* enemy;
    enemy = GameController::spawnEnemyType2();
    enemy->setScale(0.25 * RESOLUTION_VARIABLE);
    this->addChild(enemy, 4);

    //moving and deleting
    float distance = visibleSize.height + (float)ENEMY_SPRITE_SIZE * 2;

    auto enemySpeed = (float)ENEMY_DEFAULT_SPEED * RESOLUTION_VARIABLE;

    auto randA = GameController::movementFunc(enemy->getSpawnPoint() - 1, 0);
    auto randB = GameController::movementFunc(enemy->getSpawnPoint() - 1, 1);
    auto enemyAction1 = MoveBy::create(distance * 0.5 / enemySpeed, Vec2(visibleSize.width * randA, -0.5 * visibleSize.height - ENEMY_SPRITE_SIZE));
    auto enemyAction2 = MoveBy::create(distance * 0.5 / enemySpeed, Vec2(visibleSize.width * randB, -0.5 * visibleSize.height - ENEMY_SPRITE_SIZE));
    auto callBack = CallFunc::create([this, enemy]() {this->removeEnemyType2(enemy); });
    auto sequence = Sequence::create(enemyAction1, enemyAction2, callBack, NULL);
    enemy->runAction(sequence);
}
void Level::spawnEnemyType3(float dt) 
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    EnemyType3* enemy;
    enemy = GameController::spawnEnemyType3();
    this->addChild(enemy, 3);

    //moving and deleting
    float distance = visibleSize.height + (float)ENEMY_SPRITE_SIZE * 2;
    auto enemySpeed = (float)ENEMY_DEFAULT_SPEED * RESOLUTION_VARIABLE;
    auto enemyAction1 = MoveBy::create(distance / enemySpeed, Vec2(0, visibleSize.height + ENEMY_SPRITE_SIZE*2));
    auto callBack = CallFunc::create([this, enemy]() {this->removeEnemyType3(enemy); });
    auto sequence = Sequence::create(enemyAction1, callBack, NULL);
    enemy->runAction(sequence);
}
void Level::spawnEnemyProjectiles(float dt)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto randomType = cocos2d::RandomHelper::random_int(1, 2);
    if (randomType == 1) {
        if (GameController::enemies.size() > 0) {
            long min = 0;
            long max = GameController::enemies.size() - 1;
            long n = cocos2d::RandomHelper::random_int(min, max);
            /*while (GameController::enemies.at(n)->getPosition().y < player->getPosition().y)
            {
                n = cocos2d::RandomHelper::random_int(min, max);
            }*/

            //create if enemy is above player
            if (GameController::enemies.at(n)->getPosition().y > player->getPosition().y) {
                //creating
                EnemyProjectile* projectile;
                projectile = GameController::spawnEnemyProjectile(GameController::enemies.at(n)->getPosition(), player->getPosition());
                projectile->setScale(RESOLUTION_VARIABLE);
                this->addChild(projectile, 5);
                //moving and deleting
                Vec2 tar = GameController::calcTarget(GameController::enemies.at(n)->getPosition(), player->getPosition());
                float distance = GameController::findDistance(GameController::enemies.at(n)->getPosition(), tar);
                auto moveAction = MoveTo::create(distance / ENEMY_DEFAULT_PROJECTILE_SPEED / RESOLUTION_VARIABLE, tar);
                auto callBack = CallFunc::create([this, projectile]() {this->removeProjectile(projectile); });
                auto sequence = Sequence::create(moveAction, callBack, NULL);
                projectile->runAction(sequence);
                //SFX
                auto projectileSFX = AudioEngine::play2d("audio/sfx/projectileSFX.mp3", false);
                AudioEngine::setVolume(projectileSFX, 0.1);
            }
        }
    }

    else {
        if (GameController::type2Enemies.size() > 0) {
            long min = 0;
            long max = GameController::type2Enemies.size() - 1;
            long n = cocos2d::RandomHelper::random_int(min, max);
           /* while (GameController::type2Enemies.at(n)->getPosition().y < player->getPosition().y)
            {
                n = cocos2d::RandomHelper::random_int(min, max);
            }*/
            //create if enemy is above player
            if (GameController::type2Enemies.at(n)->getPosition().y > player->getPosition().y) {
                //creating
                Laser* projectile;
                projectile = GameController::spawnLaser(GameController::type2Enemies.at(n)->getPosition(), player->getPosition());
                projectile->setScale(RESOLUTION_VARIABLE);
                projectile->setRotation(GameController::calcAngle(GameController::type2Enemies.at(n)->getPosition(), player->getPosition()));
                this->addChild(projectile, 5);
                //moving and deleting
                Vec2 tar = GameController::calcTarget(GameController::type2Enemies.at(n)->getPosition(), player->getPosition());
                float distance = GameController::findDistance(GameController::type2Enemies.at(n)->getPosition(), tar);
                auto moveAction = MoveTo::create(distance / ENEMY_LASER_PROJECTILE_SPEED / RESOLUTION_VARIABLE, tar);
                auto callBack = CallFunc::create([this, projectile]() {this->removeLaser(projectile); });
                auto sequence = Sequence::create(moveAction, callBack, NULL);

                projectile->runAction(sequence);
                //SFX
                auto laserSFX = AudioEngine::play2d("audio/sfx/laserSFX.mp3", false);
                AudioEngine::setVolume(laserSFX, 0.01);
                //pausing and resuming movement of enemy
                /*
                auto  pauseCallback = CallFunc::create([i]() {
                    GameController::type2Enemies.at(i)->stopActionByTag(1);
                    });
                float delay = LASER_SPAWNING_TIME;
                auto delayAction = DelayTime::create(delay);
                auto resumeCallback = CallFunc::create([i]() {
                    GameController::type2Enemies.at(i)->resume();
                    });
                GameController::type2Enemies.at(i)->runAction(Sequence::create(pauseCallback, delayAction, resumeCallback, NULL));
                */

            }
        }
    }
}
void Level::spawnRandomEnemy(float dt) 
{
    int type = GameController::randomTypeOfEnemy();
    switch (type)
    {
    case 1:
        Level::spawnEnemy(dt);
        break;
    case 2:
        Level::spawnEnemyType2(dt);
        break;
    }
    
}

void Level::removeProjectile(Node* projectile)
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
void Level::removeEnemyType2(EnemyType2 *enemy) 
{
    GameController::type2Enemies.eraseObject(enemy);
    enemy->cleanup();
    removeChild(enemy,true);
}
void Level::removeEnemyType3(EnemyType3* enemy)
{
    GameController::type3Enemies.eraseObject(enemy);
    enemy->cleanup();
    removeChild(enemy, true);
}
void Level::removeLaser(Node* laser)
{
    GameController::laserArr.eraseObject(laser);
    laser->cleanup();
    removeChild(laser, true);
}

void Level::audioUpdate(float dt)
{
    //if (GameController::shootingTimings[currentTiming] < AudioEngine::getCurrentTime(musicID) * 1000)
    currentTime += 5;
    if (GameController::shootingTimings[currentTiming] < currentTime)
    {
        Level::spawnEnemyProjectiles(dt);
        currentTiming++;
    }
}