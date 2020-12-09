#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__
#include "JsonInstance.h"
// Util
#define RESOLUTION_VARIABLE JsonInstance::GetInstance()->GetData("balance")["debug"]["resolution"]
#define DEBUG_MASK JsonInstance::GetInstance()->GetData("balance")["debug"]["mask"]
// Magic number solvers
#define DIRECTION_LEFT 0
#define DIRECTION_RIGHT 1
// Splash definitions
#define LOGO_ANIM_NUM_OF_FRAMES 6
#define LOGO_ANIM_SPEED 0.12
// Level 1 data
#define DISPLAY_TIME_SPLASH_SCENE JsonInstance::GetInstance()->GetData("level1")["metadata"]["cutsceneData"]["splashTime"]
#define TRANSITION_TIME JsonInstance::GetInstance()->GetData("level1")["metadata"]["cutsceneData"]["transitionTime"]
#define FADE_LENGTH JsonInstance::GetInstance()->GetData("level1")["metadata"]["cutsceneData"]["fadeLength"]
#define NUMBER_OF_CADRS JsonInstance::GetInstance()->GetData("level1")["metadata"]["cutsceneData"]["numberOfFrames"]
#define LEVEL_1_DATA JsonInstance::GetInstance()->GetData("balance")["level"]["timings"]
#define ENEMIES_SPAWN_TIMINGS JsonInstance::GetInstance()->GetData("level1")["enemySpawnTimings"]["timingsPath"]
#define ENEMIES_SPAWN_TYPES JsonInstance::GetInstance()->GetData("level1")["enemySpawnTimings"]["typesPath"]
#define ENEMIES_SPAWN_POINTS JsonInstance::GetInstance()->GetData("level1")["enemySpawnTimings"]["pointsPath"]
// Level properties
#define LEVEL_WALL_DISTANCE JsonInstance::GetInstance()->GetData("balance")["level"]["wallDistance"]
#define LEVEL_FLOOR_HEIGHT JsonInstance::GetInstance()->GetData("balance")["level"]["floorHeight"]
#define LEVEL_DURATION JsonInstance::GetInstance()->GetData("balance")["level"]["levelDuration"]
// Player stats
#define PLAYER_SPEED JsonInstance::GetInstance()->GetData("balance")["player"]["speed"]
#define PLAYER_DASH_SPEED JsonInstance::GetInstance()->GetData("balance")["player"]["dashSpeed"]
#define PLAYER_JUMP_FORCE JsonInstance::GetInstance()->GetData("balance")["player"]["jumpForce"]
#define PLAYER_GRAVITY JsonInstance::GetInstance()->GetData("balance")["player"]["gravity"]
#define PLAYER_MAX_FALL_SPEED JsonInstance::GetInstance()->GetData("balance")["player"]["maxFallSpeed"]
#define PLAYER_MAX_JUMP_SPEED JsonInstance::GetInstance()->GetData("balance")["player"]["maxJumpSpeed"]
#define PLAYER_START_HP JsonInstance::GetInstance()->GetData("balance")["player"]["hp"]
#define PLAYER_ADDITIONAL_JUMPS JsonInstance::GetInstance()->GetData("balance")["player"]["additionalJumps"]
#define PLAYER_JUMP_KILL_FORCE JsonInstance::GetInstance()->GetData("balance")["player"]["jumpKillForce"]
#define PLAYER_REFILL_JUMPS_ON_KILL JsonInstance::GetInstance()->GetData("balance")["player"]["refillJumpsOnKill"]
//Enemy stats
// Default
#define ENEMY_DEFAULT_SPEED JsonInstance::GetInstance()->GetData("balance")["enemy"]["default"]["speed"]
#define ENEMY_DEFAULT_SPAWN_FREQUENCY JsonInstance::GetInstance()->GetData("balance")["enemy"]["default"]["spawnFrequency"]
#define ENEMY_DEFAULT_COLLIDE_DMG JsonInstance::GetInstance()->GetData("balance")["enemy"]["default"]["collideDamage"]
#define ENEMY_DEFAULT_PROJECTILE_DMG JsonInstance::GetInstance()->GetData("balance")["enemy"]["default"]["projectileDamage"]
#define ENEMY_DEFAULT_PROJECTILE_SPEED JsonInstance::GetInstance()->GetData("balance")["enemy"]["default"]["projectileSpeed"]
// Laser
#define ENEMY_LASER_SPEED JsonInstance::GetInstance()->GetData("balance")["enemy"]["laser"]["speed"]
#define ENEMY_LASER_SPAWN_FREQUENCY JsonInstance::GetInstance()->GetData("balance")["enemy"]["laser"]["spawnFrequency"]
#define ENEMY_LASER_COLLIDE_DMG JsonInstance::GetInstance()->GetData("balance")["enemy"]["laser"]["collideDamage"]
#define ENEMY_LASER_PROJECTILE_DMG JsonInstance::GetInstance()->GetData("balance")["enemy"]["laser"]["projectileDamage"]
#define ENEMY_LASER_PROJECTILE_SPEED JsonInstance::GetInstance()->GetData("balance")["enemy"]["laser"]["projectileSpeed"]

// Animation
// player animation and sprites
#define PLAYER_ANIM_IDLE_NUM_OF_FRAMES JsonInstance::GetInstance()->GetData("animations")["playerAnim"]["idleFrames"]
#define PLAYER_ANIM_RUN_NUM_OF_FRAMES JsonInstance::GetInstance()->GetData("animations")["playerAnim"]["runFrames"]
#define PLAYER_ANIM_JUMP_NUM_OF_FRAMES JsonInstance::GetInstance()->GetData("animations")["playerAnim"]["jumpFrames"]
#define PLAYER_ANIM_FALL_NUM_OF_FRAMES JsonInstance::GetInstance()->GetData("animations")["playerAnim"]["fallFrames"]
#define PLAYER_ANIM_IDLE_SPEED JsonInstance::GetInstance()->GetData("animations")["playerAnim"]["idleAnimSpeed"]
#define PLAYER_ANIM_RUN_SPEED JsonInstance::GetInstance()->GetData("animations")["playerAnim"]["runAnimSpeed"]
#define PLAYER_ANIM_JUMP_SPEED JsonInstance::GetInstance()->GetData("animations")["playerAnim"]["jumpAnimSpeed"]
#define PLAYER_ANIM_FALL_SPEED JsonInstance::GetInstance()->GetData("animations")["playerAnim"]["fallAnimSpeed"]
#define PLAYER_SPRITE_SIZE JsonInstance::GetInstance()->GetData("animations")["playerAnim"]["spriteSize"]
// enemy animation and sprites
#define ENEMY_DEFAULT_ANIM_IDLE_NUM_OF_FRAMES JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["default"]["animationFramesNumber"]
#define ENEMY_DEFAULT_ANIM_IDLE_SPEED JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["default"]["animationSpeed"]
#define ENEMY_DEFAULT_SPRITE_SIZE JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["default"]["spriteSize"]
#define ENEMY_LASER_ANIM_IDLE_NUM_OF_FRAMES JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["laser"]["animationFramesNumber"]
#define ENEMY_LASER_ANIM_IDLE_SPEED JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["laser"]["animationSpeed"]
#define ENEMY_LASER_SPRITE_SIZE JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["laser"]["spriteSize"]
#define ENEMY_TURRET_ANIM_IDLE_NUM_OF_FRAMES JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["turret"]["animationFramesNumber"]
#define ENEMY_TURRET_ANIM_IDLE_SPEED JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["turret"]["animationSpeed"]
#define ENEMY_TURRET_SPRITE_SIZE JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["turret"]["spriteSize"]
// enemy default projectile animation and sprites
#define ENEMY_DEFAULT_PROJECTILE_ANIM_NUM_OF_FRAMES JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["default"]["projectile"]["animationFramesNumber"]
#define ENEMY_DEFAULT_PROJECTILE_ANIM_SPEED JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["default"]["projectile"]["animationSpeed"]
#define ENEMY_DEFAULT_PROJECTILE_ANIM_SPRITE_SIZE JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["default"]["projectile"]["spriteSize"]
// enemy laser projectile animation and sprites
#define ENEMY_LASER_PROJECTILE_ANIM_NUM_OF_FRAMES JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["laser"]["projectile"]["animationFramesNumber"]
#define ENEMY_LASER_PROJECTILE_ANIM_SPEED JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["laser"]["projectile"]["animationSpeed"]
#define ENEMY_LASER_PROJECTILE_ANIM_SPRITE_SIZE_X JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["laser"]["projectile"]["spriteSizeX"]
#define ENEMY_LASER_PROJECTILE_ANIM_SPRITE_SIZE_Y JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["laser"]["projectile"]["spriteSizeY"]

#define PI 3.14159265
#endif
