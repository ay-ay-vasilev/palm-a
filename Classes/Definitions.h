#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__
// resolution
#define RESOLUTION_VARIABLE 2 // EITHER 1, 2 or 3
// magic number solvers
#define DIRECTION_LEFT 0
#define DIRECTION_RIGHT 1
// splash definitions
#define LOGO_ANIM_NUM_OF_FRAMES 6
#define LOGO_ANIM_SPEED 0.12f
// cutscene definitions
#define DISPLAY_TIME_SPLASH_SCENE 2
#define TRANSITION_TIME 0.8f
#define FADE_LENGTH 0.5f
#define NUMBER_OF_CADRS 6
// player stats
#define PLAYER_SPEED 4
#define PLAYER_DASH_SPEED 60
#define PLAYER_JUMP_FORCE 15
#define PLAYER_GRAVITY 1
#define PLAYER_START_HP 3.0
// player animation and sprites
#define PLAYER_ANIM_IDLE_NUM_OF_FRAMES 5
#define PLAYER_ANIM_RUN_NUM_OF_FRAMES 8
#define PLAYER_ANIM_IDLE_SPEED 0.1f
#define PLAYER_ANIM_RUN_SPEED 0.06f
#define PLAYER_SPRITE_SIZE 112
// level properties
#define LEVEL_WALL_DISTANCE 40
#define LEVEL_FLOOR_HEIGHT 30
#define LEVEL_DURATION 120.0
// enemy stats
#define ENEMY_SPAWN_FREQUENCY 1
#define ENEMY_SPEED 100.0f
#define ENEMY_PROJECTILE_SPEED 200.0f
#define ENEMY_PROJECTILE_FREQUENCY 3.0f
// enemy animation and sprites
#define ENEMY_ANIM_IDLE_NUM_OF_FRAMES 5
#define ENEMY_ANIM_IDLE_SPEED 0.1f
#define ENEMY_SPRITE_SIZE 112
// damage values
#define ENEMY_PROJECTILE_DMG 1
#define ENEMY_COLLIDE_DMG 1
//laser values
#define LASER_DMG 1
#define LASER_SPAWNING_TIME 0.5f

#define PI 3.14159265 
#endif
