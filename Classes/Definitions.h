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
#endif
