#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__
#include "JsonInstance.h"
// Util
#define RESOLUTION_VARIABLE JsonInstance::GetInstance()->GetData("balance")["debug"]["resolution"]
#define DEBUG_MASK JsonInstance::GetInstance()->GetData("balance")["debug"]["mask"]
// Magic number solvers
#define DIRECTION_LEFT 0
#define DIRECTION_RIGHT 1
#define MULT_BY_RESOLUTION true
#define NOT_MULT_BY_RESOLUTION false
#define PI 3.14159265
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
// enemy default projectile animation and sprites
#define ENEMY_DEFAULT_PROJECTILE_ANIM_NUM_OF_FRAMES JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["regular"]["projectile"]["animationFramesNumber"]
#define ENEMY_DEFAULT_PROJECTILE_ANIM_SPEED JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["regular"]["projectile"]["animationSpeed"]
#define ENEMY_DEFAULT_PROJECTILE_ANIM_SPRITE_SIZE JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["regular"]["projectile"]["spriteSize"]
// enemy laser projectile animation and sprites
#define ENEMY_LASER_PROJECTILE_ANIM_NUM_OF_FRAMES JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["laser"]["projectile"]["animationFramesNumber"]
#define ENEMY_LASER_PROJECTILE_ANIM_SPEED JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["laser"]["projectile"]["animationSpeed"]
#define ENEMY_LASER_PROJECTILE_ANIM_SPRITE_SIZE_X JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["laser"]["projectile"]["spriteSizeX"]
#define ENEMY_LASER_PROJECTILE_ANIM_SPRITE_SIZE_Y JsonInstance::GetInstance()->GetData("animations")["enemyAnim"]["laser"]["projectile"]["spriteSizeY"]
#endif
