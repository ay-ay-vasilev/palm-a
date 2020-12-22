#pragma once
#include "cocos2d.h"

class Util
{
public:
	static cocos2d::Animate* createAnimation(cocos2d::SpriteFrameCache* spriteCache, float numOfFrames, float animSpeed, std::string assetName);

	static cocos2d::Animate* createPlayerAnimation(cocos2d::SpriteFrameCache* spriteCache, std::string numOfFrames, std::string animSpeed, std::string assetName);
	static cocos2d::Animate* createProjectileAnimation(cocos2d::SpriteFrameCache* spriteCache, std::string numOfFrames, std::string animSpeed, std::string assetName);
	static cocos2d::Animate* createEnemyAnimation(cocos2d::SpriteFrameCache* spriteCache, std::string numOfFrames, std::string animSpeed, std::string assetName);
	static cocos2d::Animate* createLevelAnimation(cocos2d::SpriteFrameCache* spriteCache, std::string numOfFrames, std::string animSpeed, std::string assetName);

private:

};