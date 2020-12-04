#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__
#include "JsonInstance.h"
// util
#define RESOLUTION_VARIABLE JsonInstance::GetInstance()->GetData("balance")["debug"]["resolution"]
#define DEBUG_MASK JsonInstance::GetInstance()->GetData("balance")["debug"]["mask"]
// magic number solvers
#define DIRECTION_LEFT 0
#define DIRECTION_RIGHT 1
// splash definitions
#define LOGO_ANIM_NUM_OF_FRAMES 6
#define LOGO_ANIM_SPEED 0.12
// cutscene definitions
#define DISPLAY_TIME_SPLASH_SCENE 2
#define TRANSITION_TIME 0.8
#define FADE_LENGTH 0.5
#define NUMBER_OF_CADRS 6
// level properties
#define LEVEL_WALL_DISTANCE JsonInstance::GetInstance()->GetData("balance")["level"]["wallDistance"]
#define LEVEL_FLOOR_HEIGHT JsonInstance::GetInstance()->GetData("balance")["level"]["floorHeight"]
#define LEVEL_DURATION JsonInstance::GetInstance()->GetData("balance")["level"]["levelDuration"]

// player stats
#define PLAYER_SPEED JsonInstance::GetInstance()->GetData("balance")["player"]["speed"]
#define PLAYER_DASH_SPEED JsonInstance::GetInstance()->GetData("balance")["player"]["dashSpeed"]
#define PLAYER_JUMP_FORCE JsonInstance::GetInstance()->GetData("balance")["player"]["jumpForce"]
#define PLAYER_GRAVITY JsonInstance::GetInstance()->GetData("balance")["player"]["gravity"]
#define PLAYER_START_HP JsonInstance::GetInstance()->GetData("balance")["player"]["hp"]
//enemy stats NEW
#define ENEMY_DEFAULT_SPEED JsonInstance::GetInstance()->GetData("balance")["enemy"]["default"]["speed"]
#define ENEMY_DEFAULT_SPAWN_FREQUENCY JsonInstance::GetInstance()->GetData("balance")["enemy"]["default"]["spawnFrequency"]
#define ENEMY_DEFAULT_COLLIDE_DMG JsonInstance::GetInstance()->GetData("balance")["enemy"]["default"]["collideDamage"]
#define ENEMY_DEFAULT_PROJECTILE_DMG JsonInstance::GetInstance()->GetData("balance")["enemy"]["default"]["projectileDamage"]
#define ENEMY_DEFAULT_PROJECTILE_SPEED JsonInstance::GetInstance()->GetData("balance")["enemy"]["default"]["projectileSpeed"]

#define ENEMY_LASER_SPEED JsonInstance::GetInstance()->GetData("balance")["enemy"]["laser"]["speed"]
#define ENEMY_LASER_SPAWN_FREQUENCY JsonInstance::GetInstance()->GetData("balance")["enemy"]["laser"]["spawnFrequency"]
#define ENEMY_LASER_COLLIDE_DMG JsonInstance::GetInstance()->GetData("balance")["enemy"]["laser"]["collideDamage"]
#define ENEMY_LASER_PROJECTILE_DMG JsonInstance::GetInstance()->GetData("balance")["enemy"]["laser"]["projectileDamage"]
#define ENEMY_LASER_PROJECTILE_SPEED JsonInstance::GetInstance()->GetData("balance")["enemy"]["laser"]["projectileSpeed"]

// player animation and sprites
#define PLAYER_ANIM_IDLE_NUM_OF_FRAMES JsonInstance::GetInstance()->GetData("animations")["playerAnim"]["idleFrames"]
#define PLAYER_ANIM_RUN_NUM_OF_FRAMES JsonInstance::GetInstance()->GetData("animations")["playerAnim"]["runFrames"]
#define PLAYER_ANIM_IDLE_SPEED JsonInstance::GetInstance()->GetData("animations")["playerAnim"]["idleAnimSpeed"]
#define PLAYER_ANIM_RUN_SPEED JsonInstance::GetInstance()->GetData("animations")["playerAnim"]["runAnimSpeed"]
#define PLAYER_SPRITE_SIZE JsonInstance::GetInstance()->GetData("animations")["playerAnim"]["spriteSize"]
// enemy animation and sprites
#define ENEMY_ANIM_IDLE_NUM_OF_FRAMES JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["animationFramesNumber"]
#define ENEMY_ANIM_IDLE_SPEED JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["animationSpeed"]
#define ENEMY_SPRITE_SIZE JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["spriteSize"]

#define PI 3.14159265
#endif
