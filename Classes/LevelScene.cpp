#include <deque>
#include "Definitions.h"
#include "LevelScene.h"
#include "GameController.h"
#include <CCScheduler.h>
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include "json.hpp"
#include "GameConstants.h"
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

    GameConstants::initConstants("level1");
    isPaused = false;
    remainingTime = 0;
    movementInputDeck.clear();
    GameController::type1Enemies.clear();
    GameController::enemyProjectiles.clear();
    GameController::type2Enemies.clear();
    GameController::laserArr.clear();
    GameController::getJsonData();
    currentEnemy = 0;
    
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
	player->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + GameConstants::getLevelStats("FLOOR_HEIGHT")));
    player->setScale(0.25*RESOLUTION_VARIABLE);

	this->scheduleUpdate();

    char str[200] = { 0 };
    auto spriteCache = SpriteFrameCache::getInstance();
    spriteCache->addSpriteFramesWithFile("res/level/parallax_layers/level_1_static_layer.plist");
    Vector<SpriteFrame*> backgroundAnimFrames(3);

    for (int i = 1; i <= 3; i++)
    {
        sprintf(str, "level_1_static_layer%i.png", i);
        auto frame = spriteCache->getSpriteFrameByName(str);
        frame->getTexture()->setAliasTexParameters();
        backgroundAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
    }
    auto backgroundAnimation = Animation::createWithSpriteFrames(backgroundAnimFrames, 0.1);
    Animate* backgroundAnimate = Animate::create(backgroundAnimation);

    auto floor = Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("level_1_static_layer1.png"));
    floor->getTexture()->setAliasTexParameters();
    floor->setScale(RESOLUTION_VARIABLE);
    floor->setAnchorPoint(Vec2(0, 0));
    floor->setPosition(Vec2(origin.x, origin.y));
    
    floor->runAction(RepeatForever::create(backgroundAnimate));
    
    //PARALLAX
    closeSpeed = 100*(float)RESOLUTION_VARIABLE;
    midSpeed = closeSpeed/2;
    farSpeed = midSpeed/2;

    auto parallaxClose1 = Sprite::create("res/level/parallax_layers/close_background.png");
    auto parallaxClose2 = Sprite::create("res/level/parallax_layers/close_background.png");
    auto parallaxMid1 = Sprite::create("res/level/parallax_layers/mid_background.png");
    auto parallaxMid2 = Sprite::create("res/level/parallax_layers/mid_background.png");
    auto parallaxFar1 = Sprite::create("res/level/parallax_layers/far_background.png");
    auto parallaxFar2 = Sprite::create("res/level/parallax_layers/far_background.png");

    parallaxClose1->getTexture()->setAliasTexParameters();
    parallaxClose1->setScale(RESOLUTION_VARIABLE);
    parallaxClose1->setAnchorPoint(Vec2(0, 0));
    parallaxClose2->getTexture()->setAliasTexParameters();
    parallaxClose2->setScale(RESOLUTION_VARIABLE);
    parallaxClose2->setAnchorPoint(Vec2(0, 0));
    parallaxMid1->getTexture()->setAliasTexParameters();
    parallaxMid1->setScale(RESOLUTION_VARIABLE);
    parallaxMid1->setAnchorPoint(Vec2(0, 0));
    parallaxMid2->getTexture()->setAliasTexParameters();
    parallaxMid2->setScale(RESOLUTION_VARIABLE);
    parallaxMid2->setAnchorPoint(Vec2(0, 0));
    parallaxFar1->getTexture()->setAliasTexParameters();
    parallaxFar1->setScale(RESOLUTION_VARIABLE);
    parallaxFar1->setAnchorPoint(Vec2(0, 0));
    parallaxFar2->getTexture()->setAliasTexParameters();
    parallaxFar2->setScale(RESOLUTION_VARIABLE);
    parallaxFar2->setAnchorPoint(Vec2(0, 0));

    paraNodeClose = ParallaxNode::create();
    paraNodeMid = ParallaxNode::create();
    paraNodeFar = ParallaxNode::create();

    paraNodeClose->addChild(parallaxClose1, -1, Vec2(0, closeSpeed), Vec2::ZERO);
    paraNodeClose->addChild(parallaxClose2, -1, Vec2(0, closeSpeed), Vec2(0, -visibleSize.height));
    paraNodeMid->addChild(parallaxMid1, -2, Vec2(0, midSpeed), Vec2::ZERO);
    paraNodeMid->addChild(parallaxMid2, -2, Vec2(0, midSpeed), Vec2(0, -visibleSize.height));
    paraNodeFar->addChild(parallaxFar1, -3, Vec2(0, farSpeed), Vec2::ZERO);
    paraNodeFar->addChild(parallaxFar2, -3, Vec2(0, farSpeed), Vec2(0, -visibleSize.height));

    paraNodeClose->runAction(MoveTo::create(visibleSize.height / closeSpeed, Vec2(0, visibleSize.height / closeSpeed)));
    paraNodeMid->runAction(MoveTo::create(visibleSize.height / midSpeed, Vec2(0, visibleSize.height / midSpeed)));
    paraNodeFar->runAction(MoveTo::create(visibleSize.height / farSpeed, Vec2(0, visibleSize.height / farSpeed)));

    this->addChild(paraNodeClose, -1);
    this->addChild(paraNodeMid, -2);
    this->addChild(paraNodeFar, -3);

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
    /*auto enemySpawnPointer = static_cast<cocos2d::SEL_SCHEDULE>(&Level::spawnRandomEnemy);
    
    this->schedule(enemySpawnPointer, ENEMY_DEFAULT_SPAWN_FREQUENCY);*/
    
    //====================================
    //enemy type 3
    enemyType3SpawnPointer = static_cast<cocos2d::SEL_SCHEDULE>(&Level::spawnEnemyType3);
    
    this->schedule(enemyType3SpawnPointer, 5);
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
    GameController::updateEnemyFacing(player->getPosition());

    char playerScore[100];
    sprintf(playerScore, "Score: %i", remainingTime);
    scoreLabel->setString(playerScore);
    progressBar->setPercent(remainingTime / GameConstants::getLevelStats("DURATION") * 100.0);

    if (remainingTime > GameConstants::getLevelStats("DURATION") && !GameController::bossFightIsOn)
    {
        spawnBoss();
        GameController::bossFightIsOn = true;
        removeChild(progressBar,true);
        removeChild(progressBarOver,true);
        AudioEngine::stop(musicID);
        this->unschedule(enemyType3SpawnPointer);
    }
    if (player->getHP() < 0) gameOver();

    GameController::updateRotationType3(player->getPosition());
    spawnEnemyOnTiming(dt);

    if (paraNodeClose->getPosition().y == this->getContentSize().height / closeSpeed) {
        paraNodeClose->setPosition(0, 1.0f/closeSpeed);
        paraNodeClose->runAction(MoveTo::create(this->getContentSize().height / closeSpeed, Vec2(0, this->getContentSize().height / closeSpeed)));
    }
    if (paraNodeMid->getPosition().y == this->getContentSize().height / midSpeed) {
        paraNodeMid->setPosition(0, 1.0f/midSpeed);
        paraNodeMid->runAction(MoveTo::create(this->getContentSize().height / midSpeed, Vec2(0, this->getContentSize().height / midSpeed)));
    }
    if (paraNodeFar->getPosition().y == this->getContentSize().height / farSpeed) {
        paraNodeFar->setPosition(0, 1.0f/farSpeed);
        paraNodeFar->runAction(MoveTo::create(this->getContentSize().height / farSpeed, Vec2(0, this->getContentSize().height / farSpeed)));
    }


    GameController::bossMovement();
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
        player->updateHP(GameConstants::getEnemyStats("REGULAR_COLLIDE_DAMAGE"));
        playerHPBar->setPercent(player->getHP()/ GameConstants::getPlayerStats("START_HP")*100.0);

        if (a->getCollisionBitmask() == 2) {
            if (player->jumpKill(dynamic_cast<EnemyType1*>(a->getNode())->getPositionY()))
            {
                this->removeEnemy(dynamic_cast<EnemyType1*>(a->getNode()));
            }
        }
        if (b->getCollisionBitmask() == 2) {
            if (player->jumpKill(dynamic_cast<EnemyType1*>(b->getNode())->getPositionY()))
            {
                this->removeEnemy(dynamic_cast<EnemyType1*>(b->getNode()));

            }
        }
    }

    //if player collided with projectile
    if ( ( 1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask() ) 
		|| ( 3 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask() ) )
    {   
        player->updateHP(GameConstants::getProjectileStats("DEFAULT_DAMAGE"));

        if (a->getCollisionBitmask() == 3) {
            auto particles = DefaultProjectile::onDestroyParticles(a->getNode()->getPosition());
            this->addChild(particles, 100);
            
            this->removeProjectile(a->getNode());

        }
        if (b->getCollisionBitmask() == 3) {
            auto particles = DefaultProjectile::onDestroyParticles(b->getNode()->getPosition());
            this->addChild(particles, 100);

            this->removeProjectile(b->getNode());
        }

        playerHPBar->setPercent(player->getHP()/ GameConstants::getPlayerStats("START_HP")*100.0);
    }
    //if player collided with laser
    if ((1 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask())
        || (4 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        player->updateHP(GameConstants::getProjectileStats("LASER_DAMAGE"));
        
        if (a->getCollisionBitmask() == 4) {
            auto particles = LaserProjectile::onDestroyParticles(player->getPosition());
            this->addChild(particles, 100);
            this->removeLaser(a->getNode());
        }
        if (b->getCollisionBitmask() == 4) {
            auto particles = LaserProjectile::onDestroyParticles(player->getPosition());
            this->addChild(particles, 100);
            this->removeLaser(b->getNode());
        }

        playerHPBar->setPercent(player->getHP() / GameConstants::getPlayerStats("START_HP") * 100.0);
    }
    //if player collided with enemy type 2
    if ((1 == a->getCollisionBitmask() && 5 == b->getCollisionBitmask())
        || (5 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        player->updateHP(GameConstants::getEnemyStats("LASER_COLLIDE_DAMAGE"));

        playerHPBar->setPercent(player->getHP() / GameConstants::getPlayerStats("START_HP") * 100.0);

        if (a->getCollisionBitmask() == 5) {
            if (player->jumpKill(dynamic_cast<EnemyType2*>(a->getNode())->getPositionY()))
            {
                this->removeEnemyType2(dynamic_cast<EnemyType2*>(a->getNode()));
            }
        }
        if (b->getCollisionBitmask() == 5) {
            if (player->jumpKill(dynamic_cast<EnemyType2*>(b->getNode())->getPositionY()))
            {
                this->removeEnemyType2(dynamic_cast<EnemyType2*>(b->getNode()));
            }
        }
    }

    //if player collided with boss
    if ((1 == a->getCollisionBitmask() && 8 == b->getCollisionBitmask())
        || (8 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        player->jumpKill(0);
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

    if (!GameController::bossFightIsOn)
    {
        AudioEngine::stopAll();
        AudioEngine::end();
    }
    
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

void Level::spawnEnemy(float dt, int enemyPos)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    EnemyType1* enemy;
    enemy = GameController::spawnEnemy(enemyPos);
    enemy->setScale(0.25*RESOLUTION_VARIABLE);
	this->addChild(enemy, 4);

    //moving and deleting
    float distance = visibleSize.height + enemy->getContentSize().width;

    auto enemySpeed = GameConstants::getEnemyStats("REGULAR_SPEED");

    auto randA = GameController::movementFunc(enemy->getSpawnPoint()-1,0);
    auto randB = GameController::movementFunc(enemy->getSpawnPoint()-1,1);
    auto enemyAction1 = MoveBy::create(distance*0.5 / enemySpeed, Vec2(visibleSize.width * randA, -0.5*visibleSize.height - enemy->getContentSize().width));
    auto enemyAction2 = MoveBy::create(distance*0.5 / enemySpeed, Vec2(visibleSize.width * randB, -0.5*visibleSize.height - enemy->getContentSize().width));
    auto callBack = CallFunc::create([this,enemy](){this->removeEnemy(enemy);});
    auto sequence = Sequence::create(enemyAction1,enemyAction2, callBack, NULL);
    enemy->runAction(sequence);
}
void Level::spawnEnemyType2(float dt, int enemyPos)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    EnemyType2* enemy;
    enemy = GameController::spawnEnemyType2(enemyPos);
    enemy->setScale(0.25 * RESOLUTION_VARIABLE);
    this->addChild(enemy, 4);

    //moving and deleting
    float distance = visibleSize.height + enemy->getContentSize().width * 2;

    auto enemySpeed = GameConstants::getEnemyStats("LASER_SPEED");

    auto randA = GameController::movementFunc(enemy->getSpawnPoint() - 1, 0);
    auto randB = GameController::movementFunc(enemy->getSpawnPoint() - 1, 1);
    auto enemyAction1 = MoveBy::create(distance * 0.5 / enemySpeed, Vec2(visibleSize.width * randA, -0.5 * visibleSize.height - enemy->getContentSize().width));
    auto enemyAction2 = MoveBy::create(distance * 0.5 / enemySpeed, Vec2(visibleSize.width * randB, -0.5 * visibleSize.height - enemy->getContentSize().width));
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
    auto way1 = RandomHelper::random_int(4, 6) / 10.0 ;
    auto way2 = 0.15;
    auto way3 = 2;
    //moving and deleting
    float distance = visibleSize.height;
    auto enemySpeed = GameConstants::getEnemyStats("TURRET_SPEED");

    auto enemyAction1 = MoveBy::create(distance * way1 / enemySpeed, Vec2(0, visibleSize.height * way1));
    auto enemyAction2 = MoveBy::create(distance * way2 / enemySpeed, Vec2(0, visibleSize.height * way2));
    auto enemyAction3 = MoveBy::create(distance * way3 / enemySpeed, Vec2(0, visibleSize.height * way3));
    auto callBack = CallFunc::create([this, enemy]() {this->removeEnemyType3(enemy); });
    auto laserRayPointer = CallFunc::create([this, dt, enemy]() {this->spawnLaserRay(dt, enemy); });
    auto stopRotation = CallFunc::create([enemy]() {enemy->setBoolRotate(false); });

    auto sequence = Sequence::create(enemyAction1, stopRotation, enemyAction2, laserRayPointer,enemyAction3, callBack, NULL);
    enemy->runAction(sequence);
}
void Level::spawnEnemyProjectiles(float dt)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto randomType = cocos2d::RandomHelper::random_int(1, 2);
    if (randomType == 1) {
        if (GameController::type1Enemies.size() > 0) {
            long min = 0;
            long max = GameController::type1Enemies.size() - 1;
            long n = cocos2d::RandomHelper::random_int(min, max);
            /*while (GameController::enemies.at(n)->getPosition().y < player->getPosition().y)
            {
                n = cocos2d::RandomHelper::random_int(min, max);
            }*/

            //create if enemy is above player
            if (GameController::type1Enemies.at(n)->getPosition().y > player->getPosition().y) {
                //creating
                DefaultProjectile* projectile;
                projectile = GameController::spawnEnemyProjectile(GameController::type1Enemies.at(n)->getPosition(), player->getPosition());
                projectile->setScale(RESOLUTION_VARIABLE);
                this->addChild(projectile, 5);
                //moving and deleting
                Vec2 tar = GameController::calcTarget(GameController::type1Enemies.at(n)->getPosition(), player->getPosition());
                float distance = GameController::findDistance(GameController::type1Enemies.at(n)->getPosition(), tar);
                auto moveAction = MoveTo::create(distance / GameConstants::getProjectileStats("DEFAULT_SPEED"), tar);
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
                LaserProjectile* projectile;
                projectile = GameController::spawnLaser(GameController::type2Enemies.at(n)->getPosition(), player->getPosition());
                projectile->setScale(RESOLUTION_VARIABLE);
                projectile->setRotation(GameController::calcAngle(GameController::type2Enemies.at(n)->getPosition(), player->getPosition()));
                this->addChild(projectile, 5);
                //moving and deleting
                Vec2 tar = GameController::calcTarget(GameController::type2Enemies.at(n)->getPosition(), player->getPosition());
                float distance = GameController::findDistance(GameController::type2Enemies.at(n)->getPosition(), tar);
                auto moveAction = MoveTo::create(distance / GameConstants::getProjectileStats("LASER_SPEED"), tar);
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

void Level::spawnLaser(Level1Boss* boss)
{
    //here
}

void Level::spawnLaserRay(float dt,EnemyType3* enemy)
{
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    RayProjectile* projectile;
    projectile = GameController::spawnLaserRay(player->getPosition());
    projectile->setPosition(enemy->getPosition());
    projectile->setScale(RESOLUTION_VARIABLE);

    auto angle = enemy->getRotationAngle();
    if (enemy->getSpawnPoint() == 2) angle += 180;
    projectile->setRotation(angle);
    this->addChild(projectile, 5);
    auto enemySpeed = (float)100 * RESOLUTION_VARIABLE;

    float distance = visibleSize.height * 2;
    auto moveAction = MoveBy::create(1.5f,Vec2(0,enemySpeed*1.5f)); // MAGIC NUMBER
    auto remove = CallFunc::create([this, projectile]() {this->removeLaserRay(projectile); });
    auto sequence = Sequence::create(moveAction,remove,NULL);

    projectile->runAction(sequence);

    auto raySFX = AudioEngine::play2d("audio/sfx/raySFX.mp3", false);
    AudioEngine::setVolume(raySFX, 0.2);
}
void Level::spawnEnemyOnTiming(float dt)
{
    if (GameController::enemySpawnTimings[currentEnemy] * 1000 != 0 && remainingTime < GameConstants::getLevelStats("DURATION")) {
        if (currentTime > GameController::enemySpawnTimings[currentEnemy]*1000)
        {
            int type = GameController::enemyTypeArr[currentEnemy];
            switch (type)
            {
            case 1:
                Level::spawnEnemy(dt , GameController::spawnPointArr[currentEnemy]);
                break;
            case 2:
                Level::spawnEnemyType2(dt, GameController::spawnPointArr[currentEnemy]);
                break;
            }
            currentEnemy++;
        }
    }
    
    
}

void Level::removeProjectile(Node* projectile)
{
    GameController::enemyProjectiles.eraseObject(projectile);
    projectile->cleanup();
    removeChild(projectile,true);
}

void Level::removeEnemy(EnemyType1 *enemy)
{
    GameController::type1Enemies.eraseObject(enemy);
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
void Level::removeLaserRay(RayProjectile* ray)
{
    GameController::laserRays.eraseObject(ray);
    ray->cleanup();
    removeChild(ray,true);
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
void Level::spawnBoss()
{
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    Level1Boss* boss = GameController::createLevel1Boss();
    boss->setPosition(Vec2(visibleSize.width/2,visibleSize.height));
    boss->setScale(0.25 * RESOLUTION_VARIABLE);
    this->addChild(boss, 5);

    auto moveDown = MoveBy::create(5,Vec2(0,-1*boss->getContentSize().height*0.25 * RESOLUTION_VARIABLE));
    auto changeState = CallFunc::create([boss]() {boss->setState(2); });
    auto spawnRay = CallFunc::create([this,boss]() {this->spawnLaserRay(boss); });
    auto changePhase = CallFunc::create([boss]() {boss->setPhase(0); });
    auto sequence = Sequence::create(moveDown, changePhase, changeState, spawnRay, NULL);
    boss->runAction(sequence);
}
void Level::spawnLaserRay(Level1Boss* boss) 
{
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    RayProjectile* projectile;
    projectile = GameController::spawnLaserRay(player->getPosition());
    projectile->setScale(RESOLUTION_VARIABLE);
    projectile->setPosition(Vec2(boss->getPosition().x, boss->getPosition().y + projectile->getContentSize().width / 5));

    auto angle = 90;
    projectile->setRotation(angle);
    this->addChild(projectile,6);
    boss->setRay(projectile);

    //auto raySFX = AudioEngine::play2d("audio/sfx/raySFX.mp3", true);
    //AudioEngine::setVolume(raySFX, 0.2);
}