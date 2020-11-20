#include "LevelScene.h"
#include "Definitions.h"
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
    //init the music
    AudioEngine::play2d("res/music/audio.mp3", true);
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

    director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    player = Player::create();
    player->setPhysicsBody(player->getBody());
	player->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + FLOOR_HEIGHT));
    player->setScale(0.5); // MAGIC NUMBER FIX LATER
	this->addChild(player, 5);

	this->scheduleUpdate();

    auto floor = Sprite::create("res/level/test_floor.png");
    floor->getTexture()->setAliasTexParameters();
    floor->setScale(1.0); // MAGIC NUMBER FIX LATER
    floor->setAnchorPoint(Vec2(0.5, 0.5));
    floor->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(floor, 0);

    auto dashButton = MenuItemImage::create(
        "res/ui/dash_button.png",
        "res/ui/dash_button.png",
        CC_CALLBACK_1(Level::dashButtonCallback, this));
    dashButton->setScale(2.0);
    dashButton->setOpacity(70);
    dashButton->setAnchorPoint(Vec2(1, 0));
    dashButton->setPosition(Vec2(origin.x + visibleSize.width - dashButton->getContentSize().width, origin.y + dashButton->getContentSize().height));

    auto pauseButton = MenuItemImage::create(
        "res/ui/pause_button.png",
        "res/ui/pause_button.png",
        CC_CALLBACK_1(Level::pauseButtonCallback, this));
    pauseButton->setScale(2.0);
    pauseButton->setOpacity(70);
    pauseButton->setAnchorPoint(Vec2(1, 1));
    pauseButton->setPosition(Vec2(origin.x + visibleSize.width - pauseButton->getContentSize().width / 2, origin.y + visibleSize.height - pauseButton->getContentSize().height / 2));
    
    auto menu = Menu::create(pauseButton, dashButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 10);
    

    //===================================
    //player hp bar
    playerHPBar = ui::LoadingBar::create("res/ui/hp_bar_2.png");
    playerHPBar->setPosition(Vec2(origin.x + playerHPBar->getContentSize().width, origin.y + visibleSize.height - playerHPBar->getContentSize().height));
    playerHPBar->setPercent(100);
    playerHPBar->setDirection(ui::LoadingBar::Direction::LEFT);
    this->addChild(playerHPBar,101);

    cocos2d::Sprite* playerHPBarUnder = cocos2d::Sprite::create( "res/ui/hp_bar_1.png" );
    playerHPBarUnder->setPosition(Vec2(origin.x + playerHPBarUnder->getContentSize().width, origin.y + visibleSize.height - playerHPBarUnder->getContentSize().height));
    this->addChild(playerHPBarUnder,100);
    //===================================
    // // add player character sprite
    // auto character = Sprite::create("res/character/idle/test_idle_right.png");

    // if (character == nullptr)
    // {
    //     problemLoading("'test idle sprite'");
    // }
    // else
    // {
    //     // make pixel art not look blurry
    //     character->getTexture()->setAliasTexParameters();
    //     // make the character 4 times bigger
    //     character->setScale(4.0);
    //     // make the center bottom of the character the anchor point
    //     character->setAnchorPoint(Vec2(0.5, 0));
    //     // position the character on the center of the screen
    //     character->setPosition(Vec2(visibleSize.width/2 + origin.x, origin.y + 20));
    //     // add the character as a child to this layer
    //     this->addChild(character, 0);
    // }

    // auto direction = "right";

    // REMOVE LATER, THIS IS CLOSE BUTTON =======================================================
    //auto closeItem = MenuItemImage::create("res/ui/close-test.png",
    //                                       "res/ui/close-test.png",
    //                                    CC_CALLBACK_1(Level::menuCloseCallback, this));


    //closeItem->setScale(2.0); // MAGIC NUMBER FIX LATER
    //float x = origin.x + visibleSize.width - closeItem->getContentSize().width;
    //float y = origin.y + visibleSize.height - closeItem->getContentSize().height;
    //closeItem->setPosition(Vec2(x,y));

    //auto menu = Menu::create(closeItem, NULL);
    //menu->setPosition(Vec2::ZERO);
    //this->addChild(menu, 1);
    // ===========================================================================================
    
    //===================================
    //hp label
    char playerHP[5];
    sprintf(playerHP,"%i",player->getHP());

    playerHPLabel = Label::createWithTTF(playerHP,"fonts/arial.ttf",24);
    playerHPLabel->setColor( Color3B::WHITE );
    playerHPLabel->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y ) );
    this->addChild( playerHPLabel, 10 );

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
        player->updateHP(10);
        playerHPBar->setPercent(player->getHP()/2);
    }
    if ( ( 1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask() ) 
		|| ( 3 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask() ) )
    {   
        player->updateHP(2);
        playerHPBar->setPercent(player->getHP()/2);
    }
    return true;
}

void Level::update(float dt)
{
	player->update();
}

bool Level::onTouchBegan(Touch *touch, Event *event)
{
	if(touch->getLocation().x < Director::getInstance()->getVisibleSize().width/2)
	{
		player->run(0); // param '0' for left
	}
	if(touch->getLocation().x > Director::getInstance()->getVisibleSize().width/2)
	{
		player->run(1); // param '1' for right
	}

	return true;
}

void Level::onTouchEnded(Touch *touch, Event *event)
{
	player->idle();
}

void Level::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void Level::dashButtonCallback(Ref* pSender)
{
    //To do dash
}

void Level::pauseButtonCallback(Ref* pSender)
{
    if (!isPaused) {
        Director::getInstance()->stopAnimation();
        AudioEngine::pauseAll();
        isPaused = true;
    }
    else {
        Director::getInstance()->startAnimation();
        AudioEngine::resumeAll();
        isPaused = false;
    }
}

void Level::spawnEnemy(float dt)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //creating
    Enemy* enemy;
    enemy = GameController::spawnEnemy(1);
    enemy->setScale(0.5); // MAGIC NUMBER FIX LATER
	this->addChild(enemy, 4);
    //moving and deleting
    float distance = visibleSize.height+ ENEMY_SPRITE_SIZE * 2;

    switch(enemy->getSpawnPoint())
    {
        case 1:
        {
            auto enemyAction1 = MoveBy::create(distance*0.5 / ENEMY_SPEED, Vec2(visibleSize.width * -0.1, -0.5*visibleSize.height - ENEMY_SPRITE_SIZE));
            auto enemyAction2 = MoveBy::create(distance*0.5 / ENEMY_SPEED, Vec2(visibleSize.width * 0.1, -0.5*visibleSize.height - ENEMY_SPRITE_SIZE));
            auto callBack = CallFunc::create([this,enemy](){this->removeEnemy(enemy);});
            auto sequence = Sequence::create(enemyAction1,enemyAction2, callBack, NULL);
            enemy->runAction(sequence);
            break;
        }
        case 2:
        {
            auto enemyAction1 = MoveBy::create(distance*0.5 / ENEMY_SPEED, Vec2(visibleSize.width * 0.2, -0.5*visibleSize.height - ENEMY_SPRITE_SIZE));
            auto enemyAction2 = MoveBy::create(distance*0.5 / ENEMY_SPEED, Vec2(visibleSize.width * -0.2, -0.5*visibleSize.height - ENEMY_SPRITE_SIZE));
            auto callBack = CallFunc::create([this,enemy](){this->removeEnemy(enemy);});
            auto sequence = Sequence::create(enemyAction1,enemyAction2, callBack, NULL);
            enemy->runAction(sequence);
            break;
        }
        case 3:
        {
            auto enemyAction1 = MoveBy::create(distance*0.5 / ENEMY_SPEED, Vec2(visibleSize.width * -0.2, -0.5*visibleSize.height - ENEMY_SPRITE_SIZE));
            auto enemyAction2 = MoveBy::create(distance*0.5 / ENEMY_SPEED, Vec2(visibleSize.width * 0.2, -0.5*visibleSize.height - ENEMY_SPRITE_SIZE));
            auto callBack = CallFunc::create([this,enemy](){this->removeEnemy(enemy);});
            auto sequence = Sequence::create(enemyAction1,enemyAction2, callBack, NULL);
            enemy->runAction(sequence);
            break;
        }
        case 4:
        {
            auto enemyAction1 = MoveBy::create(distance*0.5 / ENEMY_SPEED, Vec2(visibleSize.width * 0.1, -0.5*visibleSize.height - ENEMY_SPRITE_SIZE));
            auto enemyAction2 = MoveBy::create(distance*0.5 / ENEMY_SPEED, Vec2(visibleSize.width * -0.1, -0.5*visibleSize.height - ENEMY_SPRITE_SIZE));
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
        this->addChild(projectile,5);
        //moving and deleting
        Vec2 tar = projectile->getTarget();
        float distanceX = projectile->getPosition().x - origin.x - tar.x;
        float distanceY = projectile->getPosition().y - origin.y - tar.y;
        float distance = sqrt(distanceX*distanceX + distanceY*distanceY);
        auto moveAction = MoveTo::create(distance / ENEMY_PROJECTILE_SPEED, tar);
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