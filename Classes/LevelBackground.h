#ifndef LEVELBACKGROUND_H_
#define LEVELBACKGROUND_H_

#include "cocos2d.h"

USING_NS_CC;

class LevelBackground : public cocos2d::Sprite
{
public:
	static LevelBackground* create(std::string level);
    void initBackground(std::string level);

    void update();

private:
    ~LevelBackground();

    cocos2d::ParallaxNode* paraNodeClose;
    cocos2d::ParallaxNode* paraNodeMid;
    cocos2d::ParallaxNode* paraNodeFar;
    float closeSpeed;
    float midSpeed;
    float farSpeed;

    static cocos2d::ParallaxNode* createParallaxLayer(cocos2d::SpriteFrameCache* spriteCache, std::string numOfFrames, std::string animSpeed, std::string assetName, float speed);
    static cocos2d::Sprite* createLayer(cocos2d::SpriteFrameCache* spriteCache, std::string numOfFrames, std::string animSpeed, std::string assetName);
};

#endif /* LEVELBACKGROUND_H_ */