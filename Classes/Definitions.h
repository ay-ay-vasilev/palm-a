#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__
#include "JsonInstance.h"
// resolution
#define RESOLUTION_VARIABLE 2
// magic number solvers
#define DIRECTION_LEFT JsonInstance::GetInstance()->GetData("level1")["metadata"]["magicNumbers"]["left"]
#define DIRECTION_RIGHT JsonInstance::GetInstance()->GetData("level1")["metadata"]["magicNumbers"]["right"]
// splash definitions
#define LOGO_ANIM_NUM_OF_FRAMES JsonInstance::GetInstance()->GetData("level1")["metadata"]["splashSceneData"]["numberOfFrames"]
#define LOGO_ANIM_SPEED JsonInstance::GetInstance()->GetData("level1")["metadata"]["splashSceneData"]["logoAnimSpeed"]
// cutscene definitions
#define DISPLAY_TIME_SPLASH_SCENE JsonInstance::GetInstance()->GetData("level1")["metadata"]["cutsceneData"]["splashTime"]
#define TRANSITION_TIME JsonInstance::GetInstance()->GetData("level1")["metadata"]["cutsceneData"]["transitionTime"]
#define FADE_LENGTH JsonInstance::GetInstance()->GetData("level1")["metadata"]["cutsceneData"]["fadeLength"]
#define NUMBER_OF_CADRS JsonInstance::GetInstance()->GetData("level1")["metadata"]["cutsceneData"]["numberOfFrames"]
// player stats
#define PLAYER_SPEED JsonInstance::GetInstance()->GetData("player")["stats"]["speed"]
#define PLAYER_DASH_SPEED JsonInstance::GetInstance()->GetData("player")["stats"]["dashSpeed"]
#define PLAYER_JUMP_FORCE JsonInstance::GetInstance()->GetData("player")["stats"]["jumpForce"]
#define PLAYER_GRAVITY JsonInstance::GetInstance()->GetData("player")["stats"]["gravity"]
#define PLAYER_START_HP JsonInstance::GetInstance()->GetData("player")["stats"]["hp"]
// player animation and sprites
#define PLAYER_ANIM_IDLE_NUM_OF_FRAMES JsonInstance::GetInstance()->GetData("player")["animationData"]["idleFrames"]
#define PLAYER_ANIM_RUN_NUM_OF_FRAMES JsonInstance::GetInstance()->GetData("player")["animationData"]["runFrames"]
#define PLAYER_ANIM_IDLE_SPEED JsonInstance::GetInstance()->GetData("player")["animationData"]["idleAnimSpeed"]
#define PLAYER_ANIM_RUN_SPEED JsonInstance::GetInstance()->GetData("player")["animationData"]["runAnimSpeed"]
#define PLAYER_SPRITE_SIZE JsonInstance::GetInstance()->GetData("player")["animationData"]["spriteSize"]
// level properties
#define LEVEL_WALL_DISTANCE JsonInstance::GetInstance()->GetData("level1")["metadata"]["wallDistance"]
#define LEVEL_FLOOR_HEIGHT JsonInstance::GetInstance()->GetData("level1")["metadata"]["floorHeight"]
#define LEVEL_DURATION JsonInstance::GetInstance()->GetData("level1")["metadata"]["levelDuration"]
// enemy stats
#define ENEMY_SPAWN_FREQUENCY JsonInstance::GetInstance()->GetData("enemies")["enemyData"]["spawnFrequency"]
#define ENEMY_SPEED JsonInstance::GetInstance()->GetData("enemies")["enemyData"]["speed"]
#define ENEMY_PROJECTILE_SPEED JsonInstance::GetInstance()->GetData("enemies")["enemyProjectileData"]["speed"]
#define ENEMY_PROJECTILE_FREQUENCY 3.0f //not needed anymore
// enemy animation and sprites
#define ENEMY_ANIM_IDLE_NUM_OF_FRAMES JsonInstance::GetInstance()->GetData("enemies")["enemyData"]["animationData"]["animationFramesNumber"]
#define ENEMY_ANIM_IDLE_SPEED JsonInstance::GetInstance()->GetData("enemies")["enemyData"]["animationData"]["animationSpeed"]
#define ENEMY_SPRITE_SIZE JsonInstance::GetInstance()->GetData("enemies")["enemyData"]["animationData"]["spriteSize"]
// damage values
#define ENEMY_PROJECTILE_DMG JsonInstance::GetInstance()->GetData("enemies")["enemyProjectileData"]["default"]["damage"]
#define ENEMY_COLLIDE_DMG JsonInstance::GetInstance()->GetData("enemies")["enemyData"]["collideDamage"]
//laser values
#define LASER_DMG JsonInstance::GetInstance()->GetData("enemies")["enemyProjectileData"]["laser"]["damage"]
#define LASER_SPAWNING_TIME JsonInstance::GetInstance()->GetData("enemies")["enemyProjectileData"]["laser"]["spawningTime"]

#define PI 3.14159265;
#endif
