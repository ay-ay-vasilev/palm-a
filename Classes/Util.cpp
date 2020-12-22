#include "Util.h"
#include "GameConstants.h"

cocos2d::Animate* Util::createAnimation(cocos2d::SpriteFrameCache* spriteCache, float numOfFrames, float animSpeed, std::string assetName)
{
	char str[200] = { 0 };
	cocos2d::Vector<cocos2d::SpriteFrame*> animFrames(numOfFrames);

	for (int i = 1; i <= numOfFrames; i++)
	{
		sprintf(str, assetName.c_str(), i);
		auto frame = spriteCache->getSpriteFrameByName(str);
		frame->getTexture()->setAliasTexParameters();
		animFrames.pushBack(frame);
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(animFrames, animSpeed);

	return cocos2d::Animate::create(animation);
}

cocos2d::Animate* Util::createPlayerAnimation(cocos2d::SpriteFrameCache* spriteCache, std::string numOfFrames, std::string animSpeed, std::string assetName)
{
	auto assetPath = GameConstants::getPlayerAssetPath(assetName);
	auto numberOfFrames = GameConstants::getPlayerAnimationData(numOfFrames);
	auto animationSpeed = GameConstants::getPlayerAnimationData(animSpeed);

	return Util::createAnimation(spriteCache, numberOfFrames, animationSpeed, assetPath);
}

cocos2d::Animate* Util::createProjectileAnimation(cocos2d::SpriteFrameCache* spriteCache, std::string numOfFrames, std::string animSpeed, std::string assetName)
{
	auto assetPath = GameConstants::getProjectileAssetPath(assetName);
	auto numberOfFrames = GameConstants::getProjectileAnimationData(numOfFrames);
	auto animationSpeed = GameConstants::getProjectileAnimationData(animSpeed);

	return Util::createAnimation(spriteCache, numberOfFrames, animationSpeed, assetPath);
}

cocos2d::Animate* Util::createEnemyAnimation(cocos2d::SpriteFrameCache* spriteCache, std::string numOfFrames, std::string animSpeed, std::string assetName)
{
	auto assetPath = GameConstants::getEnemyAssetPath(assetName);
	auto numberOfFrames = GameConstants::getEnemyAnimationData(numOfFrames);
	auto animationSpeed = GameConstants::getEnemyAnimationData(animSpeed);

	return Util::createAnimation(spriteCache, numberOfFrames, animationSpeed, assetPath);
}

cocos2d::Animate* Util::createLevelAnimation(cocos2d::SpriteFrameCache* spriteCache, std::string numOfFrames, std::string animSpeed, std::string assetName)
{
	auto assetPath = GameConstants::getLevelAssetPath(assetName);
	auto numberOfFrames = GameConstants::getLevelAnimationData(numOfFrames);
	auto animationSpeed = GameConstants::getLevelAnimationData(animSpeed);

	return Util::createAnimation(spriteCache, numberOfFrames, animationSpeed, assetPath);
}