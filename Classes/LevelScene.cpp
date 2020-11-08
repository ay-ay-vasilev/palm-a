#include "LevelScene.h"
#include "Definitions.h"
#include "GameController.h"
#include <CCScheduler.h>


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

// show error message
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}

bool Level::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
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
	player->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 60));
    player->setScale(0.5);
	this->addChild(player, 5);

	this->scheduleUpdate();

    auto floor = Sprite::create("res/level/test_floor.png");
    floor->getTexture()->setAliasTexParameters();
    // make the character 4 times bigger
    floor->setScale(2.0);
    // make the center bottom of the character the anchor point
    floor->setAnchorPoint(Vec2(0, 0));
    // position the character on the center of the screen
    floor->setPosition(Vec2(origin.x, origin.y));
    // add the character as a child to this layer
    this->addChild(floor, 0);

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
    auto closeItem = MenuItemImage::create("res/ui/close-test.png",
                                           "res/ui/close-test.png",
                                        CC_CALLBACK_1(Level::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("res/ui/close-test.png wasn't able to be loaded");
    }
    else
    {
        closeItem->setScale(2.0);
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width;
        float y = origin.y + visibleSize.height - closeItem->getContentSize().height;
        closeItem->setPosition(Vec2(x,y));
    }
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    // ===========================================================================================
    
    //====================================
    //enemy spawn
    auto enemySpawnPointer = static_cast<cocos2d::SEL_SCHEDULE>(&Level::spawnEnemy);
    
    this->schedule(enemySpawnPointer, ENEMY_SPAWN_FREQUENCY);
    
    //====================================


    // OLD STUFF

    // // create touch listener
    // auto listener1 = EventListenerTouchOneByOne::create();
    // // trigger when you push down
    // listener1->onTouchBegan = [visibleSize, character, direction](Touch* touch, Event* event) mutable {
        
    //     if (touch->getLocation().x > visibleSize.width/2) {
    //         character->setTexture("res/character/run/test_right.png");
    //         auto action = RepeatForever::create(MoveBy::create(1, Vec2(200, 0)));
    //         character->runAction(action);
    //         direction = "right";
    //     }
    //     else {
    //         character->setTexture("res/character/run/test_left.png");
    //         auto action = RepeatForever::create(MoveBy::create(1, Vec2(-200, 0)));
    //         character->runAction(action);
    //         direction = "left";
    //     }
    //     return true; // if you are consuming it
    // };

    // // trigger when you let up
    // listener1->onTouchEnded = [character, direction](Touch* touch, Event* event){
    //     if (strncmp(direction, "left", 4)) {
    //         character->setTexture("res/character/idle/test_idle_left.png");
    //     }
    //     else if (strncmp(direction, "right", 5)) {
    //         character->setTexture("res/character/idle/test_idle_right.png");
    //     }
    //     else {
    //         character->setTexture("res/character/idle/test_idle_right.png");
    //     }

    //     character->stopAllActions();
    // };

    // // Add listener
    // _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, character);

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

void Level::spawnEnemy(float dt){
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Enemy* enemy;
    
    //doesn't work for some reason
    //enemy = GameController::spawnEnemy;

    enemy=Enemy::create();
    enemy->setPhysicsBody(enemy->getBody());
    float enemyPos = Level::enemyPosition(112);
	enemy->setPosition(Vec2(enemyPos, visibleSize.height + 112 + origin.y));
    enemy->setScale(0.5);
	this->addChild(enemy, 4);

    auto enemyAction = MoveBy::create(ENEMY_SPEED, Vec2(0, -1*visibleSize.height-origin.y-224));

    enemy->runAction(enemyAction);
}
float Level::enemyPosition(float frameSize){
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float position;
    auto random = CCRANDOM_0_1();
    if (random<0.33){
        random=0.25;
    } else if (random<0.66) {
        random=0.5;
    }else{
        random=0.75;
    }
    position = (random * visibleSize.width) + (frameSize / 2);
    return position;
}