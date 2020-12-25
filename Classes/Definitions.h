#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__
#include "JsonInstance.h"
// Magic number solvers
#define DIRECTION_LEFT 0
#define DIRECTION_RIGHT 1
#define MULT_BY_RESOLUTION true
#define NOT_MULT_BY_RESOLUTION false
#define DMG_IFRAMES 0
#define DASH_IFRAMES 1
#define PI 3.14159265
// Collision masks
#define PLAYER_MASK 1
#define REGULAR_ENEMY_MASK 2
#define DEFAULT_PROJECTILE_MASK 3
#define LASER_ENEMY_MASK 5
#define LASER_PROJECTILE_MASK 4
#define TURRET_ENEMY_MASK 6
#define RAY_PROJECTILE_MASK 7
#define BOSS_MASK 8
#define PLAYER_PROJECTILE_MASK 9
// Layers
#define BEHIND -1
#define PLAYER_LAYER 6
#define ENEMY_LAYER 4
#define TURRET_LAYER 3
#define PROJECTILE_LAYER 5
#define BOSS_LAYER 3
#define BOSS_PROJECTILE_LAYER 6
#define FLOOR_LAYER 0
#define BACKGROUND_CLOSE_LAYER -1
#define BACKGROUND_MID_LAYER -2
#define BACKGROUND_FAR_LAYER -3
#define UI_LAYER 10
#define PAUSE_MENU_LAYER 13
#define PAUSE_BACKGROUND_LAYER 12
#define BAR_UNDER_LAYER 9
#define BAR_LAYER 10
#define BAR_OVER_LAYER 11
#define PARTICLES_LAYER 6
// Tags
#define ANIMATION_TAG 1
// Splash definitions
#define LOGO_ANIM_NUM_OF_FRAMES 6
#define LOGO_ANIM_SPEED 0.12
#define DISPLAY_TIME_SPLASH_SCENE 2
#define TRANSITION_TIME 0.8
// Util
#define RESOLUTION_VARIABLE JsonInstance::GetInstance()->GetData("balance")["debug"]["resolution"]
#define DEBUG_MASK JsonInstance::GetInstance()->GetData("balance")["debug"]["mask"]
#define PLAYER_TYPE JsonInstance::GetInstance()->GetData("balance")["debug"]["playerType"]
#endif